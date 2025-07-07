#pragma once
#include <iostream>
#include <cstdint>
#include <math.h>
#include <stdexcept>

#define FRAC_BITS 8

typedef int16_t fixed_point_t;
///////////////////
/// CONVERSIONS ///
///////////////////

inline fixed_point_t to_fixed(float val) {

    return fixed_point_t(val * (1 << FRAC_BITS));

}

inline float to_float(fixed_point_t val){

    return ((float)val / (float)(1 << FRAC_BITS));
    
}

//////////////////
/// OPERATIONS ///
//////////////////

inline fixed_point_t fixed_add (fixed_point_t a, fixed_point_t b){
    return a + b;
}

inline fixed_point_t fixed_sub (fixed_point_t a, fixed_point_t b){
    return a - b;
}

inline fixed_point_t fixed_mul (fixed_point_t a, fixed_point_t b){
    return static_cast<fixed_point_t>(static_cast<uint32_t>(a * b) >> FRAC_BITS);
}

inline fixed_point_t fixed_inner_product (std::vector<fixed_point_t> a, std::vector<fixed_point_t> b) {
    fixed_point_t inner_product = 0;
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must be of equal size, but are of size" + std::to_string(a.size()) + " and " + std::to_string(b.size()));
    }
    for (int i = 0; i < a.size(); i++) {
        inner_product += fixed_mul(a[i], b[i]);
    }
    return inner_product;
}

inline fixed_point_t fixed_div (fixed_point_t a, fixed_point_t b) {
    fixed_point_t num = static_cast<uint32_t>(a) << FRAC_BITS;

    return static_cast<fixed_point_t>(num / b);

}