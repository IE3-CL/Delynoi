#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#include <Delynoi/models/generator/noise/RandomDoubleNoise.h>
#include <Delynoi/models/generator/Functor.h>
#include <Delynoi/models/generator/noise/RandomIntegerNoise.h>

namespace Delynoi {
    namespace noise {
        Functor *random_double_noise(Functor *f, double min, double max) {
            return new RandomDoubleNoise(f, min, max);
        }

        Functor *random_integer_noise(Functor *f, double min, double max) {
            return new RandomIntegerNoise(f, min, max);
        }
    }
}

#pragma clang diagnostic pop
