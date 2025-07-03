#pragma once

#include <iostream>
#include <vector>
#include "fixed_point.hpp"

struct DenseLayer {

    std::vector<float> input;
    std::vector<std::vector<fixed_point_t>> weights;
    std::vector<fixed_point_t> bias;
};

class NeuralNetwork {
    public:
        std::vector<DenseLayer> layer;
        
        // Forward expects a vector of (x,y,z) coordinates, and produces 
        // a distribution over three classes (standing, walking, jogging)
        std::vector<fixed_point_t> forward(std::vector<fixed_point_t> input);
};