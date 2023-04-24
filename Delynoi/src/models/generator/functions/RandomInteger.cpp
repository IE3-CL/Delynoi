#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"

#include <Delynoi/models/generator/functions/RandomInteger.h>

using namespace Delynoi;

std::default_random_engine Random_Integer::rd;
std::mt19937 Random_Integer::rng(rd());

Random_Integer::Random_Integer(double min, double max) {
    this->min = min;
    this->max = max;
    this->uni = std::uniform_int_distribution<int>(min, max);
}

double Random_Integer::apply(double x) {
    return (uni) (Delynoi::Random_Integer::rng);
}

#pragma clang diagnostic pop
