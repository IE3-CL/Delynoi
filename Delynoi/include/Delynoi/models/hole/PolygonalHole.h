#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#ifndef DELYNOI_POLYGONALHOLE_H
#define DELYNOI_POLYGONALHOLE_H

#include <vector>
#include <Delynoi/models/polygon/Polygon.h>
#include <Delynoi/models/hole/Hole.h>

namespace Delynoi {
/*
 * Class modeling a polygonal hole.
 */
    class PolygonalHole : public Hole, public Polygon {
    public:
        /*
         * Constructor.
         */
        explicit PolygonalHole(std::vector<Point> &p);
    };

}

#endif
#pragma clang diagnostic pop
