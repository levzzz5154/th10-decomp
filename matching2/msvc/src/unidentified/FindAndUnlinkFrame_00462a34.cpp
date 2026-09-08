#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462A34..0x00462A7F: _FindAndUnlinkFrame
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FindAndUnlinkFrame_00462a34() {
    __asm {
    L_00462a34:
        push esi
    L_00462a35:
        call asm_getptd_00456357
    L_00462a3a:
        mov esi,dword ptr [esp+8]
    L_00462a3e:
        cmp esi,dword ptr [eax+88h]
    L_00462a44:
        jne short L_00462a56
    L_00462a46:
        call asm_getptd_00456357
    L_00462a4b:
        mov ecx,dword ptr [esi+4]
    L_00462a4e:
        mov dword ptr [eax+88h],ecx
    L_00462a54:
        pop esi
    L_00462a55:
        ret
    L_00462a56:
        call asm_getptd_00456357
    L_00462a5b:
        mov eax,dword ptr [eax+88h]
    L_00462a61:
        jmp short L_00462a6c
    L_00462a63:
        mov ecx,dword ptr [eax+4]
    L_00462a66:
        cmp esi,ecx
    L_00462a68:
        je short L_00462a78
    L_00462a6a:
        mov eax,ecx
    L_00462a6c:
        cmp dword ptr [eax+4],0
    L_00462a70:
        jne short L_00462a63
    L_00462a72:
        pop esi
    L_00462a73:
        jmp asm_inconsistency_004556e0
    L_00462a78:
        mov ecx,dword ptr [esi+4]
    L_00462a7b:
        mov dword ptr [eax+4],ecx
    L_00462a7e:
        pop esi
    L_00462a7f:
        ret
    }
}
