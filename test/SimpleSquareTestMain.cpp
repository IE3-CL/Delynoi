#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/models/generator/functions/functions.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <delynoi/models/generator/noise/noise.h>

int main(){
    using namespace Delynoi;

    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
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