#include <Delynoi/models/hole/CircularHole.h>
#include <Delynoi/models/polygon/Polygon.h>
#include <Delynoi/utilities/delynoi_utilities.h>

using namespace Delynoi;

CircularHole::CircularHole(const Point &p, const double r)
    : Circle(r, p) {
    this->HolePoints = discretizeCircle();
    Hole::center = Circle::center;
    computeSegments();
}

void CircularHole::computeSegments() {
    std::vector<int> indexes;
    delynoi_utilities::TrivialIndexVector(indexes, static_cast<int>(this->HolePoints.size()));

    const Polygon discretePolygon(indexes, this->HolePoints);
    discretePolygon.getSegments(this->segments);
}
