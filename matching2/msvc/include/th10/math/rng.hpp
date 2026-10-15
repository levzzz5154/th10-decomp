#pragma once

// Retail RNG layout. Only seed participates in the 16-bit recurrence;
// generation counts generated words with unsigned 32-bit wraparound.
struct RngState {
    unsigned short seed;
    unsigned short reserved;
    unsigned int generation;

    // 0x0044B9B0 - Advance one word. The 16-bit intermediate truncates
    // subtraction before rotating; this width also preserves retail codegen.
    __forceinline unsigned short NextWord() {
        unsigned short value = seed ^ 0x9630;
        value -= 0x6553;
        seed = (value >> 14) + (value << 2);
        ++generation;
        return seed;
    }
};
typedef char RngState_size_check[sizeof(RngState) == 8 ? 1 : -1];

// 0x0043CB80 - generate two words and reduce the packed value. Defined in
// the class like the retail header: its out-of-line copy is emitted beside
// the screen effects that call it, and callers spill x87 values around it.
struct EntityScriptRng : RngState {
    unsigned int NextRandomModulo(unsigned int modulus) {
        if (modulus == 0)
            return 0;
        unsigned short high = NextWord();
        unsigned short low = NextWord();
        return ((static_cast<unsigned int>(high) << 16) | low) % modulus;
    }
};

unsigned int __fastcall Rng_NextU32(RngState* state);
unsigned int __fastcall Rng_NextU32Alternate(RngState* state);
unsigned int __fastcall Rng_NextU32DoubleStep(RngState* state);
float __fastcall Rng_NextFloat(RngState* state);
float __fastcall Rng_NextFloatSigned(RngState* state);
