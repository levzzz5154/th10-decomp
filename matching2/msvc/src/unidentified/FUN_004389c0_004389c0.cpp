#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004389C0..0x004389C3: FUN_004389c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004389c0_004389c0() {
    __asm {
    L_004389c0:
        mov dword ptr [eax+4],ecx
    L_004389c3:
        ret
    }
}
