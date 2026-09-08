#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409F30..0x00409F33: FUN_00409f30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409f30_00409f30() {
    __asm {
    L_00409f30:
        mov eax,dword ptr [eax+8]
    L_00409f33:
        ret
    }
}
