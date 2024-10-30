#include <Delynoi/models/generator/functions/RandomDouble.h>

using namespace Delynoi;

std::default_random_engine Random_Double::rd; // NOLINT(*-msc51-cpp)
std::mt19937 Random_Double::rng(rd());

Random_Double::Random_Double(const double min, const double max) {
    this->min = min;
    this->max = max;
    // ReSharper disable once CppTemplateArgumentsCanBeDeduced
    this->uni = std::uniform_real_distribution<double>(min, max); // Template required for MacOS
}

double Random_Double::apply(double x) {
    return (uni) (rng);
}
