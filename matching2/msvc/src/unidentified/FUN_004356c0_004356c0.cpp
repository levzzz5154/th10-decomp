#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004356C0..0x004356C6: FUN_004356c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004356c0_004356c0() {
    __asm {
    L_004356c0:
        mov dword ptr [eax],46F210h
    L_004356c6:
        ret
    }
}
