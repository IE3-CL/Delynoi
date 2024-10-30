#ifndef DELYNOI_CIRCULARHOLE_H
#define DELYNOI_CIRCULARHOLE_H

#include <Delynoi/models/basic/Point.h>
#include <Delynoi/models/hole/Hole.h>
#include <Delynoi/models/polygon/Circle.h>

namespace Delynoi {
    /*
     * Class modeling a circular hole.
     */
    class CircularHole final : public Hole, public Circle {
    private:
        /*
         * Calculates the segments of the hole based on the radius and center of the circle.
         */
        void computeSegments();

    public:
        /*
         * Constructor.
         */
        CircularHole(const Point &p, double r);
    };
} // namespace Delynoi

#endif
