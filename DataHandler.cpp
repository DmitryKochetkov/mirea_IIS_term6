//
// Created by dimedrol on 12.04.2020.
//

#include <fstream>
#include "DataHandler.h"

void mnist::DataHandler::readTrainImages(const char *path) {

    std::ifstream file(path, std::ios::binary);

    if(file.is_open()) {
        int magic_number = 0;

        file.read((char *)&magic_number, sizeof(magic_number));
        magic_number = swap_endian(magic_number);

        if(magic_number != 2051) throw std::runtime_error("Invalid MNIST image file!");

        file.read((char *)&countTrainImages, sizeof(countTrainImages)), countTrainImages = swap_endian(countTrainImages);
        file.read((char *)&height, sizeof(height)), height = swap_endian(height);
        file.read((char *)&width, sizeof(width)), width = swap_endian(width);

        unsigned char** raw_data = new unsigned char*[countTrainImages];
        for(int i = 0; i < countTrainImages; i++) {
            raw_data[i] = new unsigned char[width * height];
            file.read((char *)raw_data[i], width * height);
        }

        trainImages.resize(countTrainImages);
        for (int i = 0; i < countTrainImages; i++) {
            for (int j = 0; j < width * height; j++)
                trainImages[i].push_back(raw_data[i][j]);
        }

        delete[] raw_data;
    }
}

void mnist::DataHandler::readTrainLabels(const char *path) {
    FILE* train_label = fopen(path, "rb");
    if (train_label == nullptr)
        throw std::runtime_error("Cannot open train images.");

    int n_images;
    fread(&n_images, sizeof(int), 1, train_label);
    fread(&n_images, sizeof(int), 1, train_label); //первые 32 бита не несут полезной информации

    if (swap_endian(n_images) != countTrainImages)
        throw std::runtime_error("MNIST training set: images and labels are incompatible");

    unsigned char* buf_labels = new unsigned char[countTrainImages];
    fread(buf_labels, sizeof(unsigned char), countTrainImages, train_label);
    for (int i = 0; i < countTrainImages; i++) {
        trainLabels.push_back((double)buf_labels[i]);
    }

    //TODO: проверить, работает ли этот код
//        double* buf_labels = new double[countTrainImages];
//        fread(buf_labels, sizeof(unsigned char), countTrainImages, train_label);
//        for (int i = 0; i < countTrainImages; i++) {
//            trainLabels.push_back((double)buf_labels[i]);
//        }

    delete[] buf_labels;

    fclose(train_label);
}

void mnist::DataHandler::readTrain(const char *path_images, const char *path_labels) {
    readTrainImages(path_images);
    readTrainLabels(path_labels);
}

std::vector<double> mnist::DataHandler::getTrainImage(int index) {
    //TODO: normalize data
    return(trainImages.at(index));
}

int mnist::DataHandler::getTrainLabel(int index) {
    std::vector<double> vector = getTrainLabelVectorized(index);
    for (int i = 0; i < vector.size(); i++)
        if (vector[i] == 1.0)
            return i;
    return -1;
}

std::vector<double> mnist::DataHandler::getTrainLabelVectorized(int index) {
    std::vector<double> result;
    result.resize(10);
    result[trainLabels.at(index)] = 1.0;
    return result;
}