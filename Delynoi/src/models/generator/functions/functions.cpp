#include <Delynoi/models/generator/Functor.h>
#include <Delynoi/models/generator/functions/RandomDouble.h>
#include <Delynoi/models/generator/functions/RandomInteger.h>
#include <Delynoi/utilities/delynoi_utilities.h>

#include <Delynoi/utilities/UniqueList.h>

namespace Delynoi {
    class Constant final : public Functor {
    public:
        Constant() = default;

        double apply(const double x) override {
            return x;
        }
    };

    class Uniform final : public Functor {
    private:
        double delta;

    public:
        explicit Uniform(const double delta) {
            this->delta = delta;
        }

        double apply(const double x) override {
            return x * delta;
        }
    };

    class Sine final : public Functor {
    private:
        double amplitude;
        double frecuency;
        double phase;

    public:
        Sine(const double a, const double f, const double p) {
            this->amplitude = a;
            this->frecuency = f;
            this->phase = p;
        }

        double apply(const double x) override {
            return amplitude * std::sin(utilities::radian(frecuency * x * 180) + utilities::radian(phase));
        }
    };

    class Cosine final : public Functor {
    private:
        double amplitude;
        double frecuency;
        double phase;

    public:
        Cosine(const double a, const double f, const double p) {
            this->amplitude = a;
            this->frecuency = f;
            this->phase = p;
        }

        double apply(const double x) override {
            return amplitude * std::cos(utilities::radian(frecuency * x * 180) + utilities::radian(phase));
        }
    };

    class DisplaceDelta final : public Functor {
    private:
        double delta;
        bool alternating = false;

    public:
        explicit DisplaceDelta(const double delta) {
            this->delta = delta;
        }

        double apply(const double x) override {
            alternating = !alternating;

            if (alternating) {
                return x + delta / 2;
            }
            return x;
        }
    };

    class ConstantAlternating final : public Functor {
    private:
        UniqueList<double> visitedPlaces;
        double delta{};
        bool alternating = false;

    public:
        ConstantAlternating() = default;

        double apply(double x) override {
            if (visitedPlaces.size() == 1) {
                delta = std::abs(visitedPlaces[0] - x);
            }

            if (const int index = visitedPlaces.push_back(x); index < visitedPlaces.size() - 1) {
                alternating = !alternating;
                visitedPlaces.clear();
            }

            if (alternating) {
                return x + delta / 2;
            }
            return x;
        }
    };

    namespace functions {
        Functor *constant() {
            return new Uniform(1.0);
        }

        Functor *displace_points(const double delta) {
            return new DisplaceDelta(delta);
        }

        Functor *constantAlternating() {
            return new ConstantAlternating();
        }

        Functor *uniform(const double delta) {
            return new Uniform(delta);
        }

        Functor *sine(const double amplitude, const double frecuency, const double phase) {
            return new Sine(amplitude, frecuency, phase);
        }

        Functor *cosine(const double amplitude, const double frecuency, const double phase) {
            return new Cosine(amplitude, frecuency, phase);
        }

        Functor *random_integer(const double min, const double max) {
            return new Random_Integer(min, max);
        }

        Functor *random_double(const double min, const double max) {
            return new Random_Double(min, max);
        }
    } // namespace functions
} // namespace Delynoi
