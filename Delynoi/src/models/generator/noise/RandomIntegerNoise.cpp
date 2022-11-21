#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include <Delynoi/models/generator/noise/RandomIntegerNoise.h>

using namespace Delynoi;

std::default_random_engine RandomIntegerNoise::rd;
std::mt19937 RandomIntegerNoise::rng(rd());

RandomIntegerNoise::RandomIntegerNoise(Functor *f, double min, double max) {
    this->min = min;
    this->max = max;
    this->f = f;
    this->uni = std::uniform_int_distribution<int>(min, max);
}

double RandomIntegerNoise::apply(double x) {
    return f->apply(x) + (uni)(Delynoi::RandomIntegerNoise::rng) * ((uni)(Delynoi::RandomIntegerNoise::rng) % 2 ? 1 : -1);
}

#pragma clang diagnostic pop
