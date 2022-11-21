#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#ifndef DELYNOI_POINTMAP_H
#define DELYNOI_POINTMAP_H

#include <map>
#include <vector>
#include <Delynoi/models/basic/Point.h>
#include <Delynoi/models/neighbourhood/NeighboursByPoint.h>
#include <fstream>

namespace Delynoi {
    /*
     * Class that models the neighbourhood by point relationship, keeping a map that relates each mesh point to all polygons
     * that contain it.
     */
    class PointMap {
    protected:
        /*
         * Map that relates points and the polygons that contain it (as a NeighboursByPoint instance)
         */
        std::map<Point, NeighboursByPoint> map;
    public:
        /*
         * Constructor
         */
        PointMap();

        /*
         * Destructor
         */
        ~PointMap();

        /*
         * Inserts a new point to the map, including a polygon that contains it
         * @param p point to insert
         * @param neighbour index of a polygon that contains the point
         */
        void insert(Point p, int neighbour);

        /*
         * Inserts a new point to the map, including a list of the polygons that contain it
         * @param p point to insert
         * @param neighbours list of the indexes of polygons that contain the point
         */
        void insert(Point &p, std::vector<int> &neighbours);

        /*
         * @param p point to lookup
         * @return all polygons that contain point p
         */
        NeighboursByPoint &get(Point p);

        /*
         * @return map that contains all relationship information
         */
        std::map<Point, NeighboursByPoint> &getMap();

        /*
         * @return number of elements of the map
         */
        int size();

        /* Prints the map to a file relative to user path
         * @param fileName name of the file to print
         */
        void printInFile(const std::string &fileName);

        /* Prints the map to a file relative to absolute path
         * @param fileName name of the file to print
         */
        void printInPath(const std::string &path);
    };
}

#endif
#pragma clang diagnostic pop
