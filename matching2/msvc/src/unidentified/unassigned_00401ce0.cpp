#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401CE0..0x00401D0B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00401ce0() {
    __asm {
    L_00401ce0:
        mov ecx,dword ptr [esp+4]
    L_00401ce4:
        mov edx,dword ptr [esp+8]
    L_00401ce8:
        mov dword ptr [eax+4Ch],ecx
    L_00401ceb:
        mov ecx,dword ptr [eax+35Ch]
    L_00401cf1:
        or ecx,8
    L_00401cf4:
        mov dword ptr [eax+50h],edx
    L_00401cf7:
        mov dword ptr [eax+35Ch],ecx
    L_00401cfd:
        ret 8
    L_00401d00:
        mov edx,dword ptr [ecx+118h]
    L_00401d06:
        imul eax,44h
    L_00401d09:
        add eax,edx
    L_00401d0b:
        ret
    }
}
