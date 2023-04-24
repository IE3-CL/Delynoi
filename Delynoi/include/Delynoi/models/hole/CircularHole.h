#ifndef DELYNOI_CIRCULARHOLE_H
#define DELYNOI_CIRCULARHOLE_H

#include <Delynoi/models/basic/Point.h>
#include <Delynoi/models/basic/Segment.h>
#include <Delynoi/models/hole/Hole.h>
#include <Delynoi/models/polygon/Circle.h>
#include <Delynoi/models/polygon/Polygon.h>
#include <vector>

namespace Delynoi {
    /*
     * Class modeling a circular hole.
     */
    class CircularHole : public Hole, public Circle {
    private:
        /*
         * Calculates the segments of the hole based on the radius and center of the circle.
         */
        void computeSegments();

    public:
        /*
         * Constructor.
         */
        CircularHole(Point p, double r);
    };
} // namespace Delynoi

#endif
