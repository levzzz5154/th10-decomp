#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401D60..0x00401D80: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00401d60() {
    __asm {
    L_00401d60:
        mov ecx,dword ptr [esp+4]
    L_00401d64:
        mov edx,dword ptr [esp+8]
    L_00401d68:
        mov dword ptr [eax+3Ch],ecx
    L_00401d6b:
        mov ecx,dword ptr [eax+35Ch]
    L_00401d71:
        or ecx,8
    L_00401d74:
        mov dword ptr [eax+40h],edx
    L_00401d77:
        mov dword ptr [eax+35Ch],ecx
    L_00401d7d:
        ret 8
    L_00401d80:
        ret
    }
}
