#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441E00..0x00441E32: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00441e00() {
    __asm {
    L_00441e00:
        fld dword ptr [ecx+4]
    L_00441e03:
        fadd dword ptr [edx+4]
    L_00441e06:
        fld dword ptr [ecx]
    L_00441e08:
        fadd dword ptr [edx]
    L_00441e0a:
        fstp dword ptr [eax]
    L_00441e0c:
        fstp dword ptr [eax+4]
    L_00441e0f:
        ret
    L_00441e10:
        mov edx,dword ptr [esi+4]
    L_00441e13:
        push ebx
    L_00441e14:
        mov ebx,dword ptr [esi+8]
    L_00441e17:
        push edi
    L_00441e18:
        mov edi,ecx
    L_00441e1a:
        mov ecx,dword ptr [edi+4]
    L_00441e1d:
        sub ecx,edx
    L_00441e1f:
        mov edx,dword ptr [edi+8]
    L_00441e22:
        mov edi,dword ptr [edi]
    L_00441e24:
        sub edx,ebx
    L_00441e26:
        sub edi,dword ptr [esi]
    L_00441e28:
        mov dword ptr [eax],edi
    L_00441e2a:
        pop edi
    L_00441e2b:
        mov dword ptr [eax+4],ecx
    L_00441e2e:
        mov dword ptr [eax+8],edx
    L_00441e31:
        pop ebx
    L_00441e32:
        ret
    }
}
