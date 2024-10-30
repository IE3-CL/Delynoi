#include <Delynoi/config/DelynoiConfig.h>
#include <Delynoi/models/basic/Point.h>
#include <cmath>
#include <vector>

// ReSharper disable once CppEnforceNestedNamespacesStyle
namespace Delynoi { // Nested namespaces requires C++ std17. This is 14+ NOLINT(*-concat-nested-namespaces)
    namespace delynoi_utilities {
        void TrivialIndexVector(std::vector<int> &index_vector, const int n) {
            for (int i = 0; i < n; i++) {
                index_vector.push_back(i);
            }
        }

        double crossProduct(const Point &a, const Point &b) {
            return a.getX() * b.getY() - a.getY() * b.getX();
        }

        double squareNorm(const Point &p) {
            return pow(p.getX(), 2) + pow(p.getY(), 2);
        }

        double norm(const Point &p) {
            return sqrt(squareNorm(p));
        }

        double orientation(const Point &p, const Point &q, const Point &r) {
            return crossProduct(q - p, r - p);
        }

        std::vector<Point> generateArcPoints(const Point &center, const double radius, const double initAngle, const double endAngle) {
            std::vector<Point> arcPoints;

            const int steps = DelynoiConfig::instance()->getDiscretizationGrade();
            const double delta = (endAngle - initAngle) / steps;

            for (int i = 0; i <= steps; i++) {
                const double angle = initAngle + delta * i;

                const double x = center.getX() + radius * std::cos(utilities::radian(angle));
                const double y = center.getY() + radius * std::sin(utilities::radian(angle));

                Point point(x, y);
                arcPoints.push_back(point);
            }

            return arcPoints;
        }

        void checkTriangleIntegrity(const std::vector<int> &trianglePoints) {
            if (trianglePoints.size() != 3 || trianglePoints[0] == trianglePoints[1] || trianglePoints[1] == trianglePoints[2] || trianglePoints[2] == trianglePoints[0]) {
                throw std::invalid_argument("Invalid triangle detected. Stopping meshing.");
            }
        }
    } // namespace delynoi_utilities
} // namespace Delynoi