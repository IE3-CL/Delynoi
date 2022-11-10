#include <delynoi/models/hole/CircularHole.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

using namespace Delynoi;

CircularHole::CircularHole(Point p, double r) : Circle(r, p) {
    this->HolePoints = discretizeCircle();
    Hole::center = Circle::center;
    computeSegments();
}

void CircularHole::computeSegments() {
    std::vector<int> indexes;
    delynoi_utilities::TrivialIndexVector(indexes, (int) this->HolePoints.size());

    Polygon discretePolygon(indexes, this->HolePoints);
    discretePolygon.getSegments(this->segments);
}

#pragma clang diagnostic pop