#include "asm_symbols.hpp"

// Semantic model for 0x00452E04..0x00452E09. This leaf releases the CRT
// on-exit lock by forwarding to the lock-specific helper.
extern "C" void __cdecl asm_FUN_00452e04_00452e04() {
    asm_FUN_00457580_00457580();
}
