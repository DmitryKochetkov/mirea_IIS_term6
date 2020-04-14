#include <iostream>
#include <vector>
#include "Activation_Functions.h"
#include "DataHandler.h"
#include <random>
#include <string>
#include <memory>
#include <fstream>
#include <climits>

double get_random(double min_range, double max_range) {
    std::random_device r;
    std::uniform_real_distribution<double> unif(min_range, max_range);
    std::default_random_engine eng(r());
    return unif(eng);
}

class Neuron {
private:
    double input;
    double bias;
    std::vector<double> weights; //i-й элемент - вес связи нейрона с i-м нейроном следующего слоя

public:
    double setInput(const double& input) {
        this->input = input;
        std::cout << "Updated neuron (value " << input << ", activation " << getActivation() << ", bias " << bias << ") with " << weights.size() << " weights" << std::endl;
    }

    double getWeight(int neuron_id) {
        return weights.at(neuron_id);
    }

    double getActivation() {
        return Sigmoid::Logistic(input).get();
    }

    double getBias() {
        return bias;
    }

    //next_size - размер следующего слоя
    explicit Neuron(const double& input, const int next_size): input(input) {
        this->bias = get_random(-1, 1);
        this->weights.resize(next_size);
        for (auto item = weights.begin(); item != weights.end(); item++)
            *item = get_random(-1, 1);
        std::cout << "Initialized neuron (value " << input << ", bias " << bias << ") with " << weights.size() << " weights" << std::endl;
    }

    //Neuron(value, Layer& prev_layer = nullptr)
};

class Layer {

public:
    std::vector<Neuron> body; //TODO: make private

    explicit Layer(size_t size, size_t next_size) {
        for (int i = 0; i < size; i++)
            body.push_back(Neuron(0.0, next_size));
    }

    double getWeightedSum(int neuron_id) {
        double result = 0.0;
        for (auto &neuron: body) {
            result += neuron.getActivation();
        }
        return result;
    }

    void Connect(Layer& next) {
        for (int i = 0; i < next.body.size(); i++) {
            next.body[i].setInput(getWeightedSum(i) + next.body[i].getBias());
        }
    }
};

class NeuralNetwork {
private:
    std::vector<Layer> layers;

    bool MSG_ON = true;

    //TODO: move out
    //TODO: use StringStream
    void print_debug_info(const std::string& info) {
        if (MSG_ON)
            std::cout << info << std::endl;
    }

public:
    explicit NeuralNetwork(const std::vector<size_t>& sizes) {
        for (int i = 0; i < sizes.size() - 1; i++)
            layers.push_back(Layer(sizes[i], sizes[i+1]));
        layers.push_back(Layer(sizes.back(), 0));
    }

    std::vector<double> FeedForward(const std::vector<double>& input) {
        print_debug_info("Trying to FeedForward...");

        if (input.size() != layers[0].body.size())
        {
            print_debug_info("(FeedForward) Incorrect input size " + std::to_string(input.size()) + ", expected " + std::to_string(layers[0].body.size()) + ".");
            throw 1; //TODO: throw exception
        }

        print_debug_info("FeedForward, layer 0");
        for (int i = 0; i < layers[0].body.size(); i++) {
            layers[0].body[i].setInput(input[i]);
        }

        for (int i = 0; i < layers.size() - 1; i++) {
            print_debug_info("FeedForward, layer " + std::to_string(i+1));
            layers[i].Connect(layers[i + 1]);
        }

        print_debug_info("Feed Forward complete.");

        std::vector<double> output_activations;
        for (auto& neuron: layers.back().body) {
            output_activations.push_back(neuron.getActivation());
        }

        std::string result = "[";
        for (int i = 0; i < output_activations.size() - 1; i++)
            result += std::to_string(i) + " -> " + std::to_string(output_activations[i]) + ", ";
        result += std::to_string(output_activations.size() - 1) + " -> " + std::to_string(output_activations.back()) + "]";

        print_debug_info("Result activations: " + result);
        return output_activations;
    }

    void BackPropagation(const std::vector<double>& input, const std::vector<double>& output) {
        print_debug_info("Training in progress...");
        //TODO: calculate a cost function
    }
};


int main() {

    mnist::DataHandler dataHandler;
    dataHandler.readTrain(
            "/home/dimedrol/Desktop/mnist/train-images-idx3-ubyte",
            "/home/dimedrol/Desktop/mnist/train-labels.idx1-ubyte");

    NeuralNetwork network({static_cast<unsigned long>(dataHandler.getWidth() * dataHandler.getHeight()), 128, 10});

    auto c = dataHandler.getTrainImage(0);
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++)
            std::cout << c[i * 28 + j] << " ";
        std::cout << std::endl;
    }

    //network.FeedForward(dataHandler.getTrainImage(0));

//    int k;
//    std::cin >> k;
//    std::cout << "Image[k] (" << (int)labels[k] << "): " << std::endl;
//    for (int i = 0; i < height; i++)
//    {
//        for (int j = 0; j < width; j++)
//            std::cout << (int)images[k][i * height + j] << " ";
//        std::cout << std::endl;
//    }


    return 0;
}
