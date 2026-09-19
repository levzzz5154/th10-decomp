#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421C0B..0x00421C49: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421c0b() {
    __asm {
    L_00421c0b:
        mov ecx,dword ptr [esp+4]
    L_00421c0f:
        mov dword ptr [eax],ecx
    L_00421c11:
        mov ecx,dword ptr [esp+8]
    L_00421c15:
        mov dword ptr [eax+2Ch],edx
    L_00421c18:
        mov edx,dword ptr [esp+0Ch]
    L_00421c1c:
        mov dword ptr [eax+30h],ecx
    L_00421c1f:
        mov ecx,dword ptr [esp+10h]
    L_00421c23:
        mov dword ptr [eax+34h],edx
    L_00421c26:
        mov edx,dword ptr [esp+14h]
    L_00421c2a:
        mov dword ptr [eax+38h],ecx
    L_00421c2d:
        mov ecx,dword ptr [esp+18h]
    L_00421c31:
        mov dword ptr [eax+3Ch],edx
    L_00421c34:
        mov edx,dword ptr [esp+1Ch]
    L_00421c38:
        mov dword ptr [eax+40h],ecx
    L_00421c3b:
        mov ecx,dword ptr [esp+20h]
    L_00421c3f:
        mov dword ptr [eax+44h],edx
    L_00421c42:
        mov dword ptr [eax+48h],ecx
    L_00421c45:
        xor eax,eax
    L_00421c47:
        ret 20h
    }
}
