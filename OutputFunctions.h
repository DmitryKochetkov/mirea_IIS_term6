//
// Created by dimedrol on 15.04.2020.
//

#include <string>
#include <vector>

#ifndef MIREA_IIS_TERM6_OUTPUTFUNCTIONS_H
#define MIREA_IIS_TERM6_OUTPUTFUNCTIONS_H

#endif //MIREA_IIS_TERM6_OUTPUTFUNCTIONS_H

namespace ext_out {

    template <typename T>
    std::string vector_to_string(std::vector<T> vector) {
        std::string result = "[";
        for (int i = 0; i < vector.size() - 1; i++) {
            result += std::to_string(vector.at(i)) + ", ";
        }
        result += std::to_string(vector.back()) + "]";
        return result;
    }

    //TODO: print_debug_info with stringstream
}