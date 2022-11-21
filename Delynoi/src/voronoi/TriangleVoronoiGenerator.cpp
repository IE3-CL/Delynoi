#include <Delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <Delynoi/voronoi/DelaunayToVoronoi.h>

using namespace Delynoi;

TriangleVoronoiGenerator::TriangleVoronoiGenerator(std::vector<Point> &point_list, const Region &region) {
    TriangleDelaunayGenerator delaunayGenerator(point_list, region);
    DelaunayInfo _delaunay = delaunayGenerator.getConformingDelaunay();

    this->delaunay = delaunayGenerator.initializeMesh<Polygon>();
    this->voronoi = DelaunayToVoronoi(_delaunay).getMesh();
}

Mesh<Polygon> &TriangleVoronoiGenerator::getMesh() {
    return this->voronoi;
}

Mesh<Polygon> &TriangleVoronoiGenerator::getTriangulation() {
    return this->delaunay;
}

void TriangleVoronoiGenerator::clear() {
    this->voronoi.clear();
    this->delaunay.clear();
}
