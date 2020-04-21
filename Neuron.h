//
// Created by dimedrol on 21.04.2020.
//

#ifndef MIREA_IIS_TERM6_NEURON_H
#define MIREA_IIS_TERM6_NEURON_H

#include <vector>
#include <random>
#include "Activation_Functions.h"

//TODO: move out
inline double get_random(double min_range, double max_range) {
    std::random_device r;
    std::uniform_real_distribution<double> unif(min_range, max_range);
    std::default_random_engine eng(r());
    return unif(eng);
}

class Neuron {
    double input;
    std::vector<double> weights;

public:
    explicit Neuron(const double& input, const int next_size): input(input) {
        this->weights.resize(next_size);
        for (auto item = weights.begin(); item != weights.end(); item++)
            *item = get_random(-1, 1);
        //std::cout << "Initialized neuron (value " << input << ", bias " << bias << ") with " << weights.size() << " weights" << std::endl;
    }

    void setInput(const double& input) {
        this->input = input;
    }

    double getWeight(int neuron_id) {
        return weights.at(neuron_id);
    }

    void setWeight(int neuron_id, double value) {
        weights[neuron_id] = value;
    }

    double getActivation() {
        return Sigmoid::Logistic(input).get();
    }

    double getActivationDerivative() {
        return Sigmoid::Logistic(input).getDerivative();
        //return Radial::Gaussian(input).getDerivative();
    }

    //?
    std::vector<double> getWeights() {
        return weights;
    }
};


#endif //MIREA_IIS_TERM6_NEURON_H
