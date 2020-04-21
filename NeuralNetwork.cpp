//
// Created by dimedrol on 21.04.2020.
//

#include <iostream>
#include "NeuralNetwork.h"

std::vector<double> NeuralNetwork::FeedForward(const std::vector<double> &input) {
    std::cout << "Trying to FeedForward..." << std::endl;

    if (input.size() != layers[0].getNeurons().size())
    {
        throw std::runtime_error("(FeedForward) Incorrect input size " + std::to_string(input.size()) + ", expected " + std::to_string(layers[0].getNeurons().size()) + ".");
    }

    for (int i = 0; i < layers[0].getNeurons().size(); i++) {
        layers[0].getNeurons()[i].setInput(input[i]);
    }

    for (int i = 0; i < layers.size() - 1; i++) {
        layers[i].Connect(layers[i + 1]);
    }

    std::cout << "Feed Forward complete." << std::endl;

    std::vector<double> output_activations;
    for (auto& neuron: layers.back().getNeurons()) {
        output_activations.push_back(neuron.getActivation());
    }

    std::string result = "[";
    for (int i = 0; i < output_activations.size() - 1; i++)
        result += std::to_string(i) + " -> " + std::to_string(output_activations[i]) + ", ";
    result += std::to_string(output_activations.size() - 1) + " -> " + std::to_string(output_activations.back()) + "]";

    std::cout << "Result activations: " + result << std::endl;
    return output_activations;
}

void NeuralNetwork::BackPropagation(const std::vector<double> &input, const std::vector<double> &output) {
    if (output.size() != layers.back().getNeurons().size())
    {
        throw "(Back propagation) Incorrect output size " + std::to_string(output.size()) + ", expected " + std::to_string(layers.back().getNeurons().size()) + ".";
    }

    std::cout << "Back propogation in progress..." << std::endl;
    FeedForward(input);

    std::vector<double> deltaLast;
    deltaLast.resize(output.size());

    //print_debug_info("(Back propagation) Deltas, layer " + std::to_string(layers.size() - 1) + ": ");
    for (int i = 0; i < deltaLast.size(); i++) {
        deltaLast[i] = output.at(i) - layers.back().getNeurons().at(i).getActivation();
    }

    //std::cout << ext_out::vector_to_string(deltaLast) << std::endl;

    std::vector<std::vector<double>> errors;
    errors.resize(layers.size());
    errors[errors.size() - 1] = deltaLast;

    for (int k = layers.size() - 2; k >= 0; k--) {

        errors[k].resize(layers[k].getNeurons().size());

        for (int i = 0; i < errors[k].size(); i++)
            for (auto& weight: layers[k].getNeurons()[i].getWeights())
                errors[k][i] += errors[k+1][i] * weight;
    }

    for (int k = 1; k < layers.size() - 2; k++) {
        for (int i = 0; i < errors[k].size(); i++)
            for (auto &weight: layers[k].getNeurons()[i].getWeights())
                weight += layers[k].getNeurons()[i].getActivationDerivative() * errors[k][i] *
                          layers[k-1].getWeightedSum(i) *
                          this->LearningRate; //производная активации от взвешенной сумммы входов? то есть без bias?
    }
}
