#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004245C0..0x004245C3: FUN_004245c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004245c0_004245c0() {
    __asm {
    L_004245c0:
        mov eax,dword ptr [eax+14h]
    L_004245c3:
        ret
    }
}
