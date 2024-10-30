#include <Delynoi/models/neighbourhood/SegmentMap.h>
#include <Delynoi/models/polygon/Polygon.h>
#include <Delynoi/utilities/convexHull.h>
#include <Delynoi/utilities/delynoi_utilities.h>
#include <Delynoi/utilities/geometryFunctions.h>

using namespace Delynoi;

Polygon::Polygon(std::vector<int> &points, const std::vector<Point> &p) {
    if (isSelfIntersecting(p)) {
        throw std::invalid_argument("Self intersecting polygons are not supported");
    }

    this->points.assign(points.begin(), points.end());
    this->centroid = Point();
    calculateHash();
}

void Polygon::mutate(const std::vector<Point> &p) {
    this->points.clear();
    delynoi_utilities::TrivialIndexVector(this->points, p.size());

    if (isSelfIntersecting(p)) {
        throw std::invalid_argument("Self intersecting polygons are not supported");
    }

    this->centroid = Point();
    calculateHash();
}

Polygon::Polygon(const std::vector<Point> &p) {
    if (isSelfIntersecting(p)) {
        throw std::invalid_argument("Self intersecting polygons are not supported");
    }

    delynoi_utilities::TrivialIndexVector(this->points, p.size());

    std::vector<Point> this_points;
    this_points.reserve(points.size());
    for (const int point: points) {
        this_points.push_back(p[point]);
    }

    this->centroid = Point();
    calculateHash();
}

Polygon::Polygon() = default;

Polygon::Polygon(const Polygon &obj) {
    this->area = obj.area;
    this->diameter = obj.diameter;
    this->centroid = obj.centroid;

    this->points.assign(obj.points.begin(), obj.points.end());
    calculateHash();
}

double Polygon::calculateDiameter(std::vector<Point> &p) {
    std::vector<std::pair<Point, Point>> rotatingCalipers = convex::rotatingCalipers(p);
    double max = -1;

    for (auto &rotatingCaliper: rotatingCalipers) {
        const double distance = delynoi_utilities::norm(rotatingCaliper.first - rotatingCaliper.second);
        if (distance > max) {
            max = distance;
        }
    }

    return max;
}

double Polygon::calculateArea(const std::vector<Point> &p) const {
    return geometry_functions::area(p, this->points);
}

double Polygon::getArea(const std::vector<Point> &_points) {
    if (this->area == -1) {
        this->area = this->calculateArea(_points);
    }

    return this->area;
}

double Polygon::getDiameter(const std::vector<Point> &_points) {
    if (this->diameter < 0) {
        std::vector<Point> thisPoints = this->getPoints(_points);
        this->diameter = calculateDiameter(thisPoints);
    }

    return this->diameter;
}

Point Polygon::getCentroid(const std::vector<Point> &_points) {
    if (!this->centroid.isValid()) {
        this->centroid = this->calculateCentroid(_points);
    }

    return this->centroid;
}

double Polygon::signedArea(const std::vector<Point> &p) const {
    double _area = 0;
    const int n = static_cast<int>(this->points.size());

    for (int i = 0; i < n; i++) {
        _area += p[points[i]].getX() * p[points[(i + 1) % n]].getY() - p[points[(i + 1) % n]].getX() * p[points[i]].getY();
    }

    return 0.5 * _area;
}

void Polygon::getSegments(std::vector<IndexSegment> &segments) const {
    const int n = static_cast<int>(this->points.size());

    for (int i = 0; i < n; i++) {
        IndexSegment s(this->points[i % n], this->points[(i + 1) % n]);
        segments.push_back(s);
    }
}

Point Polygon::calculateCentroid(const std::vector<Point> &p) const {
    const int n = this->points.size();
    double partial_x = 0;
    double partial_y = 0;

    for (int i = 0; i < n; i++) {
        Point pi = p[points[i]];
        Point pi1 = p[points[(i + 1) % n]];

        partial_x += (pi.getX() + pi1.getX()) * (pi.getX() * pi1.getY() - pi1.getX() * pi.getY());
        partial_y += (pi.getY() + pi1.getY()) * (pi.getX() * pi1.getY() - pi1.getX() * pi.getY());
    }

    const double A = this->signedArea(p);
    double cX = partial_x / (6 * A);
    double cY = partial_y / (6 * A);

    return {cX, cY};
}

bool Polygon::containsPoint(const std::vector<Point> &p, const Point &point) const {
    int j = points.size() - 1;
    bool oddNodes = false;

    for (int i = 0; i < points.size(); i++) {
        Point pI = p[points[i]];
        Point pJ = p[points[j]];

        if (pI == pJ) {
            continue;
        }

        if (pI.getY() <= point.getY() && pJ.getY() > point.getY() || pJ.getY() <= point.getY() && pI.getY() > point.getY()) {

            if (pI.getX() + (point.getY() - pI.getY()) / (pJ.getY() - pI.getY()) * (pJ.getX() - pI.getX()) < point.getX()) {
                oddNodes = !oddNodes;
            }
        }
        j = i;
    }

    if (oddNodes) {
        return true;
    }

    return inEdges(p, point);
}

IndexSegment Polygon::containerEdge(const std::vector<Point> &p, const Point &point) const {
    std::vector<IndexSegment> segments;
    this->getSegments(segments);

    for (auto &segment: segments) {
        if (segment.contains(p, point)) {
            return segment;
        }
    }

    return {-1, -1};
}

bool Polygon::inEdges(const std::vector<Point> &p, const Point &point) const {
    const IndexSegment container = containerEdge(p, point);

    return container.getFirst() != -1 && container.getSecond() != -1;
}

bool Polygon::isConvex(const std::vector<Point> &p) const {
    const int n = static_cast<int>(this->points.size());

    const double determinant = delynoi_utilities::orientation(p[this->points[0]], p[this->points[1]], p[this->points[2]]);

    for (int i = 1; i < n; i++) {
        const double newResult = delynoi_utilities::orientation(
                p[this->points[i]],
                p[this->points[(i + 1) % n]],
                p[this->points[(i + 2) % n]]);
        if (determinant * newResult < 0) {
            return false;
        }
    }

    return true;
}

std::vector<int> Polygon::getPoints() const {
    return this->points;
}

std::vector<int> &Polygon::getPoints() {
    return this->points;
}

int Polygon::numberOfSides() const {
    return static_cast<int>(points.size());
}

bool Polygon::isClockwise(const std::vector<Point> &p) const {
    const int n = static_cast<int>(points.size());

    Point pI = p[points[0]];
    Point pI1 = p[points[n - 1]];

    double sum = (pI.getX() - pI1.getX()) * (pI.getY() + pI1.getY());

    for (int i = 0; i < n - 1; i++) {
        pI1 = p[points[(i + 1) % n]];
        pI = p[points[i]];

        sum += (pI1.getX() - pI.getX()) * (pI1.getY() + pI.getY());
    }

    return sum > 0;
}

bool Polygon::operator==(const Polygon &other) const {
    return this->hash == other.hash;
}

std::string Polygon::getString() {
    std::string base = utilities::toString<double>(this->points.size());

    for (const int point: this->points) {
        base += " " + utilities::toString<double>(point);
    }

    return base;
}

bool Polygon::isVertex(const int index) {
    return std::find(points.begin(), points.end(), index) != points.end();
}

void Polygon::calculateHash() {
    std::size_t _hash = 0;

    for (const int point: points) {
        _hash += utilities::hash32(point);
    }

    this->hash = _hash;
}

void Polygon::fixCCW(const std::vector<Point> &p) {
    if (isClockwise(p)) {
        std::reverse(this->points.begin(), this->points.end());
        this->area = -1;
    }
}

std::vector<Point> Polygon::getPoints(const std::vector<Point> &p) {
    std::vector<Point> returnPoints;

    returnPoints.reserve(this->points.size());
    for (const int point: this->points) {
        returnPoints.push_back(p[point]);
    }

    return returnPoints;
}

bool Polygon::operator<(const Polygon &other) const {
    return this->hash < other.hash;
}

bool Polygon::isSelfIntersecting(const std::vector<Point> &_points) const {
    std::vector<IndexSegment> segments;
    this->getSegments(segments);
    const int n = segments.size();
    Point intersection;

    for (int i = 0; i < n; ++i) {
        const IndexSegment &s = segments[i];

        for (int j = 0; j < n; ++j) {
            if (i == j || j == (i - 1 + n) % n || j == (i + 1) % n) {
                continue;
            }

            if (s.intersection(_points, segments[j], intersection)) {
                return true;
            }
        }
    }
    return false;
}

bool Polygon::containsEdge(const IndexSegment &s) const {
    const int n = this->numberOfSides();

    const int i = utilities::indexOf(this->points, s.getFirst());
    const int j = utilities::indexOf(this->points, s.getSecond());

    return i != -1 && j != -1 && (std::abs(i - j) == 1 || std::abs(i - j) == n - 1);
}

Point Polygon::getAverage(const std::vector<Point> &p) {
    double x = 0;
    double y = 0;

    for (const int v: points) {
        Point vertex = p[v];

        x += vertex.getX();
        y += vertex.getY();
    }

    x = x / this->numberOfSides();
    y = y / this->numberOfSides();

    return {x, y};
}

double Polygon::getMaxDistance(const std::vector<Point> &points) const {
    const int n = this->points.size();
    double maxEdge = LLONG_MIN;

    for (int i = 0; i < this->points.size(); ++i) {
        const double distance = IndexSegment(this->points[i], this->points[(i + 1) % n]).length(points);
        if (distance > maxEdge) {
            maxEdge = distance;
        }
    }

    return maxEdge;
}
