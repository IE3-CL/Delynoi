#include <Delynoi/models/hole/PolygonalHole.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

using namespace Delynoi;

PolygonalHole::PolygonalHole(std::vector<Point> &p) : Polygon(p) {
    for (auto &i: p) {
        this->HolePoints.push_back(i);
    }
    this->center = this->getCentroid(p);
    Polygon::getSegments(this->segments);
}

#pragma clang diagnostic pop
