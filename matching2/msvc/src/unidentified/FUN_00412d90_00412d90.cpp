#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412D90..0x00412D9B: FUN_00412d90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412d90_00412d90() {
    __asm {
    L_00412d90:
        mov edx,dword ptr [eax]
    L_00412d92:
        mov dword ptr [ecx+18h],edx
    L_00412d95:
        mov eax,dword ptr [eax+4]
    L_00412d98:
        mov dword ptr [ecx+1Ch],eax
    L_00412d9b:
        ret
    }
}
