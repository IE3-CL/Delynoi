#ifndef DELYNOI_DELAUNAYINFO_H
#define DELYNOI_DELAUNAYINFO_H

#include <Delynoi/models/polygon/Triangle.h>
#include <Delynoi/voronoi/structures/PointData.h>

namespace Delynoi {
    /*
     * Structure that contains all information about the Delaunay triangulation required for the Voronoi diagram
     * calculation.
     */
    struct DelaunayInfo {
        /*
         * List of Delaunay triangles
         */
        std::vector<Triangle> triangles;

        /*
         * List of points of the Delaunay triangulation
         */
        std::vector<Point> meshPoints;

        /*
         * SegmentMap with the Delaunay neighbourhood information
         */
        SegmentMap *delaunayEdges;

        /*
         * List of PointData (point index and an associated segment index)
         */
        std::vector<PointData> points;

        /*
         * List of the indexes of the points actually used by the Delaunay triangulation (Triangle does not assure unique
         * points when the input is not unique)
         */
        UniqueList<int> realPoints;

        /*
         * List of EdgeData (each edge with its associated incident polygons)
         */
        std::vector<EdgeData> edges;

        /*
         * Map that relates edges endpoints and the index of the corresponding EdgeData
         */
        std::unordered_map<Key, int, KeyHasher> edgeMap;
        UniqueList<Point> circumcenters;

        /*
         * Constructor
         */
        DelaunayInfo(const std::vector<Triangle> &t, const std::vector<Point> &p, SegmentMap *e, const std::vector<PointData> &pD, const UniqueList<int> &rP, const std::vector<EdgeData> &eD, const std::unordered_map<Key, int, KeyHasher> &eM, const UniqueList<Point> &c) {
            triangles = t;
            meshPoints = p;
            delaunayEdges = e;
            points = pD;
            realPoints = rP;
            edges = eD;
            edgeMap = eM;
            circumcenters = c;
        }
    };
} // namespace Delynoi

#endif
