#include <Delynoi/config/DelynoiConfig.h>
#include <Delynoi/models/polygon/Circle.h>
#include <Delynoi/utilities/delynoi_utilities.h>

#include <cmath>

using namespace Delynoi;

Circle::Circle(const double r, const Point &c) {
    this->radius = r;
    this->center = c;
}

std::vector<Point> Circle::discretizeCircle() const {
    const DelynoiConfig *config = DelynoiConfig::instance();

    std::vector<Point> points;
    const double delta = 360.0 / config->getDiscretizationGrade();

    double angle = 0;
    while (angle < 360) {
        double x = center.getX() + radius * cos(utilities::radian(angle));
        double y = center.getY() + radius * sin(utilities::radian(angle));

        points.emplace_back(x, y);

        angle += delta;
    }

    return points;
}
