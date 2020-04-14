//
// Created by dimedrol on 12.04.2020.
//

#include "DataHandler.h"

void mnist::DataHandler::readTrainImages(const char *path) {
    FILE* train_img = fopen(path, "rb");

    if (train_img == nullptr)
        throw std::runtime_error("Cannot open train images.");

    int msb;
    int n_images;
    fread(&msb, sizeof(int), 1, train_img);
    fread(&n_images, sizeof(int), 1, train_img);
    fread(&width, sizeof(int), 1, train_img);
    fread(&height, sizeof(int), 1, train_img);

    countTrainImages = swap_endian(n_images);
    width = swap_endian(width);
    height = swap_endian(height);
    trainImages.resize(countTrainImages);

    for (int i = 0; i < countTrainImages; i++) {
        unsigned char* buf = new unsigned char[width * height];
        fread(buf, sizeof(unsigned char), width * height, train_img);
        for (int j = 0; j < width * height; j++)
            trainImages.at(i).push_back((double)(buf[i * width + j]));
        delete[] buf;
    }

    fclose(train_img);
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
    return trainImages.at(index);
}

std::vector<double> mnist::DataHandler::getTrainLabel(int index) {
    std::vector<double> result;
    result.resize(10);
    result[trainLabels.at(index)] = 1.0;
    return result;
}
