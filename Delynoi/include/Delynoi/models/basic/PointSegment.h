#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#ifndef DELYNOI_POINTSEGMENT_H
#define DELYNOI_POINTSEGMENT_H

#include <Delynoi/models/basic/Point.h>
#include <Delynoi/models/basic/Segment.h>

namespace Delynoi {
    /*
     * This class models a segment which endpoints are represented by the points directly.
     */
    class PointSegment : public Segment<Point> {
    public:
        /*
         * Constructor. Creates a segment with two endpoints.
         */
        PointSegment(Point p1, Point p2);

        /*
         * Constructor. Creates an empty segment.
         */
        PointSegment();

        /*
         * @return the length of the segment
         */
        double length();

        /*
         * Determines whether a point is contained in the segment.
         * @param point  point to check
         * @return whether the point is contained or not
         */
        bool contains(Point point);

        /*
        * Returns the string representation of the segment.
        * @return string representing the segment as a pair
        */
        std::string getString() const override;

        /*
       * @return angle of the line segment in degrees.
       */
        double cartesianAngle();

        /* Equality operator.
         * @param other segment to compare
         * @return are the two segments equal or not
         */
        bool operator==(const PointSegment &other) const;
    };
}

#endif
#pragma clang diagnostic pop
