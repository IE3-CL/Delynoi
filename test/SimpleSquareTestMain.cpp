#include <Delynoi/models/basic/Point.h>
#include <Delynoi/models/Region.h>
#include <Delynoi/models/generator/functions/functions.h>
#include <Delynoi/voronoi/TriangleVoronoiGenerator.h>

using namespace Delynoi;

int main() {
    std::vector<Point> square_points = {Point(0, 0), Point(10, 0), Point(10, 10), Point(0, 10)};
    Region square(square_points);

    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 3, 3);
    std::vector<Point> seeds = square.getSeedPoints();
    TriangleDelaunayGenerator delaunayGenerator(seeds, square);
    TriangleVoronoiGenerator g(seeds, square);
    Mesh<Polygon> m = g.getMesh();
    Mesh<Triangle> t = delaunayGenerator.getConstrainedDelaunayTriangulation();
    m.printInFile("simpleSquareMesh.txt");
    t.printInFile("simpleSquareMesh_t.txt");

    return 0;
}