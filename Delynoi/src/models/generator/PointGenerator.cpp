#include <Delynoi/models/generator/PointGenerator.h>

using namespace Delynoi;

PointGenerator::PointGenerator() = default;

PointGenerator::PointGenerator(Functor *lX, Functor *lY) {
    this->lX = lX;
    this->lY = lY;

    this->variable = functions::independent_variable::both;
}

PointGenerator::PointGenerator(Functor *l, const functions::independent_variable variable) {
    this->variable = variable;

    switch (variable) {
        case functions::independent_variable::x:
            this->lY = l;
            break;
        case functions::independent_variable::y:
            this->lX = l;
            break;
        case functions::independent_variable::both:
            throw std::invalid_argument("Both x and y are free variables and only one creator function given");
    }
}

void PointGenerator::generate(std::vector<Point> &vector, const BoundingBox &box, const int nX, const int nY) const {
    const double dX = box.getWidth() / (nX - 1);
    const double dY = box.getHeight() / (nY - 1);

    for (int i = 0; i < nY; i++) {
        for (int j = 0; j < nX; j++) {
            const double x = box.xMin() + j * dX;
            const double y = box.yMin() + i * dY;

            vector.push_back(result(x, y));
        }
    }
}

Point PointGenerator::result(double x, double y) const {
    switch (variable) {
        case functions::independent_variable::x:
            return {x, y + this->lY->apply(x)};
        case functions::independent_variable::y:
            return {x + this->lX->apply(y), y};
        case functions::independent_variable::both:
            return {this->lX->apply(x), this->lY->apply(y)};
    }
    return {0, 0};
}
