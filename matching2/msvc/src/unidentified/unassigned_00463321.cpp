#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463321..0x00463329: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00463321() {
    __asm {
    L_00463321:
        inc edx
    L_00463322:
        TH10_REL8(0xeb, 0x00463322, VA_asm_target_004632cc)
    L_00463324:
        mov edi,dword ptr [ebp+0Ch]
    L_00463327:
        mov esi,dword ptr [ebp+8]
    }
}
