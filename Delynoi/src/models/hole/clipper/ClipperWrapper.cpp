#include <Delynoi/models/hole/clipper/ClipperWrapper.h>

using namespace Delynoi;

ClipperLib::Paths ClipperWrapper::polyIntersection(const std::vector<Point> &parent, const std::vector<Point> &child, int maxScale) {
    ClipperLib::Path region, hole;
    ClipperLib::Paths solution;

    for (auto &i: parent) {
        region << scalePoint(i, maxScale);
    }

    for (auto &i: child) {
        hole << scalePoint(i, maxScale);
    }

    ClipperLib::Clipper clipper;
    clipper.AddPath(region, ClipperLib::ptSubject, true);
    clipper.AddPath(hole, ClipperLib::ptClip, true);
    clipper.Execute(ClipperLib::ctDifference, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

    return solution;
}

ClipperLib::IntPoint ClipperWrapper::scalePoint(Point point, int maxScale) {
    return {(int) (maxScale * point.getX()), (int) (maxScale * point.getY())};
}
