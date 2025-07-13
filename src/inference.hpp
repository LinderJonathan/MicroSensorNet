#include <iostream>
#include <fstream>
#include <sstream>
#include <neural_network.hpp>
#include <fixed_point.hpp>

#define JOGGING 0
#define STANDING 1
#define WALKING 2

std::string inference (NeuralNetwork nn, const std::vector<fixed_point_t>& input) {

    std::vector<fixed_point_t> logits = nn.forward(input);

    uint8_t label = std::distance(logits.begin(), std::max_element(logits.begin(), logits.end()));
    
    switch (label)
    {
    case STANDING:
        return "Standing";
        break;
    case WALKING:
        return "Walking";
        break;
    case JOGGING:
        return "Jogging";
        break;
    default:
        break;
    }
    return "N/A";
}

std::tuple<std::vector<std::string>, std::vector<std::vector<float>>> readCSV (const std::string& csv_path) {
    
    std::vector<std::string> labels;
    std::vector<std::vector<float>> data;
    std::ifstream file(csv_path);


    std::string line;

    std::getline(file, line); // Remove header row
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