#include <delynoi/models/hole/PolygonalHole.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

PolygonalHole::PolygonalHole(std::vector<Point> &p) : Polygon(p) {
    for (int i = 0; i < p.size(); i++) {
        this->HolePoints.push_back(p.at(i));
    }
    this->center = this->getCentroid(p);
    Polygon::getSegments(this->segments);
}


#pragma clang diagnostic pop