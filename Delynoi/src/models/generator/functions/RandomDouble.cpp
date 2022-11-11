#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include <Delynoi/models/generator/functions/RandomDouble.h>

using namespace Delynoi;

std::default_random_engine Random_Double::rd;
std::mt19937 Random_Double::rng(rd());

Random_Double::Random_Double(double min, double max) {
    this->min = min;
    this->max = max;
    this->uni = std::uniform_real_distribution<double>(min, max);
}

double Random_Double::apply(double x) {
    return (uni)(Delynoi::Random_Double::rng);
}

#pragma clang diagnostic pop