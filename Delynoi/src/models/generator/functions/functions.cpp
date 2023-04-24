#include <Delynoi/models/generator/Functor.h>
#include <Delynoi/models/generator/functions/RandomDouble.h>
#include <Delynoi/models/generator/functions/RandomInteger.h>
#include <Delynoi/utilities/UniqueList.h>
#include <Delynoi/utilities/delynoi_utilities.h>

namespace Delynoi {
    class Constant : public Functor {
    public:
        Constant() = default;

        inline double apply(double x) override { return x; }
    };

    class Uniform : public Functor {
    private:
        double delta;

    public:
        explicit Uniform(double delta) { this->delta = delta; }

        inline double apply(double x) override { return x * delta; }
    };

    class Sine : public Functor {
    private:
        double amplitude;
        double frecuency;
        double phase;

    public:
        Sine(double a, double f, double p) {
            this->amplitude = a;
            this->frecuency = f;
            this->phase = p;
        }

        inline double apply(double x) override {
            return amplitude * std::sin(utilities::radian(frecuency * x * 180) + utilities::radian(phase));
        };
    };

    class Cosine : public Functor {
    private:
        double amplitude;
        double frecuency;
        double phase;

    public:
        Cosine(double a, double f, double p) {
            this->amplitude = a;
            this->frecuency = f;
            this->phase = p;
        }

        inline double apply(double x) override {
            return amplitude * std::cos(utilities::radian(frecuency * x * 180) + utilities::radian(phase));
        };
    };

    class DisplaceDelta : public Functor {
    private:
        double delta;
        bool alternating = false;

    public:
        explicit DisplaceDelta(double delta) {
            this->delta = delta;
        }

        inline double apply(double x) override {
            alternating = !alternating;

            if (alternating) {
                return x + delta / 2;
            } else {
                return x;
            }
        }
    };

    class ConstantAlternating : public Functor {
    private:
        UniqueList<double> visitedPlaces;
        double delta{};
        bool alternating = false;

    public:
        ConstantAlternating() = default;

        inline double apply(double x) override {
            if (visitedPlaces.size() == 1) {
                delta = std::abs(visitedPlaces[0] - x);
            }

            int index = visitedPlaces.push_back(x);

            if (index < visitedPlaces.size() - 1) {
                alternating = !alternating;
                visitedPlaces.clear();
            }

            if (alternating) {
                return x + delta / 2;
            } else {
                return x;
            }
        }
    };

    namespace functions {
        Functor *constant() {
            return new Uniform(1.0);
        }

        Functor *displace_points(double delta) {
            return new DisplaceDelta(delta);
        }

        Functor *constantAlternating() {
            return new ConstantAlternating();
        }

        Functor *uniform(double delta) {
            return new Uniform(delta);
        }

        Functor *sine(double amplitude, double frecuency, double phase) {
            return new Sine(amplitude, frecuency, phase);
        }

        Functor *cosine(double amplitude, double frecuency, double phase) {
            return new Cosine(amplitude, frecuency, phase);
        }

        Functor *random_integer(double min, double max) {
            return new Random_Integer(min, max);
        }

        Functor *random_double(double min, double max) {
            return new Random_Double(min, max);
        }
    } // namespace functions
} // namespace Delynoi
