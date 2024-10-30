#ifndef DELYNOI_DELAUNAYTRIANGULATIONGENERATOR_H
#define DELYNOI_DELAUNAYTRIANGULATIONGENERATOR_H

#include <Delynoi/models/Region.h>
#include <Delynoi/triangulation/TriangulationGenerator.h>
#include <Delynoi/voronoi/TriangleDelaunayGenerator.h>

namespace Delynoi {
    /*
     * Class that trriangulates a Polygon using its Delaunay triangulation.
     */
    class DelaunayTriangulationGenerator final : public TriangulationGenerator {
    public:
        /* Triangulates a polygon.
        * @param p polygon to triangulate
        * @param points list of points instances which the polygon points reference to (most likely, mesh points)
        * @return list of triangles obtained triangulating the polygon
        */
        std::vector<Triangle> triangulate(Polygon p, std::vector<Point> &points) override;
    };
} // namespace Delynoi

#endif