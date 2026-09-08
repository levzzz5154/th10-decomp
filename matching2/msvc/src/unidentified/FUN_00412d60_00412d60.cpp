#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412D60..0x00412D6A: FUN_00412d60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412d60_00412d60() {
    __asm {
    L_00412d60:
        mov edx,dword ptr [eax]
    L_00412d62:
        mov dword ptr [ecx],edx
    L_00412d64:
        mov eax,dword ptr [eax+4]
    L_00412d67:
        mov dword ptr [ecx+4],eax
    L_00412d6a:
        ret
    }
}
