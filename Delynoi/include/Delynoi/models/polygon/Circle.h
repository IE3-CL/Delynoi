#ifndef DELYNOI_CIRCLE_H
#define DELYNOI_CIRCLE_H

#include <Delynoi/models/basic/Point.h>
#include <vector>

namespace Delynoi {
    /*
     * Class that models a circle using its center and its radius.
     */
    class Circle {
    protected:
        /*
         * Circle radius
         */
        double radius;
        /*
         * Circle center
         */
        Point center;

    public:
        /*
         * Constructor
         */
        Circle(double r, const Point &c);

        /* Generates points that represent the boundary of the circle
         * @return list of points that model the circle boundary
         */
        std::vector<Point> discretizeCircle() const;
    };
} // namespace Delynoi

#endif
