#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412D80..0x00412D8B: FUN_00412d80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412d80_00412d80() {
    __asm {
    L_00412d80:
        mov edx,dword ptr [eax]
    L_00412d82:
        mov dword ptr [ecx+10h],edx
    L_00412d85:
        mov eax,dword ptr [eax+4]
    L_00412d88:
        mov dword ptr [ecx+14h],eax
    L_00412d8b:
        ret
    }
}
