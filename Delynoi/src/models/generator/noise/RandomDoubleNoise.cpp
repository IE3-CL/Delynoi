#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include <Delynoi/models/generator/noise/RandomDoubleNoise.h>

using namespace Delynoi;

std::default_random_engine RandomDoubleNoise::rd;
std::mt19937 RandomDoubleNoise::rng(rd());

RandomDoubleNoise::RandomDoubleNoise(Functor *f, double min, double max) {
    this->min = min;
    this->max = max;
    this->f = f;

    this->uni = std::uniform_real_distribution<double>(min, max);
    this->uni_int = std::uniform_int_distribution<int>(INT_MIN + 100000, INT_MAX - 100000);
}

double RandomDoubleNoise::apply(double x) {
    return f->apply(x) + (uni)(Delynoi::RandomDoubleNoise::rng) * ((uni_int)(Delynoi::RandomDoubleNoise::rng) % 2 ? 1 : -1);
}

#pragma clang diagnostic pop
