#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedStructInspection"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#ifndef DELYNOI_SEGMENTMAP_H
#define DELYNOI_SEGMENTMAP_H

#include <Delynoi/voronoi/structures/mapdata.h>
#include <Delynoi/utilities/Pair.h>
#include <unordered_map>
#include <Delynoi/models/neighbourhood/NeighboursBySegment.h>
#include <fstream>
#include <Delynoi/models/basic/IndexSegment.h>

namespace Delynoi {
/*
 * Struct used to compute the hash value of an NeighboursBySegment instance (so it can be used as hash map key)
 */
    struct NeighboursHasher {
        std::size_t operator()(const NeighboursBySegment &k) const {
            return utilities::hash32(k.getFirst()) + utilities::hash32(k.getSecond());
        }
    };

/*
 * Class that models the neighbourhood by segment relationship, keeping a map that relates each mesh segment to all polygons
 * that contain it
 */
    class SegmentMap {
    protected:
        /*
         * Map that relates segments and the polygons that contain it (as a NeighboursBySegment instance)
         */
        std::unordered_map<IndexSegment, NeighboursBySegment, SegmentHasher> map;
    public:
        /*
         * Default constructor
         */
        SegmentMap();

        /* Inserts a new segment on the map, given one of the polygons that contains it
         * @param s segment to insert
         * @param polygonIndex index of the polygon that contains the segment
         */
        void insert(const IndexSegment &s, int polygonIndex);

        /* Inserts a new segment on the map, given a NeighboursBySegment instance
         * @param s segment to insert
         * @param n NeighboursBySegment instance
         */
        void insert(const IndexSegment &s, NeighboursBySegment n);

        /*
         * @param s segment to lookup
         * @return polygons incident to the given segment
         */
        NeighboursBySegment &get(const IndexSegment &s);

        /*
         * @return reference to the map that relates segments and neighbours
         */
        std::unordered_map<IndexSegment, NeighboursBySegment, SegmentHasher> &getMap();

        /*
         * @return map that relates segments and neighbours
         */
        std::unordered_map<IndexSegment, NeighboursBySegment, SegmentHasher> getMap() const;

        /*
         * @return number of elements on the map
         */
        int size();

        /* Prints the map information in a file relative to user path
         * @param fileName name of the file to print
         */
        void printInFile(const std::string &fileName);

        /* Prints the map information in a file relative to absolute path
         * @param fileName name of the file to print
         */
        void printInPath(const std::string &path);

        /* Checks if a given segment is in the map
         * @param s segment to check
         * @return whether the segment is in the map or not
         */
        bool containsSegment(const IndexSegment &s);
    };
}

#endif
#pragma clang diagnostic pop
