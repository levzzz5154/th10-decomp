#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004389B0..0x004389B2: FUN_004389b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004389b0_004389b0() {
    __asm {
    L_004389b0:
        mov dword ptr [eax],ecx
    L_004389b2:
        ret
    }
}
