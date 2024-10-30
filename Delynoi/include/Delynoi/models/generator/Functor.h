#ifndef DELYNOI_FUNCTOR_H
#define DELYNOI_FUNCTOR_H

namespace Delynoi {
    /*
     * Abstract class with a similar meaning as a lambda function or function pointer.
     */
    class Functor {
    public:
        virtual ~Functor() = default;
        /*
         * Applies the function on a number
         * @param x parameter of the function
         * @return value of the function with the given parameter
         */
        virtual double apply(double x) = 0;
    };
} // namespace Delynoi

#endif
