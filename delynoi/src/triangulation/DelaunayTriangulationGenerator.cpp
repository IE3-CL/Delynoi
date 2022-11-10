#include <delynoi/triangulation/DelaunayTriangulationGenerator.h>

using namespace Delynoi;

std::vector<Triangle> DelaunayTriangulationGenerator::triangulate(Polygon p, std::vector<Point> &points) {
    Region r(p, points);

    TriangleDelaunayGenerator generator(points, r);
    Mesh<Triangle> triangulation = generator.getConstrainedDelaunayTriangulation();

    return triangulation.getPolygons();
}
