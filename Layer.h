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
    explicit Layer(size_t size, size_t next_size) {
//        for (int i = 0; i < size; i++)
//            neurons.push_back(Neuron(0.5, next_size));
    }
};


#endif //MIREA_IIS_TERM6_LAYER_H
