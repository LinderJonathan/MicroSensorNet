#pragma once

#include <iostream>
#include <vector>
#include <numeric>
#include "fixed_point.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;
struct DenseLayer {

    std::vector<fixed_point_t>input;
    std::vector<std::vector<fixed_point_t>> weights;
    std::vector<fixed_point_t> bias;

    std::vector<fixed_point_t> layer_forward(const std::vector<fixed_point_t>& input) {

        std::vector<fixed_point_t> output(weights.size(), 0);
        for (unsigned int i = 0; i < weights.size(); i++) {

            fixed_point_t xw = fixed_inner_product(weights[i], input);
            output[i] = fixed_add(xw, bias[i]);
        }
        return output;
    }
};

class NeuralNetwork {
    public:
        NeuralNetwork();
        std::vector<DenseLayer> layers;

        // Forward expects a vector of (x,y,z) coordinates, and produces 
        // a distribution over three classes (standing, walking, jogging)
        std::vector<fixed_point_t> forward(const std::vector<fixed_point_t>& input);
        std::vector<fixed_point_t> relu(std::vector<fixed_point_t>& input);
        void load_weights(json data);
};