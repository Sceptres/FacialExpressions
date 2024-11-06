#include "MeshWeight.hpp"

MeshWeight::MeshWeight(const char* source) {
    std::ifstream in(source);

    // Read weights line by line
    std::string weightLine;
    while(std::getline(in, weightLine)) {
        float weight = std::stof(weightLine);
        this->weights.push_back(weight);
    }

    in.close();
}

std::vector<float> MeshWeight::getWeights() {
    return this->weights;
}