//
// Created by dimedrol on 21.04.2020.
//

#ifndef MIREA_IIS_TERM6_LAYER_H
#define MIREA_IIS_TERM6_LAYER_H


#include <vector>
#include "Neuron.h"

class Layer {
private:
    std::vector<Neuron> neurons;
    Neuron bias;

public:
    explicit Layer(size_t size, size_t next_size): bias(get_random(-1.0, 1.0), next_size) {
        for (int i = 0; i < size; i++)
            neurons.push_back(Neuron(0.5, next_size));
    }

    double getWeightedSum(int neuron_id) {
        double result = 0.0;
        for (auto &neuron: neurons) {
            result += neuron.getActivation() * neuron.getWeight(neuron_id);
        }
        result += bias.getActivation() * bias.getWeight(neuron_id);
        return result;
    }

    void Connect(Layer& next) {
        for (int i = 0; i < next.neurons.size(); i++) {
            next.neurons[i].setInput(getWeightedSum(i));
        }
    }

    std::vector<Neuron> getNeurons() {
        return neurons;
    }
};


#endif //MIREA_IIS_TERM6_LAYER_H
