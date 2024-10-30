#include <Delynoi/triangulation/DelaunayTriangulationGenerator.h>

using namespace Delynoi;

std::vector<Triangle> DelaunayTriangulationGenerator::triangulate(const Polygon p, std::vector<Point> &points) {
    const Region r(p, points);

    TriangleDelaunayGenerator generator(points, r);
    Mesh<Triangle> triangulation = generator.getConstrainedDelaunayTriangulation();

    return triangulation.getPolygons();
}
