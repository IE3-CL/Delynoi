#ifndef DELYNOI_POLYGON_H
#define DELYNOI_POLYGON_H

#include <Delynoi/models/basic/IndexSegment.h>
#include <Delynoi/models/basic/Point.h>
#include <climits>
#include <vector>

namespace Delynoi {
    /*
     * Models a polygon (with an arbitrary number of sides).
     */
    class Polygon {
    protected:
        /*
         * List of the indexes (in the mesh) of the polygon points
         */
        std::vector<int> points;

        /*
         * Pre-calculated polygon properties
         */
        double diameter = -1;
        double area = -1;
        Point centroid;

        /* Calculates the polygon diameter
         * @param p mesh points
         * @return polygon diameter
         */
        static double calculateDiameter(std::vector<Point> &p);

        /* Calculates the polygon area
         * @param p mesh points
         * @return polygon area
         */
        double calculateArea(const std::vector<Point> &p) const;

        /* Calculates the polygon centroid
         * @param p mesh points
         * @return polygon centroid
         */
        Point calculateCentroid(const std::vector<Point> &p) const;

        /*
         * Calculates the polygon hash value
         */
        void calculateHash();

    public:
        /*
         * Constructor. Receives a list of point indexes and the mesh points to create the polygon
         */
        Polygon(std::vector<int> &points, const std::vector<Point> &p);

        /*
         * Constructor. Receives a list of points representing the polygon
         */
        explicit Polygon(const std::vector<Point> &p);

        /*
         * Copy constructor.
         */
        Polygon(const Polygon &obj);

        /*
         * Default constructor.
         */
        Polygon();

        /*
         * @return polygon diameter
         */
        double getDiameter(const std::vector<Point> &_points);

        /*
         * @return polygon area
         */
        double getArea(const std::vector<Point> &_points);

        /*
         * @return polygon centroid
         */
        Point getCentroid(const std::vector<Point> &_points);

        /* Gets the polygon segments and set them in the given vector
         * @param segments vector that will contain the segments
         */
        void getSegments(std::vector<IndexSegment> &segments) const;

        /*
         * @return polygon points indexes list
         */
        std::vector<int> getPoints() const;

        /*
         * @return reference to the polygon points indexes list
         */
        std::vector<int> &getPoints();

        /*
         * @param p mesh points
         * @return polygon point list (Point instances, not their indexes)
         */
        std::vector<Point> getPoints(const std::vector<Point> &p);

        /*
         * @return number of sides of the polygon
         */
        int numberOfSides() const;

        /*
         * Equality operator
         * @param other polygon to compare against
         * @return whether the two polygons are equal or not
         */
        bool operator==(const Polygon &other) const;

        /*
         * Less than operator.
         * @param other polygon to compare against
         * @return whether this polygon is less than the other
         */
        bool operator<(const Polygon &other) const;

        /* Gives a string representation of the polygon, first including the number of sides, followed by the indexes of
         * each point index
         * @return the string representation of the polygon
         */
        std::string getString();

        /* Changes the points defining the polygon, changing the value of the object without destroying this instance
         * @param p points to assign to this polygon
         */
        void mutate(const std::vector<Point> &p);

        /* Determines if a point is inside the polygon
         * @param p mesh points
         * @param point point to check
         * @return whether the point is inside the polygon or not
         */
        bool containsPoint(const std::vector<Point> &p, const Point &point) const;

        /* Determines if a point is in the border of the polygon
         * @param p mesh points
         * @param point point to check
         * @return whether the point is in the border of the polygon or not
         */
        bool inEdges(const std::vector<Point> &p, const Point &point) const;

        /* Calculates the signed area of the polygon (using the counter-clockwise rule)
         * @param p mesh points
         * @return signed polygon area
         */
        double signedArea(const std::vector<Point> &p) const;

        /* Checks if a segment is part of the polygon
         * @param s segment to check
         * @return if the segment is part of the polygon
         */
        bool containsEdge(const IndexSegment &s) const;

        /* Checks if the polygon is convex
         * @param p mesh points
         * @return if the polygon is convex or not
         */
        bool isConvex(const std::vector<Point> &p) const;

        /* Checks if the polygon points are counter or clockwise checking the signed area of the points
         * @param p mesh points
         * @return if the points are ordered clockwise or not
         */
        bool isClockwise(const std::vector<Point> &p) const;

        /* Checks if a given point index is part of the polygon (is a vertex)
         * @param index point index to check
         * @return if the index is a vertex or not
         */
        bool isVertex(int index);

        /* Checks if the polygon self-intersects
         * @param points mesh points
         * @return if the polygon is self-intersecting
         */
        bool isSelfIntersecting(const std::vector<Point> &_points) const;

        /*
         * Hash value of the polygon (calculated using the indexes of the points)
         */
        std::size_t hash = 0;

        /* Checks if the polygon is in counter-clockwise or clockwise, and fixes the order of the point if the second is the
         * case.
         * @param p mesh points
         */
        void fixCCW(const std::vector<Point> &p);

        /* Finds the segment of the polygon that contains a given point
         * @param p mesh points
         * @param point point to use
         * @return segment that contains point
         */
        IndexSegment containerEdge(const std::vector<Point> &p, const Point &point) const;

        /* Gets the average vertex value of the polygon
         * @param p mesh points
         * @return average point
         */
        Point getAverage(const std::vector<Point> &p);

        /* Computes the maximum distance between any two vertexes of the polygon
         * @param points mesh points
         * @return max distance between points of the polygon
         */
        double getMaxDistance(const std::vector<Point> &points) const;
    };
} // namespace Delynoi

#endif
