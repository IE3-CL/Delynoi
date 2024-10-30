#include <Delynoi/models/generator/Functor.h>
#include <Delynoi/models/generator/noise/RandomDoubleNoise.h>
#include <Delynoi/models/generator/noise/RandomIntegerNoise.h>

// ReSharper disable once CppEnforceNestedNamespacesStyle
namespace Delynoi { // Nested namespaces requires C++ std17. This is 14+ NOLINT(*-concat-nested-namespaces)
    namespace noise {
        Functor *random_double_noise(Functor *f, const double min, const double max) {
            return new RandomDoubleNoise(f, min, max);
        }

        Functor *random_integer_noise(Functor *f, const double min, const double max) {
            return new RandomIntegerNoise(f, min, max);
        }
    } // namespace noise
} // namespace Delynoi