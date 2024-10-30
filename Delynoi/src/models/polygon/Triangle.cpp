#include <Delynoi/models/polygon/Triangle.h>

using namespace Delynoi;

Triangle::Triangle() = default;

Triangle::Triangle(std::vector<int> points, const std::vector<Point> &p)
    : Polygon(points, p) {
    this->circumcenter = this->calculateCircumcenter(p);
}

Triangle::Triangle(std::vector<int> points, const std::vector<Point> &p, UniqueList<Point> &circumcenters)
    : Polygon(points, p) {
    this->circumcenter = this->calculateCircumcenter(p);
    this->circumcenterIndex = circumcenters.push_back(this->circumcenter);
}

Triangle::Triangle(std::vector<int> points, const std::vector<Point> &p, std::vector<Point> &circumcenters)
    : Polygon(points, p) {
    this->circumcenter = this->calculateCircumcenter(p);
    this->circumcenterIndex = circumcenters.size();
    circumcenters.push_back(this->circumcenter);
}

Point Triangle::getCircumcenter() const {
    return this->circumcenter;
}

int Triangle::getCircumcenterIndex() const {
    return this->circumcenterIndex;
}

Point Triangle::calculateCircumcenter(const std::vector<Point> &p) const {
    const Point A = p[this->points[0]];
    const Point B = p[this->points[1]];
    const Point C = p[this->points[2]];

    const double d = 2 * (A.getX() * (B.getY() - C.getY()) + B.getX() * (C.getY() - A.getY()) + C.getX() * (A.getY() - B.getY()));

    double uX = (A.squareNorm() * (B.getY() - C.getY()) + B.squareNorm() * (C.getY() - A.getY()) + C.squareNorm() * (A.getY() - B.getY())) / d;
    double uY = (A.squareNorm() * (C.getX() - B.getX()) + B.squareNorm() * (A.getX() - C.getX()) + C.squareNorm() * (B.getX() - A.getX())) / d;

    return {uX, uY};
}

int Triangle::nextEdge(const int center, const EdgeData edge, std::unordered_map<Key, int, KeyHasher> &edgeMap) const {
    const auto nextEdge = Key(center, thirdPoint(edge));

    return edgeMap[nextEdge];
}

int Triangle::thirdPoint(const EdgeData edge) const {
    if (this->points[0] == edge.p1) {
        if (this->points[1] == edge.p2) {
            return this->points[2];
        }
        return this->points[1];
    }
    if (this->points[1] == edge.p1) {
        if (this->points[0] == edge.p2) {
            return this->points[2];
        }
        return this->points[0];
    }
    if (this->points[0] == edge.p2) {
        return this->points[1];
    }
    return this->points[0];
}

bool Triangle::isNull() const {
    return this->points.empty();
}
