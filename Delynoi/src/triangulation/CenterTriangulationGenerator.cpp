#include <Delynoi/triangulation/CenterTriangulationGenerator.h>

using namespace Delynoi;

std::vector<Triangle> CenterTriangulationGenerator::triangulate(Polygon p, std::vector<Point> &points) {
    if (!p.isConvex(points)) {
        throw std::invalid_argument("Can not use a center triangulation scheme on a non convex polygon");
    }

    const std::vector<int> polyPoints = p.getPoints();
    const int n = polyPoints.size();

    std::vector<Triangle> triangles;
    const Point center = p.getAverage(points);
    points.push_back(center);
    const int centerIndex = points.size() - 1;

    for (int i = 0; i < n; ++i) {
        // ReSharper disable once CppTemplateArgumentsCanBeDeduced
        const std::vector<int> trianglePoints = {polyPoints[i], polyPoints[(i + 1) % n], centerIndex}; // MacOS requires int

        Triangle t(trianglePoints, points);
        triangles.push_back(t);
    }

    return triangles;
}
