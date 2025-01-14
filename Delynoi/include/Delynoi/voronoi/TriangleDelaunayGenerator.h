#ifndef DELYNOI_TRIANGLEDELAUNAY_H
#define DELYNOI_TRIANGLEDELAUNAY_H

#include <Delynoi/models/Mesh.h>
#include <Delynoi/models/Region.h>
#include <Delynoi/utilities/delynoi_utilities.h>
#include <Delynoi/voronoi/structures/DelaunayInfo.h>
#include <Delynoi/voronoi/structures/PointData.h>

namespace Delynoi {
    /*
     * Class in charge of computing the Delaunay triangulation using the seed points and domain given, using Triangle.
     */
    class TriangleDelaunayGenerator {
    private:
        /*
         * Input parameters, seed points for the diagram and domain
         */
        Region region;
        std::vector<Point> seedPoints;

        /*
         * Output for the representation of the Delaunay triangulation as a Delynoi mesh
         */
        std::vector<Triangle> triangles;
        std::vector<Point> meshPoints;
        SegmentMap *delaunayEdges;

        /*
         * Information for the computation of the Voronoi diagram
         */
        std::vector<PointData> points;
        UniqueList<int> realPoints;
        std::vector<EdgeData> edges;
        UniqueList<Point> circumcenters;
        std::unordered_map<Key, int, KeyHasher> edgeMap;
        bool empty = false;
        bool meshInitialized = false;
        Mesh<Triangle> mesh;

        /* Calls the Triangle library, filling the class members with the result
         * @param point_list points which Delaunay triangulation must be computed
         * @param switches list of switches for Triangle (define a number of options)
         */
        void callTriangle(std::vector<Point> &point_list, char switches[]);

        /* Calls the Triangle library, filling the class members with the result
         * @param point_list points which Delaunay triangulation must be computed
         * @param switches list of switches for Triangle (define a number of options)
         * @param restrictedSegment list of segments inside the domain which must be included in the triangulation
         */
        void callTriangle(std::vector<Point> &point_list, char switches[], const std::vector<PointSegment> &restrictedSegments);

    public:
        /*
         * Constructor
         */
        TriangleDelaunayGenerator(const std::vector<Point> &points, const Region &region);

        /* Returns the conforming Delaunay triangulation (all triangles, even those in the boundary or next to restricted
         * segments, are Delaunay through the inclusion of additional points)
         * @return the conforming Delaunay triangulation
         */
        Mesh<Triangle> &getConformingDelaunayTriangulation(bool ignoreInvalidTriangles = false);

        /* Returns the constrained Delaunay triangulation (triangles next to constrained segments are not necessarily
         * delaunay)
         * @return the constrained Delaunay triangulation
         */
        Mesh<Triangle> getConstrainedDelaunayTriangulation(bool ignoreInvalidTriangles = false);

        /* Returns the constrained Delaunay triangulation (triangles next to constrained segments are not necessarily
         * delaunay)
         * @return the constrained Delaunay triangulation
         */
        Mesh<Triangle> getConstrainedDelaunayTriangulation(const std::vector<PointSegment> &restrictedSegments, bool ignoreInvalidTriangles = false);

        /* Returns the conforming Delaunay triangulation in the format that can be used to compute the Voronoi diagram
         * @return Delaunay triangulation in DelaunayInfo format
         */
        DelaunayInfo getConformingDelaunay();

        /* Writes the input information in a text file (so that we can call Triangle externally)
         * @param point_list seed points
         * @param region domain in which the triangulation must be computed
         * @param regionIndex indexes of the points (in point_list) definining the region
         */
        static void writeTriangleInputFile(UniqueList<Point> &point_list, Region _region, std::vector<int> regionIndex);

        /* Creates a Mesh (in Delynoi format) from the information of the Delaunay triangulation
        * @return Delaunay triangulation in Mesh form
        */
        template<typename T>
        Mesh<T> initializeMesh(const bool ignoreInvalidTriangles = false) {
            UniqueList<Point> _points;
            auto *pointMap = new PointMap;
            const std::vector<int> indexes = _points.push_list(this->meshPoints);

            std::vector<T> polygons;
            for (int i = 0; i < triangles.size(); i++) {
                Triangle t = triangles[i];
                std::vector<int> oldPoints = t.getPoints();
                std::vector<int> newPoints;

                for (int j = 0; j < oldPoints.size(); ++j) {
                    newPoints.push_back(indexes[oldPoints[j]]);
                    pointMap->insert(meshPoints[newPoints[j]], i);
                }

                try {
                    delynoi_utilities::checkTriangleIntegrity(newPoints);
                    polygons.push_back(T(newPoints, meshPoints));
                } catch (std::exception &) {
                    if (!ignoreInvalidTriangles) throw;
                }
            }

            return Mesh<T>(_points, polygons, this->delaunayEdges, pointMap);
        }
    };
} // namespace Delynoi

#endif
