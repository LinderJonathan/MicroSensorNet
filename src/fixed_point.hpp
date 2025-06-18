#pragma once
#include <iostream>
#include <cstdint>
#include <math.h>

#define FRAC_BITS 8

typedef uint16_t fixed_point_t;
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

inline fixed_point_t fixed_div (fixed_point_t a, fixed_point_t b) {
    fixed_point_t num = static_cast<uint32_t>(a) << FRAC_BITS;

    return static_cast<fixed_point_t>(num / b);

}