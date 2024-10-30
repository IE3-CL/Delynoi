#include <Delynoi/models/polygon/BoundingBox.h>

using namespace Delynoi;

BoundingBox::BoundingBox(const Point &p1, const Point &p2) {
    this->p1 = p1;
    this->p2 = p2;
}

Point BoundingBox::getFirst() const {
    return this->p1;
}

Point BoundingBox::getSecond() const {
    return this->p2;
}

double BoundingBox::getWidth() const {
    return std::abs(p1.getX() - p2.getX());
}

double BoundingBox::getHeight() const {
    return std::abs(p1.getY() - p2.getY());
}

double BoundingBox::xMin() const {
    return std::min(p1.getX(), p2.getX());
}

double BoundingBox::yMin() const {
    return std::min(p1.getY(), p2.getY());
}

double BoundingBox::xMax() const {
    return std::max(p1.getX(), p2.getX());
}

double BoundingBox::yMax() const {
    return std::max(p1.getY(), p2.getY());
}

bool BoundingBox::operator==(const BoundingBox &other) const {
    return getFirst() == other.getFirst() && getSecond() == other.getSecond() ||
           getSecond() == other.getFirst() && getFirst() == other.getSecond();
}

void BoundingBox::getSegments(std::vector<PointSegment> &segments) {
    Point p3(p2.getX(), p1.getY());
    Point p4(p1.getX(), p2.getY());

    segments.emplace_back(p1, p3);
    segments.emplace_back(p3, p2);
    segments.emplace_back(p2, p4);
    segments.emplace_back(p4, p1);
}

bool BoundingBox::contains(const Point &p) const {
    return p.getX() >= xMin() && p.getX() <= xMax() && p.getY() >= yMin() && p.getY() <= yMax();
}
