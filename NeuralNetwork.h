//
// Created by dimedrol on 21.04.2020.
//

#ifndef MIREA_IIS_TERM6_NEURALNETWORK_H
#define MIREA_IIS_TERM6_NEURALNETWORK_H

//Данный класс реализует многослойный перцептрон

#include <cstdlib>
#include <vector>
#include "Layer.h"

class NeuralNetwork {
private:
    double LearningRate;
    std::vector<Layer> layers;

public:
    explicit NeuralNetwork(const std::vector<size_t>& sizes, double LearningRate): LearningRate(LearningRate) {
        for (int i = 0; i < sizes.size() - 1; i++)
            layers.push_back(Layer(sizes[i], sizes[i+1]));
        layers.push_back(Layer(sizes.back(), 0));
    }

    std::vector<double> FeedForward(const std::vector<double>& input);

    void BackPropagation(const std::vector<double>& input, const std::vector<double>& output);
};


#endif //MIREA_IIS_TERM6_NEURALNETWORK_H
