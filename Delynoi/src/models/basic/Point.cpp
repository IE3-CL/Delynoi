#include <Delynoi/config/DelynoiConfig.h>
#include <Delynoi/models/basic/Point.h>

#include <cmath>

using namespace Delynoi;

Point::Point(const double x, const double y) {
    this->x = x;
    this->y = y;
}

Point::Point() {
    this->x = 0;
    this->y = 0;

    this->isEmpty = true;
}

bool Point::isValid() const {
    return this->isEmpty;
}

double Point::getX() const {
    return this->x;
}

double Point::getY() const {
    return this->y;
}

std::string Point::getString() const {
    return utilities::toString<double>(this->getX()) + " " + utilities::toString<double>(this->getY());
}

double Point::squareNorm() const {
    return pow(this->getX(), 2) + pow(this->getY(), 2);
}

bool Point::operator==(const Point &other) const {
    const DelynoiConfig *config = DelynoiConfig::instance();

    return std::abs(this->x - other.x) < config->getTolerance() &&
           std::abs(this->y - other.y) < config->getTolerance();
}

Point Point::operator-(const Point &other) const {
    return {this->x - other.x, this->y - other.y};
}

bool Point::isInBoundary() const {
    return this->isBoundaryPoint;
}

void Point::setBoundary() {
    this->isBoundaryPoint = true;
}

void Point::setX(const double newX) {
    this->x = newX;
}

void Point::setY(const double newY) {
    this->y = newY;
}

bool Point::operator<(const Point &other) const {
    if (const DelynoiConfig *config = DelynoiConfig::instance();
        std::abs(this->x - other.x) < config->getTolerance()) {
        if (std::abs(this->y - other.y) < config->getTolerance()) {
            return false;
        }
        return this->y < other.y;
    }

    return this->x < other.x;
}
