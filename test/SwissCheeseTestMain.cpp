#include <Delynoi/models/basic/Point.h>
#include <Delynoi/models/Region.h>
#include <Delynoi/models/hole/CircularHole.h>
#include <Delynoi/models/generator/functions/functions.h>
#include <Delynoi/voronoi/TriangleVoronoiGenerator.h>

int main() {
    using namespace Delynoi;

    std::vector<Point> square_points = {Point(0, 0), Point(10, 0), Point(10, 10), Point(0, 10)};
    Region square(square_points);

    Hole circular0 = CircularHole(Point(5, 10), 2);
    Hole circular1 = CircularHole(Point(10, 5), 2);
    Hole circular2 = CircularHole(Point(5, 0), 2);
    Hole circular3 = CircularHole(Point(0, 5), 2);
    square.addHole(circular0);
    square.addHole(circular1);
    square.addHole(circular2);
    square.addHole(circular3);

    square.generateSeedPoints(PointGenerator(functions::random_double(0, 10), functions::random_double(0, 10)), 10, 10);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleVoronoiGenerator generator(seeds, square);
    Mesh<Polygon> m = generator.getMesh();
    m.printInFile("SwissCheeseMesh.txt");

}