#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

// TODO: add vcpkg.json file to handle all future dependencies
int load_weights_json(std::string weights_path) {
    
    std::ifstream f(weights_path);
    json data = json::parse(f);
    return 0;
}