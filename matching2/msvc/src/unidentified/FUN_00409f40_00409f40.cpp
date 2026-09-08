#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409F40..0x00409F49: FUN_00409f40
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409f40_00409f40() {
    __asm {
    L_00409f40:
        mov ecx,dword ptr [eax+8Ch]
    L_00409f46:
        mov eax,dword ptr [ecx+edx*8]
    L_00409f49:
        ret
    }
}
