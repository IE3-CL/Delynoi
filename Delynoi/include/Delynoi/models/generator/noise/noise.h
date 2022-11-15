#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#ifndef DELYNOI_NOISE_H
#define DELYNOI_NOISE_H

#include <Delynoi/models/generator/Functor.h>

namespace Delynoi {
    /*
     * Namespace with all noise functions definitions.
     */
    namespace noise {
        /* Creates a RandomDoubleNoise instance.
         * @param f Function class to which the noise will be applied
         * @param min minimum value of the noise
         * @param max maximum value of the noise
         * @return Function class with the noise applied
         */
        Functor *random_double_noise(Functor *f, double min, double max);

        /* Creates a RandomIntegereNoise instance.
         * @param f Function class to which the noise will be applied
         * @param min minimum value of the noise
         * @param max maximum value of the noise
         * @return Function class with the noise applied
         */
        Functor *random_integer_noise(Functor *f, double min, double max);
    }
}

#endif
#pragma clang diagnostic pop
