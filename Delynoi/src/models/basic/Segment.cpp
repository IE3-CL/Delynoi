#include <Delynoi/config/DelynoiConfig.h>
#include <Delynoi/models/basic/Segment.h>

#include <cmath>

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
bool Segment<T>::contains(const Point &point, const Point &_p1, const Point &_p2) const {
    const DelynoiConfig *config = DelynoiConfig::instance();

    bool test1 = ((point.getX() >= _p1.getX() || std::abs(point.getX() - _p1.getX()) < config->getTolerance()) &&
                  (point.getX() <= _p2.getX() || std::abs(point.getX() - _p2.getX()) < config->getTolerance())) ||
                 ((point.getX() >= _p2.getX() || std::abs(point.getX() - _p2.getX()) < config->getTolerance()) &&
                  (point.getX() <= _p1.getX() || std::abs(point.getX() - _p1.getX()) < config->getTolerance()));
    bool test2 = (point.getY() >= _p1.getY() || std::abs(point.getY() - _p1.getY()) < config->getTolerance()) && (point.getY() <= _p2.getY() || std::abs(point.getY() - _p2.getY()) < config->getTolerance()) || ((point.getY() >= _p2.getY() || std::abs(point.getY() - _p2.getY()) < config->getTolerance()) && (point.getY() <= _p1.getY() || std::abs(point.getY() - _p1.getY()) < config->getTolerance()));

    return test1 && test2 &&
           std::abs(_p1.getX() * (_p2.getY() - point.getY()) + _p2.getX() * (point.getY() - _p1.getY()) + point.getX() * (_p1.getY() - _p2.getY())) < config->getTolerance();
}

template<class T>
bool Segment<T>::isVertex(T p) {
    return this->p1 == p || this->p2 == p;
}

template<class T>
double Segment<T>::cartesianAngle(const Point &_p1, const Point &_p2) {
    const double dY = _p2.getY() - _p1.getY();
    const double dX = _p2.getX() - _p1.getX();

    return utilities::degrees(atan2(dY, dX));
}

template<class T>
bool Segment<T>::intersects(const Point &_p1, const Point &_p2, const Point &o1, const Point &o2, Point &inter) {
    const double tolerance = DelynoiConfig::instance()->getTolerance();

    const double s1_x = _p2.getX() - _p1.getX();
    const double s1_y = _p2.getY() - _p1.getY();
    const double s2_x = o2.getX() - o1.getX();
    const double s2_y = o2.getY() - o1.getY();

    const double s = (-s1_y * (_p1.getX() - o1.getX()) + s1_x * (_p1.getY() - o1.getY())) / (-s2_x * s1_y + s1_x * s2_y);

    if (const double t = (s2_x * (_p1.getY() - o1.getY()) - s2_y * (_p1.getX() - o1.getX())) / (-s2_x * s1_y + s1_x * s2_y); s >= 0 - tolerance && s <= 1 + tolerance && t >= 0 - tolerance && t <= 1 + tolerance) {
        const double i_x = _p1.getX() + t * s1_x;
        const double i_y = _p1.getY() + t * s1_y;

        inter.setX(i_x);
        inter.setY(i_y);

        return true;
    }

    return false;
}

template<class T>
bool Segment<T>::intersectionInfinite(const Point _p1, const Point _p2, const Point o1, const Point o2, Point &inter) {
    const double tolerance = DelynoiConfig::instance()->getTolerance();

    const double s1_x = _p2.getX() - _p1.getX();
    const double s1_y = _p2.getY() - _p1.getY();
    const double s2_x = o2.getX() - o1.getX();
    const double s2_y = o2.getY() - o1.getY();

    if (const double t = (s2_x * (_p1.getY() - o1.getY()) - s2_y * (_p1.getX() - o1.getX())) / (-s2_x * s1_y + s1_x * s2_y); t <= 1 + tolerance && t >= 0 - tolerance) {
        const double i_x = _p1.getX() + t * s1_x;
        const double i_y = _p1.getY() + t * s1_y;

        inter.setX(i_x);
        inter.setY(i_y);

        return true;
    }

    return false;
}

template<class T>
double Segment<T>::length(const Point &_p1, const Point &_p2) {
    return std::sqrt(std::pow(_p1.getX() - _p2.getX(), 2) + std::pow(_p1.getY() - _p2.getY(), 2));
}

// ReSharper disable once CppRedundantQualifier
template class Delynoi::Segment<int>; // Fix explicit instantiation for MacOS

// ReSharper disable once CppRedundantQualifier
template class Delynoi::Segment<Point>; // Fix explicit instantiation for MacOS
