#include <Delynoi/models/neighbourhood/SegmentMap.h>

using namespace Delynoi;

SegmentMap::SegmentMap() = default;

SegmentMap::~SegmentMap() {
    this->map.clear();
}

void SegmentMap::insert(const IndexSegment &s, const int polygonIndex) {
    const auto got = this->map.find(s);
    if (got == this->map.end()) {
        NeighboursBySegment n(polygonIndex);
        this->map.insert(std::make_pair(s, n));
    } else {
        got->second.setNeighbour(polygonIndex);
    }
}

void SegmentMap::insert(const IndexSegment &s, const NeighboursBySegment n) {
    this->map[s] = n;
}

NeighboursBySegment &SegmentMap::get(const IndexSegment &s) {
    return map[s];
}

std::unordered_map<IndexSegment, NeighboursBySegment, SegmentHasher> &SegmentMap::getMap() {
    return this->map;
}

std::unordered_map<IndexSegment, NeighboursBySegment, SegmentHasher> SegmentMap::getMap() const {
    return this->map;
}

int SegmentMap::size() const {
    return this->map.size();
}

void SegmentMap::printInFile(const std::string &fileName) const {
    this->printInPath(utilities::getPath() + fileName);
}

void SegmentMap::printInPath(const std::string &path) const {
    std::ofstream file;
    file.open(path, std::ios::out);

    for (const auto &v: this->map) { // Structured binding only C++ std17
        file << v.first.getString() + " " + v.second.getString() << std::endl;
    }

    file.close();
}

bool SegmentMap::containsSegment(const IndexSegment &s) {
    return this->map.find(s) != this->map.end();
}
