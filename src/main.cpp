#include "neural_network.hpp"
#include "inference.hpp"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>

#define WEIGHT_PATH "weights/weights.json"
#define INFERENCE_DATA_PATH "data/data_human_filtered/inference.csv"

NeuralNetwork NN;
using json = nlohmann::json;

int main() {

    // Load weights into neural network
    std::ifstream f(WEIGHT_PATH);
    json data = json::parse(f);
    NN.load_weights(data);

    // Load test data and perform inference
    std::tuple<std::vector<std::string>, std::vector<std::vector<float>>> dataCSV = readCSV(INFERENCE_DATA_PATH);

    std::vector<std::string> labels = std::get<0>(dataCSV); 
    std::vector<std::vector<float>> data = std::get<1>(dataCSV);

    for (auto& label : labels) {
        std::cout << label << std::endl;
    }

    // TODO: log neural network performance (MCU constraints, inference time, RAM usage, latency)
    return 0;
}