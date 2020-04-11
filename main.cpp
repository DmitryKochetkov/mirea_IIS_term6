#include <iostream>
#include <vector>
#include "Activation_Functions.h"
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
            body.push_back(Neuron(0, next_size));
    }

    double getWeightedSum(int neuron_id) {
        double result = 0;
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

    void FeedForward(const std::vector<double>& input) {
        print_debug_info("Trying to FeedForward...");

        if (input.size() != layers[0].body.size())
        {
            print_debug_info("(FeedForward) Incorrect input size " + std::to_string(input.size()) + ", expected " + std::to_string(layers[0].body.size()) + ".");
            return;
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
    }

    void BackPropagation() {
        //TODO: implement
    }
};

template <typename T>
T swap_endian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}

int main() {
    FILE* train_img = fopen("/home/dimedrol/Desktop/mnist/train-images-idx3-ubyte", "rb");
    FILE* train_label = fopen("/home/dimedrol/Desktop/mnist/train-labels.idx1-ubyte", "rb");

    if (train_img == nullptr) {
        std::cout << "Cannot open train images." << std::endl;
        return 1;
    }

    if (train_label == nullptr) {
        std::cout << "Cannot open train labels." << std::endl;
        return 1;
    }

    const int n = 1;
    int msb[n];
    int n_images;
    int width;
    int height;
    fread(&msb, sizeof(int), n, train_img);
    fread(&n_images, sizeof(int), 1, train_img);
    fread(&width, sizeof(int), 1, train_img);
    fread(&height, sizeof(int), 1, train_img);

    n_images = swap_endian(n_images);
    width = swap_endian(width);
    height = swap_endian(height);


    std::cout << std::endl;
    std::cout << "Reading MNIST headers..." << std::endl;
    std::cout << "Number of images: " << n_images << std::endl;
    std::cout << "Number of rows: " << width << std::endl;
    std::cout << "Number of columns: " << height << std::endl;

    unsigned char** images = new unsigned char*[n_images];
    unsigned char* labels = new unsigned char[n_images];

    for (int i = 0; i < n_images; i++) {
        images[i] = new unsigned char[width * height];
        fread(images[i], sizeof(unsigned char), width * height, train_img);
    }
    int buf;

    fread(&buf, sizeof(int), 2, train_label);
    fread(labels, sizeof(unsigned char), n_images, train_label);

    fclose(train_img);
    fclose(train_label);

    int k;
    std::cin >> k;
    std::cout << "Image[k] (" << (int)labels[k] << "): " << std::endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            std::cout << (int)images[k][i * height + j] << " ";
        std::cout << std::endl;
    }

    //NeuralNetwork network({static_cast<unsigned long>(width * height), 128, 10});
    //network.FeedForward(first_image);

    return 0;
}
