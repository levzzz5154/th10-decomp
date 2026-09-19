#include "th10/math/rng.hpp"

// 0x0043CB80..0x0043CBD7: generate two words and reduce the packed value.
struct EntityScriptRng_0043cb80 : RngState {
    __declspec(noinline) unsigned int NextRandomModulo(unsigned int modulus);
};

#pragma code_seg(".text$01rng")
unsigned int EntityScriptRng_0043cb80::NextRandomModulo(unsigned int modulus) {
    if (modulus == 0)
        return 0;
    unsigned short high = NextWord();
    unsigned short low = NextWord();
    return ((static_cast<unsigned int>(high) << 16) | low) % modulus;
}
#pragma code_seg()
