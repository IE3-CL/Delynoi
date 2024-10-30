#include <Delynoi/models/Region.h>

#include <Delynoi/config/DelynoiConfig.h>
#include <Delynoi/models/generator/PointGenerator.h>
#include <Delynoi/models/hole/Hole.h>
#include <Delynoi/models/hole/clipper/ClipperWrapper.h>
#include <Delynoi/models/hole/clipper/lib/clipper.hpp>
#include <Delynoi/models/polygon/Polygon.h>

#include <climits>
#include <fstream>
#include <vector>

using namespace Delynoi;

Region::Region(const std::vector<Point> &points)
    : Polygon(points) {
    this->p = points;
}

void Region::mutate(const std::vector<Point> &points) {
    this->p = points;
    Polygon::mutate(points);
}

Region::Region() = default;

Region::Region(const Polygon &other, const std::vector<Point> &points) {
    const std::vector<int> otherPoints = other.getPoints();

    for (int i = 0; i < other.numberOfSides(); ++i) {
        this->p.push_back(points[otherPoints[i]]);
    }

    Polygon::mutate(this->p);
}

Region::Region(const Region &other)
    : Polygon(other) {
    this->p = other.p;
    this->holes.assign(other.holes.begin(), other.holes.end());
}

std::vector<Hole> &Region::getHoles() {
    return this->holes;
}

std::vector<Point> Region::getSeedPoints() {
    return this->seedPoints;
}

void Region::addHole(Hole h) {
    //When we receive a hole we check whether the difference between the region and the hole is just
    //one path (according to the used library)
    const DelynoiConfig *config = DelynoiConfig::instance();
    ClipperLib::Path region, hole;
    ClipperLib::Paths solution;

    for (auto &i: this->p) {
        region << ClipperLib::IntPoint(static_cast<int>(config->getScale() * i.getX()), static_cast<int>(config->getScale() * i.getY()));
    }

    const std::vector<Point> holePoints = h.getPoints();
    for (auto &holePoint: holePoints) {
        hole << ClipperLib::IntPoint(static_cast<int>(config->getScale() * holePoint.getX()), static_cast<int>(config->getScale() * holePoint.getY()));
    }

    ClipperLib::Clipper clipper;
    clipper.AddPath(region, ClipperLib::ptSubject, true);
    clipper.AddPath(hole, ClipperLib::ptClip, true);
    clipper.Execute(ClipperLib::ctDifference, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

    if (solution.size() == 1) {
        //Hole does intersect, so Region has to change and the hole "disappears"
        std::vector<Point> newPoints;

        for (const auto &i: solution[0]) {
            newPoints.emplace_back(i.X / (1.0 * config->getScale()), i.Y / (1.0 * config->getScale()));
        }

        this->mutate(newPoints);
    } else {
        //Two cases, hole is completely inside or completely outside, just ignore holes outside

        if (Polygon::containsPoint(this->p, h.getCenter())) {
            this->holes.push_back(h);
        } else {
            throw std::invalid_argument("Hole lies completely outside of domain region");
        }
    }
}

void Region::cleanInternalHoles() {
    this->holes.clear();
}

void Region::generateSeedPoints(const PointGenerator &_p, const int nX, const int nY) {
    const BoundingBox box = this->getBox();
    _p.generate(this->seedPoints, box, nX, nY);
    this->clean();
}

void Region::addSeedPoints(std::vector<Point> &seeds) {
    this->seedPoints.assign(seeds.begin(), seeds.end());
    this->clean();
}

void Region::addSeedsFromFile(const std::string &fileName) {
    std::ifstream infile;
    infile = utilities::openFile(fileName);

    std::string line;
    std::getline(infile, line);
    int numberMeshPoints = std::atoi(line.c_str()); // NOLINT(*-err34-c)
    for (int i = 0; i < numberMeshPoints; ++i) {
        std::getline(infile, line);
        std::vector<std::string> splittedLine = utilities::splitBySpaces(line);

        Point newPoint(std::atof(splittedLine[0].c_str()), std::atof(splittedLine[1].c_str())); // NOLINT(*-err34-c)
        this->seedPoints.push_back(newPoint);
    }

    infile.close();
    this->clean();
}

BoundingBox Region::getBox() const {
    double xMin = LLONG_MAX;
    double xMax = LLONG_MIN;
    double yMin = LLONG_MAX;
    double yMax = LLONG_MIN;

    for (auto &v: p) {
        xMin = v.getX() < xMin ? v.getX() : xMin;
        xMax = v.getX() > xMax ? v.getX() : xMax;
        yMin = v.getY() < yMin ? v.getY() : yMin;
        yMax = v.getY() > yMax ? v.getY() : yMax;
    }

    return {Point(xMin, yMin), Point(xMax, yMax)};
}

void Region::clean() {
    std::vector<int> toKeep;
    std::vector<Point> newSeeds;

    for (int i = 0; i < seedPoints.size(); i++) {
        if (Polygon::containsPoint(p, seedPoints[i])) {
            bool keep = true;

            for (Hole h: this->holes) {
                keep = keep && !h.containsPoint(seedPoints[i]);
            }

            if (keep) {
                toKeep.push_back(i);
            }
        }
    }

    newSeeds.reserve(toKeep.size());
    for (const int i: toKeep) {
        newSeeds.push_back(seedPoints[i]);
    }

    this->seedPoints = newSeeds;
}

std::vector<Point> Region::getRegionPoints() {
    std::vector<Point> points;
    points.assign(this->p.begin(), this->p.end());

    for (auto &hole: holes) {
        std::vector<Point> _p = hole.getPoints();
        points.insert(points.end(), _p.begin(), _p.end());
    }

    return points;
}

void Region::getSegments(std::vector<IndexSegment> &s) {
    Polygon::getSegments(s);
    int offset = static_cast<int>(this->p.size());

    for (Hole h: this->holes) {
        h.getSegments(s, offset);
        offset += h.getPoints().size();
    }
}

bool Region::containsPoint(const Point &_p) const {
    const std::vector<Point> regionPoints = this->p;

    return Polygon::containsPoint(regionPoints, _p);
}

bool Region::inEdges(const Point &_p) const {
    const std::vector<Point> regionPoints = this->p;

    return Polygon::inEdges(regionPoints, _p);
}

void Region::cleanSeedPoints() {
    this->seedPoints.clear();
}

void Region::printInFile(const std::string &fileName) {
    this->printInPath(utilities::getPath() + fileName);
}

void Region::printInPath(const std::string &path) {
    std::ofstream file;
    file.open(path, std::ios::out);

    const std::vector<Point> points = this->getRegionPoints();

    file << points.size() + seedPoints.size() << std::endl;
    for (auto &point: points) {
        file << point.getString() << std::endl;
    }

    for (auto &seedPoint: seedPoints) {
        file << seedPoint.getString() << std::endl;
    }

    std::vector<IndexSegment> segments;
    this->getSegments(segments);

    file << segments.size() << std::endl;
    for (const IndexSegment &s: segments) {
        file << s.getString() << std::endl;
    }

    file << 0 << std::endl;

    file.close();
}
