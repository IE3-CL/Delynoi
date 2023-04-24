#ifndef DELYNOI_CIRCLE_H
#define DELYNOI_CIRCLE_H

#include <Delynoi/models/basic/Point.h>
#include <Delynoi/utilities/delynoi_utilities.h>
#include <Delynoi/utilities/geometryFunctions.h>
#include <cmath>
#include <cstdlib>
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
        Circle(double r, Point c);

        /* Generates points that represent the boundary of the circle
         * @return list of points that model the circle boundary
         */
        std::vector<Point> discretizeCircle();
    };
} // namespace Delynoi

#endif
