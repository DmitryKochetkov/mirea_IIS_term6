//
// Created by dimedrol on 12.04.2020.
//

#ifndef MIREA_IIS_TERM6_DATAHANDLER_H
#define MIREA_IIS_TERM6_DATAHANDLER_H

#include <climits>
#include <vector>
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace mnist {
    class DataHandler;
}


class mnist::DataHandler {
private:
    int width;
    int height;
    int countTrainImages;

    std::vector<std::vector<double>> trainImages;
    std::vector<double> trainLabels;

    void readTrainImages(const char* path);

    void readTrainLabels(const char* path);


public:
    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    template <typename T>
    static T swap_endian(T u)
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

    void readTrain(const char* path_images, const char* path_labels);

    std::vector<double> getTrainImage(int index);

    void printTrainImage(int index) {

        std::cout << "Image[" << index << "] (" << *std::find(getTrainLabel(index).begin(), getTrainLabel(index).end(), 1.0) << "): " << std::endl;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
                std::cout << (int)trainImages[index][i * height + j] << " ";
            std::cout << std::endl;
        }
    }

    std::vector<double> getTrainLabel(int index);
};


#endif //MIREA_IIS_TERM6_DATAHANDLER_H
