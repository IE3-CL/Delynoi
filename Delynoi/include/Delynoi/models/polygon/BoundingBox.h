#ifndef DELYNOI_RECTANGLE_H
#define DELYNOI_RECTANGLE_H

#include <Delynoi/models/basic/Point.h>
#include <Delynoi/models/basic/PointSegment.h>

namespace Delynoi {
    /*
     * Models an axes oriented bounding box (basically, a rectangle).
     */
    class BoundingBox {
    private:
        /*
         * Corners of the rectangle
         */
        Point p1;
        Point p2;

    public:
        /*
         * Constructor
         */
        BoundingBox(const Point &p1, const Point &p2);

        /*
         * @return the first corner of the bounding box
         */
        Point getFirst() const;

        /*
         * @return the second corner of the bounding box
         */
        Point getSecond() const;

        /*
         * @return width of the box
         */
        double getWidth() const;

        /*
         * @return height of the box
         */
        double getHeight() const;

        /*
         * @return x-axis value of the left side of the box
         */
        double xMin() const;

        /*
         * @return y-axis value of the bottom side of the box
         */
        double yMin() const;

        /*
         * @return x-axis value of the right side of the box
         */
        double xMax() const;

        /*
         * @return y-axis value of the top side of the box
         */
        double yMax() const;

        /* Equality operator
         * @param
         * @return
         */
        bool operator==(const BoundingBox &other) const;

        /* Checks if a point is inside the box
         * @param p point to check
         * @return whether the point is inside the box or not
         */
        bool contains(const Point &p) const;

        /* Fills a vector with the segments of the box
         * @param segments vector in which the segments of the box will be kept
         */
        void getSegments(std::vector<PointSegment> &segments);
    };
} // namespace Delynoi

#endif
