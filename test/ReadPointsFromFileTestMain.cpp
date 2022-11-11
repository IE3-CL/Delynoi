#include <vector>
#include <Delynoi/models/basic/Point.h>
#include <Delynoi/models/Region.h>
#include <Delynoi/voronoi/TriangleVoronoiGenerator.h>

using namespace Delynoi;

int main() {
    std::vector<Point> square_points = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Region square(square_points);

    square.addSeedsFromFile("points_file.txt");
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleVoronoiGenerator generator(seeds, square);
    Mesh<Polygon> m = generator.getMesh();
    m.printInFile("ReadFromFileMesh.txt");
}