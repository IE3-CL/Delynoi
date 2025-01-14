#include <Delynoi/triangulation/EarTriangulationGenerator.h>

using namespace Delynoi;

Triangle EarTriangulationGenerator::getEar(const std::vector<Point> &points, std::vector<int> &pointList) {
    const int size = static_cast<int>(pointList.size());

    if (size < 3) {
        Triangle t;
        return t;
    }

    if (size == 3) {
        Triangle ear({pointList[0], pointList[1], pointList[2]}, points);
        pointList.clear();
        return ear;
    }

    for (int i = 0; i < size; i++) {
        Triangle t({pointList[(size + i - 1) % size], pointList[i % size], pointList[(size + i + 1) % size]}, points);
        if (t.isConvex(points)) {
            bool test = false;
            for (int j = 0; j < size; j++) {
                if (!t.isVertex(pointList[j]) && t.containsPoint(points, points[pointList[j]])) {
                    test = true;
                }
            }

            if (!test) {
                pointList.erase(pointList.begin() + i);
                return t;
            }
        }
    }

    Triangle t;
    return t;
}

std::vector<Triangle> EarTriangulationGenerator::triangulate(Polygon p, std::vector<Point> &points) {
    std::vector<Triangle> triangles;
    std::vector<int> pointList = p.getPoints();

    while (pointList.size() >= 3) {
        Triangle ear = getEar(points, pointList);
        if (ear.isNull()) {
            break;
        }
        triangles.push_back(ear);
    }

    return triangles;
}
