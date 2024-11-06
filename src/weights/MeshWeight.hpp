#ifndef MESH_WEIGHT_CLASS
#define MESH_WEIGHT_CLASS

#include <iostream>
#include <fstream>

/**
 * Class that holds the data of a weights file
 */
class MeshWeight {
    public:
        /**
         * Initializes a mesh weight file
         * 
         * @param[in] source The path to the source .weights file
         */
        MeshWeight(const char* source);

        /**
         * Access method to the weights imported from the .weights file
         * 
         * @return std::vector<float> A vector of floats representing the weights read from the .weights file
         */
        std::vector<float> getWeights();

    private:
        std::vector<float> weights;
};

#endif