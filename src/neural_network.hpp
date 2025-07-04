#pragma once

#include <iostream>
#include <vector>
#include <numeric>
#include "fixed_point.hpp"

struct DenseLayer {

    std::vector<fixed_point_t>input;
    std::vector<std::vector<fixed_point_t>> weights;
    std::vector<fixed_point_t> bias;

    std::vector<fixed_point_t> layer_forward(const std::vector<fixed_point_t>& input) {

        std::vector<fixed_point_t> output(weights.size(), 0);
        for (unsigned int i = 0; i < weights.size(); i++) {

            fixed_point_t xw = std::inner_product(weights[i].begin(), weights[i].end(), input.begin(), 0);
            output[i] = xw + bias[i];
        }

    }


};

class NeuralNetwork {
    public:
        std::vector<DenseLayer> layers;
        // Forward expects a vector of (x,y,z) coordinates, and produces 
        // a distribution over three classes (standing, walking, jogging)
        std::vector<fixed_point_t> forward(const std::vector<fixed_point_t>& input);
        std::vector<fixed_point_t> relu(std::vector<fixed_point_t>& input);
};