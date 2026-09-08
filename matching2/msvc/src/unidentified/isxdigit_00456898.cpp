#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456898..0x004568D6: _isxdigit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_isxdigit_00456898() {
    __asm {
    L_00456898:
        call asm_getptd_00456357
    L_0045689d:
        mov eax,dword ptr [eax+64h]
    L_004568a0:
        cmp eax,dword ptr [data_0047320c]
    L_004568a6:
        je short L_004568ad
    L_004568a8:
        call asm_updatetlocinfo_00455ade
    L_004568ad:
        cmp dword ptr [eax+28h],1
    L_004568b1:
        jle short L_004568c6
    L_004568b3:
        push 80h
    L_004568b8:
        push dword ptr [esp+8]
    L_004568bc:
        push eax
    L_004568bd:
        call asm_isctype_mt_00455752
    L_004568c2:
        add esp,0Ch
    L_004568c5:
        ret
    L_004568c6:
        mov eax,dword ptr [eax+48h]
    L_004568c9:
        mov ecx,dword ptr [esp+4]
    L_004568cd:
        movzx eax,byte ptr [eax+ecx*2]
    L_004568d1:
        and eax,80h
    L_004568d6:
        ret
    }
}
