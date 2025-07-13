#include "neural_network.hpp"
#include "inference.hpp"
#include "fixed_point.hpp"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

#define WEIGHT_PATH "weights/weights.json"
#define INFERENCE_DATA_PATH "data/data_human_filtered/inference.csv"
#define REPEATS 10
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
    std::vector<std::vector<float>> dataGyroscope = std::get<1>(dataCSV);

    uint32_t correctly_predicted = 0;

    auto total_duration = std::chrono::microseconds(0);

    // Inference
    for (uint32_t i = 0; i < labels.size(); i++) {
        std::string prediction;
        auto duration = std::chrono::microseconds(0);

        // Inference timing averaging
        for (uint8_t r = 0; r < REPEATS; r++) {
            auto start = std::chrono::high_resolution_clock::now();        
            prediction = inference(NN, to_fixed_vect(dataGyroscope[i]));
            auto end = std::chrono::high_resolution_clock::now();
            duration += std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        }
        if (prediction == labels[i]) {
            correctly_predicted++;
        }

        total_duration += duration;
    }

    // BELOW TODO IS ACTUAL TODO
    // TODO: log neural network performance (MCU constraints, inference time, RAM usage, latency)

    float total_seconds = static_cast<float>(total_duration.count()) / 1'000'000.0f;
    int total_samples = REPEATS * labels.size();
    float throughput = total_samples / total_seconds;

    // TODO: fix chrono type printing
    std::cout << "Accuracy: " << (static_cast<float>(correctly_predicted) / labels.size()) * 100.0f << " %" << std::endl;
    std::cout << "Total average inference time (" << REPEATS << " repeats): " << (static_cast<float>(total_duration.count()) / total_samples) << " microseconds" << std::endl;
    std::cout << "Throughput (" << REPEATS << " repeats): " << throughput << " samples/sec" << std::endl;
    return 0;
}