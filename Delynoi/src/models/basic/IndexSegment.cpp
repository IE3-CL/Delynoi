#include <Delynoi/models/basic/IndexSegment.h>
#include <Delynoi/utilities/delynoi_utilities.h>

using namespace Delynoi;

IndexSegment::IndexSegment(const int i1, const int i2)
    : Segment(i1, i2) {
    this->hash = utilities::hash32(i1) + utilities::hash32(i2);
}

IndexSegment::IndexSegment(const IndexSegment &other)
    : Segment(other) {
    this->p1 = other.p1;
    this->p2 = other.p2;

    this->hash = utilities::hash32(this->p1) + utilities::hash32(this->p2);
}

IndexSegment::IndexSegment() = default;

bool IndexSegment::contains(const std::vector<Point> &p, const Point &point) const {
    return Segment::contains(point, p[this->p1], p[this->p2]);
}

bool IndexSegment::contains(const std::vector<Point> &p, const IndexSegment &s) const {
    return this->contains(p, p[s.getFirst()]) && this->contains(p, p[s.getSecond()]);
}

Point IndexSegment::middlePoint(const std::vector<Point> &p) const {
    return {(p[this->p1].getX() + p[this->p2].getX()) / 2, (p[this->p1].getY() + p[this->p2].getY()) / 2};
}

double IndexSegment::cartesianAngle(const std::vector<Point> &p) const {
    return Segment::cartesianAngle(p[this->p1], p[this->p2]);
}

bool IndexSegment::intersection(const std::vector<Point> &points, const PointSegment &other, Point &inter) const {
    return intersects(points[this->p1], points[this->p2], other.getFirst(), other.getSecond(), inter);
}

bool IndexSegment::intersection(const std::vector<Point> &points, const IndexSegment &other, Point &inter) const {
    return intersects(points[this->p1], points[this->p2], points[other.getFirst()], points[other.getSecond()], inter);
}

void IndexSegment::orderCCW(const std::vector<Point> &points, const Point &center) {
    if (!this->isCCW(points, center)) {
        const int tmp = this->p1;
        this->p1 = this->p2;
        this->p2 = tmp;
    }
}

bool IndexSegment::isCCW(const std::vector<Point> &points, const Point &center) const {
    const Point p1 = points[this->p1];
    const Point p2 = points[this->p2];

    return delynoi_utilities::orientation(p1, p2, center) > 0;
}

std::string IndexSegment::getString() const {
    return utilities::toString<double>(this->getFirst()) + " " + utilities::toString<double>(this->getSecond());
}

bool IndexSegment::operator==(const IndexSegment &other) const {
    return getFirst() == other.getFirst() && getSecond() == other.getSecond() ||
           getFirst() == other.getSecond() && getSecond() == other.getFirst();
}

bool IndexSegment::operator<(const IndexSegment &other) const {
    if (this->p1 == other.p1) {
        return this->p2 < other.p2;
    }

    return this->p1 < other.p1;
}

double IndexSegment::length(const std::vector<Point> &points) const {
    return Segment::length(points[this->p1], points[this->p2]);
}

bool IndexSegment::isContained(const PointSegment &s, const std::vector<Point> &p) const {
    return s.contains(p[this->p1]) && s.contains(p[this->p2]);
}

IndexSegment IndexSegment::add(const int o) const {
    return {this->p1 + o, this->p2 + o};
}
