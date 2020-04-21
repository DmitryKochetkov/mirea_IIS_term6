cmake_minimum_required(VERSION 3.15)
project(mirea_IIS_term6)

set(CMAKE_CXX_STANDARD 14)

add_executable(mirea_IIS_term6 main.cpp Activation_Functions.h DataHandler.cpp DataHandler.h OutputFunctions.h NeuralNetwork.cpp NeuralNetwork.h Layer.cpp Layer.h Neuron.cpp Neuron.h)