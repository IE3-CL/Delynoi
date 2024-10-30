#include <Delynoi/config/DelynoiConfig.h>
#include <Delynoi/models/basic/Point.h>
#include <Delynoi/models/basic/PointSegment.h>
#include <Delynoi/utilities/delynoi_utilities.h>

namespace Delynoi::geometry_functions {
    double area2(const Point &p1, const Point &p2, const Point &p3) {
        const Point v1 = p2 - p1;
        const Point v2 = p3 - p1;

        return delynoi_utilities::crossProduct(v1, v2);
    }

    bool collinear(const Point &p1, const Point &p2, const Point &p3) {
        const DelynoiConfig *config = DelynoiConfig::instance();

        return std::abs(area2(p1, p2, p3)) < config->getTolerance();
    }

    bool collinear(const PointSegment &seg1, const PointSegment &seg2) {
        return collinear(seg1.getFirst(), seg1.getSecond(), seg2.getFirst()) &&
               collinear(seg1.getFirst(), seg1.getSecond(), seg2.getSecond());
    }

    double triangleArea(const Point &p1, const Point &p2, const Point &origin) {
        return area2(p1, p2, origin) / 2.0;
    }

    double area(const std::vector<Point> &points, const std::vector<int> &index) {
        double area = 0.0;
        const int n = static_cast<int>(index.size());

        for (int i = 0; i < n; i++) {
            area += triangleArea(points[index[i % n]], points[index[(i + 1) % n]], points[index[0]]);
        }

        return area;
    }

    double area(const std::vector<Point> &points) {
        double area = 0.0;
        const int n = static_cast<int>(points.size());

        for (int i = 0; i < n; i++) {
            area += triangleArea(points[i % n], points[(i + 1) % n], points[0]);
        }

        return area;
    }
} // namespace Delynoi::geometry_functions