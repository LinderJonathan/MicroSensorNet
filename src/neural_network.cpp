#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <nlohmann/json.hpp>
#include "neural_network.hpp"

using json = nlohmann::json;

NeuralNetwork::NeuralNetwork(){
    layers.resize(3);
}



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

void NeuralNetwork::load_weights(json data){
    for (int i = 0; i < 3; i++) {

        std::string weight_key = "fc" + std::to_string(i+1) + ".weight";
        std::string bias_key = "fc" + std::to_string(i+1) + ".bias";

        layers[i].weights = data[weight_key].get<std::vector<std::vector<fixed_point_t>>>();
        layers[i].bias = data[bias_key].get<std::vector<fixed_point_t>>();
    }

}