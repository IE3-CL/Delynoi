#include <Delynoi/models/generator/Functor.h>
#include <Delynoi/models/basic/Point.h>
#include <Delynoi/models/Region.h>
#include <Delynoi/voronoi/TriangleVoronoiGenerator.h>

using namespace Delynoi;

class CustomGenerator : public Functor {
    inline double apply(double x) {
        return x / 2;
    }
};

int main() {
    std::vector<Point> square_points = {Point(0, 0), Point(10, 0), Point(10, 10), Point(0, 10)};
    Region square(square_points);

    square.generateSeedPoints(PointGenerator(new CustomGenerator(), new CustomGenerator()), 10, 10);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleVoronoiGenerator generator(seeds, square);
    Mesh<Polygon> m = generator.getMesh();
    m.printInFile("CustomGeneratorMesh.txt");
}