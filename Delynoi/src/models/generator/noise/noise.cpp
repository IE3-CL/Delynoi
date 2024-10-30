#include <Delynoi/models/generator/Functor.h>
#include <Delynoi/models/generator/noise/RandomDoubleNoise.h>
#include <Delynoi/models/generator/noise/RandomIntegerNoise.h>

namespace Delynoi::noise {
    Functor *random_double_noise(Functor *f, const double min, const double max) {
        return new RandomDoubleNoise(f, min, max);
    }

    Functor *random_integer_noise(Functor *f, const double min, const double max) {
        return new RandomIntegerNoise(f, min, max);
    }
} // namespace Delynoi::noise