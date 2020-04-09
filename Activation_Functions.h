//
// Created by dimedrol on 07.04.2020.
//

#ifndef MIREA_IIS_TERM6_ACTIVATION_FUNCTIONS_H
#define MIREA_IIS_TERM6_ACTIVATION_FUNCTIONS_H

#include <cmath>

class MathFunction {
protected:
    double x;

public:
    virtual double get() = 0;
    virtual double getDerivative() = 0;
    explicit MathFunction(const double& x): x(x) {}
};

//сигмоидальные функции активации
namespace Sigmoid {

    class Logistic : public MathFunction {
    public:
        double get() override {
            return 1/(1 + exp(-x));
        }

        double getDerivative() override {
            return get() * (1 - get());
        }

        explicit Logistic(const double &x) : MathFunction(x) {}
    };

    class HyperbolicTangent : public MathFunction {
    public:
        double get() override {
            return tanh(x);
        }

        double getDerivative() override {
            //return pow(1 + cosh(x), 2);
            return 1 - pow(get(), 2);
        }

    public:
        explicit HyperbolicTangent(const double &x) : MathFunction(x) {}
    };
}

//радиально-базисные функции активации
namespace Radial {
    class Gaussian : public MathFunction {
    public:
        double get() override {
            return exp(-pow(x, 2));
        }

        double get(double epsilon) {
            return exp(-pow(epsilon * x, 2));
        }

        double getDerivative() override {
            return -2 * x * exp(-x * x);
        }

        explicit Gaussian(const double &x) : MathFunction(x) {}
    };
}

#endif //MIREA_IIS_TERM6_ACTIVATION_FUNCTIONS_H
