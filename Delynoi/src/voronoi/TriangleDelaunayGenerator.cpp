#include <Delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <utility>

extern "C" {
#include <Delynoi/voronoi/lib/triangle.h>
}

using namespace Delynoi;

TriangleDelaunayGenerator::TriangleDelaunayGenerator(const std::vector<Point> &points, const Region &region) {
    this->region = region;
    this->seedPoints = points;
    this->delaunayEdges = new SegmentMap;
}

void TriangleDelaunayGenerator::callTriangle(std::vector<Point> &point_list, char *switches) {
    this->empty = true;
    this->callTriangle(point_list, switches, std::vector<PointSegment>());
}

void TriangleDelaunayGenerator::callTriangle(std::vector<Point> &point_list, char *switches, const std::vector<PointSegment> &restrictedSegments) {
    this->empty = true;
    triangulateio in{}, out{};

    std::vector<Point> regionPoints = region.getRegionPoints();
    UniqueList<Point> pointList;
    pointList.push_list(point_list);
    std::vector<int> regionIndex = pointList.push_list(regionPoints);

    in.numberofpoints = pointList.size();
    in.pointlist = static_cast<double *>(malloc(in.numberofpoints * 2 * sizeof(REAL_TRIANGLE)));
    in.numberofpointattributes = 1;
    in.pointattributelist = static_cast<double *>(malloc(in.numberofpoints * in.numberofpointattributes * sizeof(REAL_TRIANGLE)));
    int _points = 0;

    for (int i = 0; i < pointList.size(); i++) {
        in.pointlist[_points] = pointList[i].getX();
        in.pointlist[_points + 1] = pointList[i].getY();
        in.pointattributelist[i] = 0.0;
        _points += 2;
    }

    in.pointmarkerlist = static_cast<int *>(nullptr);

    std::vector<IndexSegment> segments;
    region.getSegments(segments);

    in.numberofsegments = static_cast<int>(segments.size() + restrictedSegments.size());
    in.segmentlist = static_cast<int *>(malloc(in.numberofsegments * 2 * sizeof(int)));
    in.segmentmarkerlist = static_cast<int *>(nullptr);
    int k;
    for (k = 0; k < segments.size(); k++) {
        in.segmentlist[2 * k] = regionIndex[segments[k].getFirst()];
        in.segmentlist[2 * k + 1] = regionIndex[segments[k].getSecond()];
    }

    for (const auto &s: restrictedSegments) {
        in.segmentlist[2 * k] = pointList.indexOf(s.getFirst());
        in.segmentlist[2 * k + 1] = pointList.indexOf(s.getSecond());
        k++;
    }

    std::vector<Hole> &holes = region.getHoles();
    in.numberofholes = static_cast<int>(holes.size());
    in.holelist = static_cast<double *>(malloc(in.numberofholes * 2 * sizeof(REAL_TRIANGLE)));
    for (int i = 0; i < holes.size(); i++) {
        in.holelist[2 * i] = holes[i].getCenter().getX();
        in.holelist[2 * i + 1] = holes[i].getCenter().getY();
    }

    in.numberofregions = 0;

    out.pointlist = static_cast<double *>(nullptr);
    out.pointattributelist = static_cast<double *>(nullptr);
    out.pointmarkerlist = static_cast<int *>(nullptr);
    out.trianglelist = static_cast<int *>(nullptr);
    out.triangleattributelist = static_cast<double *>(nullptr);
    out.segmentmarkerlist = static_cast<int *>(nullptr);
    out.segmentlist = static_cast<int *>(nullptr);
    out.edgelist = static_cast<int *>(nullptr);
    out.edgemarkerlist = static_cast<int *>(nullptr);

    triangulate(switches, &in, &out, nullptr);

    for (int i = 0; i < out.numberofpoints; i++) {
        PointData data(i);
        this->points.push_back(data);
        this->meshPoints.emplace_back(out.pointlist[i * 2], out.pointlist[i * 2 + 1]);
        if (out.pointmarkerlist[i] == 1) {
            this->meshPoints.back().setBoundary();
        }
    }

    for (int i = 0; i < out.numberofedges; i++) {
        EdgeData data(out.edgelist[2 * i], out.edgelist[2 * i + 1]);
        this->edges.push_back(data);
        edgeMap.insert(std::make_pair(Key(out.edgelist[2 * i], out.edgelist[2 * i + 1]), i));
        this->points[out.edgelist[2 * i]].setEdge(i, out.edgemarkerlist[i]);
        this->points[out.edgelist[2 * i + 1]].setEdge(i, out.edgemarkerlist[i]);
    }

    for (int i = 0; i < out.numberoftriangles; i++) {
        // ReSharper disable once CppTemplateArgumentsCanBeDeduced
        std::vector<int> triangle_points = {out.trianglelist[3 * i], out.trianglelist[3 * i + 1], out.trianglelist[3 * i + 2]}; // MacOS requires <int>
        realPoints.push_back(out.trianglelist[3 * i]);
        realPoints.push_back(out.trianglelist[3 * i + 1]);
        realPoints.push_back(out.trianglelist[3 * i + 2]);

        Triangle triangle(triangle_points, this->meshPoints, this->circumcenters);
        int i1 = edgeMap[Key(out.trianglelist[3 * i], out.trianglelist[3 * i + 1])];
        int i2 = edgeMap[Key(out.trianglelist[3 * i + 1], out.trianglelist[3 * i + 2])];
        int i3 = edgeMap[Key(out.trianglelist[3 * i + 2], out.trianglelist[3 * i])];

        this->edges[i1].setTriangle(i);
        this->edges[i2].setTriangle(i);
        this->edges[i3].setTriangle(i);

        this->triangles.push_back(triangle);
    }

    for (auto data: edges) {
        IndexSegment segment(data.p1, data.p2);
        NeighboursBySegment neighbours(data.t1, data.t2);

        this->delaunayEdges->insert(segment, neighbours);
    }

    free(in.pointlist);
    free(in.pointattributelist);
    free(in.pointmarkerlist);
    free(in.segmentlist);
    free(in.segmentmarkerlist);
    free(in.holelist);

    free(out.pointlist);
    free(out.pointattributelist);
    free(out.pointmarkerlist);
    free(out.trianglelist);
    free(out.triangleattributelist);
    free(out.segmentmarkerlist);
    free(out.segmentlist);
    free(out.edgelist);
    free(out.edgemarkerlist);
}

Mesh<Triangle> &TriangleDelaunayGenerator::getConformingDelaunayTriangulation(const bool ignoreInvalidTriangles) {
    if (!this->empty) {
        char switches[] = "pzejDQ";
        callTriangle(seedPoints, switches);
    }
    if (this->meshInitialized) return this->mesh;
    this->mesh = initializeMesh<Triangle>(ignoreInvalidTriangles);
    this->meshInitialized = true;
    return this->mesh;
}

void TriangleDelaunayGenerator::writeTriangleInputFile(UniqueList<Point> &point_list, Region _region, std::vector<int> regionIndex) {
    std::string path = utilities::getPath();
    path += "toTriangle.poly";

    std::ofstream file;
    file.open(path, std::ios::out);

    file << point_list.size() << " 2 0 0" << std::endl;
    for (int i = 0; i < point_list.size(); ++i) {
        file << i << " " << point_list[i].getString() << std::endl;
    }

    std::vector<IndexSegment> segments;
    _region.getSegments(segments);

    file << segments.size() << " 0" << std::endl;
    for (int i = 0; i < segments.size(); ++i) {
        file << i << " " << regionIndex[segments[i].getFirst()] << " " << regionIndex[segments[i].getSecond()] << std::endl;
    }

    std::vector<Hole> holes = _region.getHoles();

    file << holes.size() << std::endl;

    for (int j = 0; j < holes.size(); ++j) {
        file << j << " " << holes[j].getCenter().getString() << std::endl;
    }

    file.close();
}

DelaunayInfo TriangleDelaunayGenerator::getConformingDelaunay() {
    if (!this->empty) {
        char switches[] = "pzejDQ";
        callTriangle(seedPoints, switches);
    }

    return DelaunayInfo(triangles, meshPoints, delaunayEdges, points, realPoints, edges, edgeMap, circumcenters);
}

Mesh<Triangle> TriangleDelaunayGenerator::getConstrainedDelaunayTriangulation(const bool ignoreInvalidTriangles) {
    if (!this->empty) {
        char switches[] = "pzejQ";
        callTriangle(seedPoints, switches);
    }

    return initializeMesh<Triangle>(ignoreInvalidTriangles);
}

Mesh<Triangle> TriangleDelaunayGenerator::getConstrainedDelaunayTriangulation(const std::vector<PointSegment> &restrictedSegments, const bool ignoreInvalidTriangles) {
    if (!this->empty) {
        char switches[] = "pzejQ";
        callTriangle(seedPoints, switches, restrictedSegments);
    }

    return initializeMesh<Triangle>(ignoreInvalidTriangles);
}
