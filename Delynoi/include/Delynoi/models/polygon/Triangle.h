#ifndef DELYNOI_TRIANGLE_H
#define DELYNOI_TRIANGLE_H

#include <Delynoi/models/neighbourhood/EdgeData.h>
#include <Delynoi/models/polygon/Polygon.h>
#include <Delynoi/utilities/UniqueList.h>
#include <Delynoi/voronoi/structures/mapdata.h>
#include <unordered_map>

namespace Delynoi {
    /*
     * Class that models a triangle, which, differently from an arbitrary polygon, has a circumcenter.
     */
    class Triangle : public Polygon {
    private:
        /*
         * Circumcenter of the triangle
         */
        Point circumcenter;

        int circumcenterIndex{};

        /*
         * Calculates the circumcenter
         * @param p mesh points
         * @return triangle circumcenter
         */
        Point calculateCircumcenter(const std::vector<Point> &p) const;

    public:
        /*
         * Default constructor
         */
        Triangle();

        /*
         * Constructor
         */
        Triangle(std::vector<int> points, const std::vector<Point> &p);

        Triangle(std::vector<int> points, const std::vector<Point> &p, UniqueList<Point> &circumcenters);

        Triangle(std::vector<int> points, const std::vector<Point> &p, std::vector<Point> &circumcenters);

        /*
         * @return circumcenter of the triangle
         */
        Point getCircumcenter() const;

        int getCircumcenterIndex() const;

        /*
         * Given an EdgeData instance and a point, determines the next edge that is to be used in the computation of the
         * Voronoi diagram.
         * @param center center of the voronoi cell (point around which we will rotate)
         * @param edge current edge from which we will obtain the next one
         * @param edgeMap map with the information relating edge endpoints and EdgeData indexes
         * @return index of the next EdgeData for the Voronoi diagram computation
         */
        int nextEdge(int center, EdgeData edge, std::unordered_map<Key, int, KeyHasher> &edgeMap) const;

        /*
         * Given an edge, it determines the point of the triangle not contained in it
         * @param edge edge to operate on
         * @return index (in the mesh points list) of the point not contained in the edge
         */
        int thirdPoint(EdgeData edge) const;

        /*
         * @return is the triangle valid (have its endpoints been set)
         */
        bool isNull() const;
    };
} // namespace Delynoi

#endif
