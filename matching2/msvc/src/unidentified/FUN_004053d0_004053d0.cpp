#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004053D0..0x004053D3: FUN_004053d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004053d0_004053d0() {
    __asm {
    L_004053d0:
        mov eax,dword ptr [eax+3Ch]
    L_004053d3:
        ret
    }
}
