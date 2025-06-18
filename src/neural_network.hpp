#pragma once

#include <iostream>
#include <vector>
#include "fixed_point.hpp"


class NeuralNetwork {
    public:
        std::vector<DenseLayer> bias;

};

class DenseLayer {
    public:
        std::vector<float> input;
        std::vector<std::vector<fixed_point_t>> weights;
        std::vector<fixed_point_t> bias;
};  