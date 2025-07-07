#include "neural_network.hpp"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>

#define WEIGHT_PATH "weights/weights.json"

NeuralNetwork NN;
using json = nlohmann::json;
int main() {
    
    std::ifstream f(WEIGHT_PATH);
    json data = json::parse(f);
    NN.load_weights(data);
    //std::cout << data.dump() << std::endl;
    for (size_t i = 0; i < NN.layers[0].weights.size(); i++) {
        const auto& row = NN.layers[0].weights[i];
        for (size_t j = 0; j < row.size(); j++) {
            std::cout << row[j] << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}