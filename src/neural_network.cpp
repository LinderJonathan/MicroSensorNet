#include <iostream>
#include <vector>
#include <algorithm>
#include "neural_network.hpp"

// TODO: instantiate class

std::vector<fixed_point_t> NeuralNetwork::forward(const std::vector<fixed_point_t>& input){
    
    // TODO: iterate over the layers in the network,
    for (auto& l : layers) {
        std::vector<fixed_point_t> input = l.layer_forward(input);
        relu(input);
    }

    return {0};

}

std::vector<fixed_point_t> NeuralNetwork::relu(std::vector<fixed_point_t>& input){
    for (auto& neuron : input) {
        neuron = std::max(neuron, static_cast<fixed_point_t>(0));
    }
}