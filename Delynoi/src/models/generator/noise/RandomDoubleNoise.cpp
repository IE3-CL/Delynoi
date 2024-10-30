#include <Delynoi/models/generator/noise/RandomDoubleNoise.h>
#include <climits> // Used on linux

using namespace Delynoi;

std::default_random_engine RandomDoubleNoise::rd; // NOLINT(*-msc51-cpp)
std::mt19937 RandomDoubleNoise::rng(rd());

RandomDoubleNoise::RandomDoubleNoise(Functor *f, const double min, const double max) {
    this->min = min;
    this->max = max;
    this->f = f;

    // ReSharper disable CppTemplateArgumentsCanBeDeduced
    this->uni = std::uniform_real_distribution<double>(min, max); // MacOS require template
    // ReSharper disable CppTemplateArgumentsCanBeDeduced
    this->uni_int = std::uniform_int_distribution<int>(INT_MIN + 100000, INT_MAX - 100000);
}

double RandomDoubleNoise::apply(const double x) {
    return f->apply(x) + (uni) (rng) * ((uni_int) (rng) % 2 ? 1 : -1);
}
