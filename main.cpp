#include <iostream>
#include <vector>
#include "Activation_Functions.h"

int main() {

    std::cout << "Logistic: " << Sigmoid::Logistic(2.0).get() << std::endl;
    std::cout << "Tanh: " << Sigmoid::HyperbolicTangent(2.0).get() << std::endl;
    std::cout << "Gaussian: " << Radial::Gaussian(2.0).get() << std::endl;

    std::cout << "Logistic derivative: " << Sigmoid::Logistic(2.0).getDerivative() << std::endl;
    std::cout << "Tanh derivative: " << Sigmoid::HyperbolicTangent(2.0).getDerivative() << std::endl;
    std::cout << "Gaussian derivative: " << Radial::Gaussian(2.0).getDerivative() << std::endl;
    return 0;
}
