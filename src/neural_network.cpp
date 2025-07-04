#include <iostream>
#include <vector>
#include <algorithm>
#include "neural_network.hpp"

// TODO: instantiate class

std::vector<fixed_point_t> NeuralNetwork::forward(const std::vector<fixed_point_t>& input){

    std::vector<fixed_point_t> x = layers[0].layer_forward(input);
    relu(x);

    x = layers[1].layer_forward(x);
    relu(x);

    x = layers[2].layer_forward(x);
    relu(x);

    return x;
}

std::vector<fixed_point_t> NeuralNetwork::relu(std::vector<fixed_point_t>& input){
    for (auto& neuron : input) {
        neuron = std::max(neuron, static_cast<fixed_point_t>(0));
    }
}