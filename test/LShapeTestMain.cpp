#include <Delynoi/models/basic/Point.h>
#include <Delynoi/models/Region.h>
#include <Delynoi/models/generator/functions/functions.h>
#include <Delynoi/voronoi/TriangleVoronoiGenerator.h>

using namespace Delynoi;

int main() {
    std::vector<Point> l_points = {Point(10, 0), Point(20, 0), Point(20, 20), Point(0, 20), Point(0, 10), Point(10, 10)};
    Region l_region(l_points);

    l_region.generateSeedPoints(PointGenerator(functions::random_double(0, 20), functions::random_double(0, 20)), 10, 10);
    std::vector<Point> seeds = l_region.getSeedPoints();

    TriangleVoronoiGenerator g(seeds, l_region);
    Mesh<Polygon> LRandom = g.getMesh();
    LRandom.printInFile("LShapedMesh.txt");
}
