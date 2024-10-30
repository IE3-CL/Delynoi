#include <Delynoi/models/generator/noise/RandomIntegerNoise.h>

using namespace Delynoi;

std::default_random_engine RandomIntegerNoise::rd; // NOLINT(*-msc51-cpp)
std::mt19937 RandomIntegerNoise::rng(rd());

RandomIntegerNoise::RandomIntegerNoise(Functor *f, const double min, const double max) {
    this->min = min;
    this->max = max;
    this->f = f;
    this->uni = std::uniform_int_distribution<>(min, max);
}

double RandomIntegerNoise::apply(const double x) {
    return f->apply(x) + (uni) (rng) * ((uni) (rng) % 2 ? 1 : -1);
}
