#include <Delynoi/models/neighbourhood/PointMap.h>

#include <fstream>

using namespace Delynoi;

PointMap::PointMap() = default;

PointMap::~PointMap() {
    map.clear();
}

void PointMap::insert(Point p, const int neighbour) {
    if (const auto got = this->map.find(p); got == this->map.end()) {
        NeighboursByPoint n(neighbour);
        this->map.insert(std::make_pair(p, n));
    } else {
        NeighboursByPoint &n = got->second;
        n.add(neighbour);
    }
}

void PointMap::insert(Point &p, const std::vector<int> &neighbours) {
    if (const auto got = this->map.find(p); got == this->map.end()) {
        NeighboursByPoint n(neighbours);
        this->map.insert(std::make_pair(p, n));
    } else {
        NeighboursByPoint &n = got->second;
        n.insert(neighbours);
    }
}

NeighboursByPoint &PointMap::get(const Point &p) {
    return this->map[p];
}

std::map<Point, NeighboursByPoint> &PointMap::getMap() {
    return this->map;
}

int PointMap::size() const {
    return this->map.size();
}

void PointMap::printInFile(const std::string &fileName) const {
    this->printInPath(utilities::getPath() + fileName);
}

void PointMap::printInPath(const std::string &path) const {
    std::ofstream file;
    file.open(path, std::ios::out);

    for (const auto &[fst, snd]: this->map) {
        file << fst.getString() + " ";
        NeighboursByPoint n = snd;

        for (const int i: n.getNeighbours()) {
            file << i << " ";
        }

        file << std::endl;
    }

    file.close();
}
