#include <Delynoi/models/neighbourhood/NeighboursBySegment.h>

using namespace Delynoi;

NeighboursBySegment::NeighboursBySegment() = default;

NeighboursBySegment::NeighboursBySegment(const int i1) {
    this->n1 = i1;
}

NeighboursBySegment::NeighboursBySegment(const int i1, const int i2) {
    this->n1 = i1;
    this->n2 = i2;
}

NeighboursBySegment::NeighboursBySegment(const Pair<int> &p) {
    this->n1 = p.first;
    this->n2 = p.second;
}

void NeighboursBySegment::setNeighbour(const int i) {
    this->n2 = i;
}

int NeighboursBySegment::getFirst() const {
    return this->n1;
}

int NeighboursBySegment::getSecond() const {
    return this->n2;
}

std::string NeighboursBySegment::getString() const {
    return utilities::toString<double>(this->n1) + " " + utilities::toString<double>(this->n2);
}

bool NeighboursBySegment::operator==(const NeighboursBySegment &other) const {
    return this->getFirst() == other.getFirst() && this->getSecond() == other.getSecond() ||
           this->getFirst() == other.getSecond() && this->getSecond() == other.getFirst();
}

void NeighboursBySegment::setFirst(const int value) {
    this->n1 = value;
}

void NeighboursBySegment::setSecond(const int value) {
    this->n2 = value;
}
