#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#include <Delynoi/models/neighbourhood/SegmentMap.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

using namespace Delynoi;

SegmentMap::SegmentMap() = default;

void SegmentMap::insert(const IndexSegment &s, int polygonIndex) {
    auto got = this->map.find(s);

    if (got == this->map.end()) {
        NeighboursBySegment n(polygonIndex);
        this->map.insert(std::make_pair(s, n));
    } else {
        got->second.setNeighbour(polygonIndex);
    }
}

void SegmentMap::insert(const IndexSegment &s, NeighboursBySegment n) {
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

int SegmentMap::size() {
    return this->map.size();
}

void SegmentMap::printInFile(const std::string &fileName) {
    std::string path = utilities::getPath();
    path += fileName;

    std::ofstream file;
    file.open(path, std::ios::out);

    for (const auto &v: this->map) {
        file << v.first.getString() + " " + v.second.getString() << std::endl;
    }

    file.close();
}

bool SegmentMap::containsSegment(const IndexSegment &s) {
    return this->map.find(s) != this->map.end();
}

#pragma clang diagnostic pop
#pragma clang diagnostic pop