#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412F10..0x00412F19: FUN_00412f10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412f10_00412f10() {
    __asm {
    L_00412f10:
        mov eax,dword ptr [esp+4]
    L_00412f14:
        mov dword ptr [ecx+10h],eax
    L_00412f17:
        ret 4
    }
}
