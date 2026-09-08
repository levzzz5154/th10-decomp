#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004524A1..0x004524A5: _free
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_free_004524a1() {
    __asm {
    L_004524a1:
        jmp asm_free_00452422
    }
}
