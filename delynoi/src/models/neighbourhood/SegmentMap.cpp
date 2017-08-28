#include <delynoi/models/neighbourhood/SegmentMap.h>


SegmentMap::SegmentMap() {}

void SegmentMap::insert(IndexSegment s, int polygonIndex) {
    auto got = this->map.find(s);

    if(got == this->map.end()){
        Neighbours n (polygonIndex);
        this->map.insert(std::make_pair(s,n));
    }else{
        got->second.setNeighbour(polygonIndex);
    }
}

void SegmentMap::insert(IndexSegment s, Neighbours n) {
    this->map[s] = n;
}

Neighbours& SegmentMap::get(IndexSegment s) {
    return map[s];
}

std::unordered_map<IndexSegment,Neighbours, SegmentHasher>& SegmentMap::getMap() {
    return this->map;
}

int SegmentMap::size() {
    return this->map.size();
}

void SegmentMap::delete_element(IndexSegment key) {
    this->map.erase(key);
}

void SegmentMap::printInFile(std::string fileName) {
    std::string path = utilities::getPath();
    path +=  fileName;

    std::ofstream file;
    file.open(path, std::ios::out);


    for(auto v : this->map){
        file << v.first.getString() + " " + v.second.getString() << std::endl;
    }

    file.close();
}

bool SegmentMap::containsSegment(IndexSegment s) {
    return this->map.find(s)!= this->map.end();
}
