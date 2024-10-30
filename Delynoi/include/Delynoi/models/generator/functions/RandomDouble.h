#ifndef DELYNOI_RANDOMDOUBLE_H
#define DELYNOI_RANDOMDOUBLE_H

#include <Delynoi/models/generator/Functor.h>
#include <random>

namespace Delynoi {
    /*
     * Generates random double numbers.
     */
    class Random_Double final : public Functor {
    public:
        /*
        * Parameters for the number generation. Maximum and minimum possible values.
        */
        double min;
        double max;

        /*
       * Parameters for random double number generation.
       */
        static std::default_random_engine rd;
        static std::mt19937 rng;
        std::uniform_real_distribution<> uni;

        /*
         * Constructor.
         */
        Random_Double(double min, double max);

        /*
        * Applies the function (as this is random generation, the result does not use the argument).
        * @param x argument of the function
        * @return function result
        */
        double apply(double x) override;
    };
} // namespace Delynoi

#endif
