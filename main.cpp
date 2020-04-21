#include <iostream>
#include <vector>
#include "Activation_Functions.h"
#include "DataHandler.h"
#include "OutputFunctions.h"
#include "NeuralNetwork.h"
#include <random>
#include <string>
#include <memory>
#include <fstream>
#include <climits>
#include <algorithm>

double get_random(double min_range, double max_range) {
    std::random_device r;
    std::uniform_real_distribution<double> unif(min_range, max_range);
    std::default_random_engine eng(r());
    return unif(eng);
}

int main() {

    mnist::DataHandler dataHandler;
    dataHandler.readTrain(
            "/home/dimedrol/Desktop/mnist/train-images-idx3-ubyte",
            "/home/dimedrol/Desktop/mnist/train-labels.idx1-ubyte");

    //NeuralNetwork network({static_cast<unsigned long>(dataHandler.getWidth() * dataHandler.getHeight(), 10, 10}, 0.1);
    NeuralNetwork network({5, 4, 2}, 0.1);

//    int epochs = 100;
//    for (int i = 0; i < epochs; i++) {
//        network.BackPropagation(dataHandler.getTrainImage(i), dataHandler.getTrainLabel(i));
//        std::cout << "Back propagation " << i << " complete" << std::endl;
//    }

    //std::cout << "Learning complete. Starting tests..." << std::endl;

//    for (int i = epochs; i < epochs + 50; i++) {
//        std::cout << "Attempt " << i << ".";
//        dataHandler.printTrainImage(i);
//        network.FeedForward(dataHandler.getTrainImage(i));
//    }

    dataHandler.printTrainImage(0);
    std::cout << "*************************" << std::endl;
    dataHandler.printTrainImage(1);
    std::cout << "*************************" << std::endl;
    dataHandler.printTrainImage(2);
    std::cout << "*************************" << std::endl;
    dataHandler.printTrainImage(3);
    std::cout << "*************************" << std::endl;
    dataHandler.printTrainImage(106);
    std::cout << "*************************" << std::endl;

    return 0;
}
