#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedLocalVariable"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "UnusedValue"

#include <Delynoi/models/basic/Segment.h>

using namespace Delynoi;

template<class T>
Segment<T>::Segment(T p1, T p2) {
    this->p1 = p1;
    this->p2 = p2;
}

template<class T>
Segment<T>::Segment() = default;

template<class T>
T Segment<T>::getFirst() const {
    return this->p1;
}

template<class T>
T Segment<T>::getSecond() const {
    return this->p2;
}

template<class T>
bool Segment<T>::contains(Point point, Point _p1, Point _p2) {
    DelynoiConfig *config = DelynoiConfig::instance();

    bool test1 = ((point.getX() >= _p1.getX() || std::abs(point.getX() - _p1.getX()) < config->getTolerance()) &&
                  (point.getX() <= _p2.getX() || std::abs(point.getX() - _p2.getX()) < config->getTolerance())) ||
                 ((point.getX() >= _p2.getX() || std::abs(point.getX() - _p2.getX()) < config->getTolerance()) &&
                  (point.getX() <= _p1.getX() || std::abs(point.getX() - _p1.getX()) < config->getTolerance()));
    bool test2 = (
            (point.getY() >= _p1.getY() || std::abs(point.getY() - _p1.getY()) < config->getTolerance()) &&
            (point.getY() <= _p2.getY() || std::abs(point.getY() - _p2.getY()) < config->getTolerance()) ||
            ((point.getY() >= _p2.getY() || std::abs(point.getY() - _p2.getY()) < config->getTolerance()) &&
             (point.getY() <= _p1.getY() || std::abs(point.getY() - _p1.getY()) < config->getTolerance())));

    return test1 && test2 &&
           std::abs(_p1.getX() * (_p2.getY() - point.getY()) + _p2.getX() * (point.getY() - _p1.getY()) + point.getX() * (_p1.getY() - _p2.getY())) < config->getTolerance();
}

template<class T>
bool Segment<T>::isVertex(T p) {
    return this->p1 == p || this->p2 == p;
}

template<class T>
double Segment<T>::cartesianAngle(Point _p1, Point _p2) {
    double dY = _p2.getY() - _p1.getY();
    double dX = _p2.getX() - _p1.getX();

    return utilities::degrees(atan2(dY, dX));
}

template<class T>
bool Segment<T>::intersects(Point _p1, Point _p2, Point o1, Point o2, Point &inter) {
    double tolerance = DelynoiConfig::instance()->getTolerance();

    double s1_x, s1_y, s2_x, s2_y;
    s1_x = _p2.getX() - _p1.getX();
    s1_y = _p2.getY() - _p1.getY();
    s2_x = o2.getX() - o1.getX();
    s2_y = o2.getY() - o1.getY();

    double s, t;
    s = (-s1_y * (_p1.getX() - o1.getX()) + s1_x * (_p1.getY() - o1.getY())) / (-s2_x * s1_y + s1_x * s2_y);
    t = (s2_x * (_p1.getY() - o1.getY()) - s2_y * (_p1.getX() - o1.getX())) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= (0 - tolerance) && s <= (1 + tolerance) && t >= (0 - tolerance) && t <= (1 + tolerance)) {
        double i_x = _p1.getX() + (t * s1_x);
        double i_y = _p1.getY() + (t * s1_y);

        inter.setX(i_x);
        inter.setY(i_y);

        return true;
    }

    return false;
}

template<class T>
bool Segment<T>::intersectionInfinite(Point _p1, Point _p2, Point o1, Point o2, Point &inter) {
    double tolerance = DelynoiConfig::instance()->getTolerance();

    double s1_x, s1_y, s2_x, s2_y;
    s1_x = _p2.getX() - _p1.getX();
    s1_y = _p2.getY() - _p1.getY();
    s2_x = o2.getX() - o1.getX();
    s2_y = o2.getY() - o1.getY();

    double s, t;
    s = (-s1_y * (_p1.getX() - o1.getX()) + s1_x * (_p1.getY() - o1.getY())) / (-s2_x * s1_y + s1_x * s2_y);
    t = (s2_x * (_p1.getY() - o1.getY()) - s2_y * (_p1.getX() - o1.getX())) / (-s2_x * s1_y + s1_x * s2_y);

    if (t <= (1 + tolerance) && t >= (0 - tolerance)) {
        double i_x = _p1.getX() + (t * s1_x);
        double i_y = _p1.getY() + (t * s1_y);

        inter.setX(i_x);
        inter.setY(i_y);

        return true;
    }

    return false;
}

template<class T>
double Segment<T>::length(Point _p1, Point _p2) {
    return std::sqrt(std::pow(_p1.getX() - _p2.getX(), 2) + std::pow(_p1.getY() - _p2.getY(), 2));
}

template
class Delynoi::Segment<int>;

template
class Delynoi::Segment<Point>;

#pragma clang diagnostic pop