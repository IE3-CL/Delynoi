#include <Delynoi/models/basic/PointSegment.h>

using namespace Delynoi;

PointSegment::PointSegment(const Point &p1, const Point &p2)
    : Segment(p1, p2) {
}

PointSegment::PointSegment() = default;

bool PointSegment::contains(const Point &point) const {
    return Segment::contains(point, p1, p2);
}

double PointSegment::length() const {
    return Segment::length(this->p1, this->p2);
}

std::string PointSegment::getString() const {
    return this->getFirst().getString() + " " + this->getSecond().getString();
}

double PointSegment::cartesianAngle() const {
    return Segment::cartesianAngle(this->p1, this->p2);
}

bool PointSegment::operator==(const PointSegment &other) const {
    return getFirst() == other.getFirst() && getSecond() == other.getSecond() ||
           getFirst() == other.getSecond() && getSecond() == other.getFirst();
}
