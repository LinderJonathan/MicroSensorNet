#include <iostream>
#include <fstream>
#include <sstream>
#include <neural_network.hpp>
#include <fixed_point.hpp>

uint8_t inference (NeuralNetwork nn, const std::vector<fixed_point_t>& input) {
    
    std::vector<fixed_point_t> logits = nn.forward(input);

    uint8_t label = std::distance(logits.begin(), std::max_element(logits.begin(), logits.end()));
    return label;
}

std::tuple<std::vector<std::string>, std::vector<std::vector<float>>> readCSV (const std::string& csv_path) {
    
    std::vector<std::string> labels;
    std::vector<std::vector<float>> data;
    std::ifstream file(csv_path);
    
    std::string line;
    while (std::getline(file, line)) {
        std::vector<float> row;
        std::string label;

        std::stringstream ss(line);
        std::string cell;

        if (std::getline(ss, cell, ',')) {
            labels.push_back(cell);
        }

        while(std::getline(ss, cell, ',')) {
            row.push_back(std::stof(cell));
        }
        data.push_back(row);
    }
    return std::make_tuple(labels, data);
}