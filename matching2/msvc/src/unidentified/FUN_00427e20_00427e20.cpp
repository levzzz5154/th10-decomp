#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427E20..0x00427E36: FUN_00427e20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00427e20_00427e20() {
    __asm {
    L_00427e20:
        push esi
    L_00427e21:
        mov esi,dword ptr [edx]
    L_00427e23:
        mov dword ptr [ecx],esi
    L_00427e25:
        mov edx,dword ptr [edx+4]
    L_00427e28:
        mov dword ptr [ecx+4],edx
    L_00427e2b:
        mov edx,esi
    L_00427e2d:
        mov dword ptr [eax],edx
    L_00427e2f:
        mov ecx,dword ptr [ecx+4]
    L_00427e32:
        mov dword ptr [eax+4],ecx
    L_00427e35:
        pop esi
    L_00427e36:
        ret
    }
}
