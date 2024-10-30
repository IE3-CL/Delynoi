#ifndef DELYNOI_POLYGONALHOLE_H
#define DELYNOI_POLYGONALHOLE_H

#include <Delynoi/models/hole/Hole.h>
#include <Delynoi/models/polygon/Polygon.h>
#include <vector>

namespace Delynoi {
    /*
     * Class modeling a polygonal hole.
     */
    class PolygonalHole final : public Hole, public Polygon {
    public:
        /*
         * Constructor.
         */
        explicit PolygonalHole(std::vector<Point> &p);
    };

} // namespace Delynoi

#endif
