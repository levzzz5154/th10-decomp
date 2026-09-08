#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460CEE..0x00460D0F: _tolower
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_tolower_00460cee() {
    __asm {
    L_00460cee:
        call asm_getptd_00456357
    L_00460cf3:
        mov eax,dword ptr [eax+64h]
    L_00460cf6:
        cmp eax,dword ptr [data_0047320c]
    L_00460cfc:
        je short L_00460d03
    L_00460cfe:
        call asm_updatetlocinfo_00455ade
    L_00460d03:
        push dword ptr [esp+4]
    L_00460d07:
        push eax
    L_00460d08:
        call asm_tolower_mt_00460c26
    L_00460d0d:
        pop ecx
    L_00460d0e:
        pop ecx
    L_00460d0f:
        ret
    }
}
