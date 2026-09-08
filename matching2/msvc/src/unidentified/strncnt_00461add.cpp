#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461ADD..0x00461AF8: _strncnt
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_strncnt_00461add() {
    __asm {
    L_00461add:
        mov ecx,dword ptr [esp+4]
    L_00461ae1:
        test ecx,ecx
    L_00461ae3:
        je short L_00461af0
    L_00461ae5:
        dec ecx
    L_00461ae6:
        cmp byte ptr [eax],0
    L_00461ae9:
        je short L_00461af1
    L_00461aeb:
        inc eax
    L_00461aec:
        test ecx,ecx
    L_00461aee:
        jne short L_00461ae5
    L_00461af0:
        dec ecx
    L_00461af1:
        mov eax,dword ptr [esp+4]
    L_00461af5:
        sub eax,ecx
    L_00461af7:
        dec eax
    L_00461af8:
        ret
    }
}
