#ifndef TH10_MATH_QUANTIZED_VECTOR_HPP
#define TH10_MATH_QUANTIZED_VECTOR_HPP

#include <cstdint>

// The 0x1C-byte parameter block shared by the retail leaves at 0x00404D40
// (subtract), 0x00404DA0 (scale) and 0x00404E10 (add). Six float channels are
// followed by byte-quantized forms of channels 2..5: retail leaves those four
// values on the x87 stack and runs each through MSVC's float-to-integer helper
// at 0x00463B2C before storing the low byte.
struct QuantizedVector {
    float components[6];
    uint8_t quantized[4];
};

inline void QuantizedVector_UpdateBytes(QuantizedVector* vector) {
    for (int index = 0; index < 4; ++index) {
        vector->quantized[index] =
            (uint8_t)(int)vector->components[index + 2];
    }
}

// Both of these are defined in src/math/math_utils.cpp, which owns the
// 0x00404D40 coverage entry.
QuantizedVector* Vec_Scale(QuantizedVector* destination,
                           const QuantizedVector* source, float scalar);

QuantizedVector* Vec_Subtract(QuantizedVector* destination,
                              const QuantizedVector* left,
                              const QuantizedVector* right);

// Channel-wise addition. This is the same leaf the retail binary exposes at
// 0x00404E10; that address is already carried by src/game/particle_seed.cpp,
// so this definition is deliberately inline and unlabelled rather than
// claiming the address a second time in the coverage ledger.
inline QuantizedVector* Vec_Add(QuantizedVector* destination,
                                const QuantizedVector* left,
                                const QuantizedVector* right) {
    for (int index = 0; index < 6; ++index) {
        destination->components[index] =
            left->components[index] + right->components[index];
    }
    QuantizedVector_UpdateBytes(destination);
    return destination;
}

#endif // TH10_MATH_QUANTIZED_VECTOR_HPP
