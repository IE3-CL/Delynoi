#include <Delynoi/models/basic/Point.h>
#include <Delynoi/utilities/delynoi_utilities.h>
#include <algorithm>
#include <vector>

// ReSharper disable once CppEnforceNestedNamespacesStyle
namespace Delynoi { // Nested namespaces requires C++ std17. This is 14+ NOLINT(*-concat-nested-namespaces)
    namespace convex {
        struct PointComparator {
            bool operator()(const Point &p1, const Point &p2) const {
                if (p1.getX() == p2.getX()) {
                    return p1.getY() < p2.getY();
                }

                return p1.getX() < p2.getX();
            }
        } comparator;

        void convexHull(std::vector<Point> &points, std::vector<Point> &upper, std::vector<Point> &lower) {
            std::sort(points.begin(), points.end(), comparator);
            for (auto &point: points) {

                while (upper.size() > 1 && delynoi_utilities::orientation(upper[upper.size() - 2], upper[upper.size() - 1], point) >= 0) {
                    upper.pop_back();
                }

                while (lower.size() > 1 && delynoi_utilities::orientation(lower[lower.size() - 2], lower[lower.size() - 1], point) <= 0) {
                    lower.pop_back();
                }

                upper.push_back(point);
                lower.push_back(point);
            }
        }

        std::vector<std::pair<Point, Point>> rotatingCalipers(std::vector<Point> &points) {
            std::vector<Point> u;
            std::vector<Point> l;
            convexHull(points, u, l);

            std::vector<std::pair<Point, Point>> pairs;

            int i = 0, j = l.size() - 1;
            while (i < u.size() - 1 || j > 0) {
                pairs.emplace_back(u[i], l[j]);

                if (i == u.size() - 1)
                    j--;
                else if (j == 0)
                    i++;
                else if ((u[i + 1].getY() - u[i].getY()) * (l[j].getX() - l[j - 1].getX()) > (l[j].getY() - l[j - 1].getY()) * (u[i + 1].getX() - u[i].getX()))
                    i++;
                else
                    j--;
            }

            return pairs;
        }
    } // namespace convex
} // namespace Delynoi