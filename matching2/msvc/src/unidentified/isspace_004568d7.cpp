#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004568D7..0x00456910: _isspace
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_isspace_004568d7() {
    __asm {
    L_004568d7:
        call asm_getptd_00456357
    L_004568dc:
        mov eax,dword ptr [eax+64h]
    L_004568df:
        cmp eax,dword ptr [data_0047320c]
    L_004568e5:
        je short L_004568ec
    L_004568e7:
        call asm_updatetlocinfo_00455ade
    L_004568ec:
        cmp dword ptr [eax+28h],1
    L_004568f0:
        jle short L_00456902
    L_004568f2:
        push 8
    L_004568f4:
        push dword ptr [esp+8]
    L_004568f8:
        push eax
    L_004568f9:
        call asm_isctype_mt_00455752
    L_004568fe:
        add esp,0Ch
    L_00456901:
        ret
    L_00456902:
        mov eax,dword ptr [eax+48h]
    L_00456905:
        mov ecx,dword ptr [esp+4]
    L_00456909:
        movzx eax,byte ptr [eax+ecx*2]
    L_0045690d:
        and eax,8
    L_00456910:
        ret
    }
}
