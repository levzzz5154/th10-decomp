#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004567AB..0x0045685D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004567ab() {
    __asm {
    L_004567ab:
        call asm_getptd_00456357
    L_004567b0:
        mov eax,dword ptr [eax+64h]
    L_004567b3:
        cmp eax,dword ptr [data_0047320c]
    L_004567b9:
        je short L_004567c0
    L_004567bb:
        call asm_updatetlocinfo_00455ade
    L_004567c0:
        cmp dword ptr [eax+28h],1
    L_004567c4:
        jle short L_004567d9
    L_004567c6:
        push 103h
    L_004567cb:
        push dword ptr [esp+8]
    L_004567cf:
        push eax
    L_004567d0:
        call asm_isctype_mt_00455752
    L_004567d5:
        add esp,0Ch
    L_004567d8:
        ret
    L_004567d9:
        mov eax,dword ptr [eax+48h]
    L_004567dc:
        mov ecx,dword ptr [esp+4]
    L_004567e0:
        movzx eax,word ptr [eax+ecx*2]
    L_004567e4:
        and eax,103h
    L_004567e9:
        ret
    L_004567ea:
        call asm_getptd_00456357
    L_004567ef:
        mov eax,dword ptr [eax+64h]
    L_004567f2:
        cmp eax,dword ptr [data_0047320c]
    L_004567f8:
        je short L_004567ff
    L_004567fa:
        call asm_updatetlocinfo_00455ade
    L_004567ff:
        cmp dword ptr [eax+28h],1
    L_00456803:
        jle short L_00456815
    L_00456805:
        push 1
    L_00456807:
        push dword ptr [esp+8]
    L_0045680b:
        push eax
    L_0045680c:
        call asm_isctype_mt_00455752
    L_00456811:
        add esp,0Ch
    L_00456814:
        ret
    L_00456815:
        mov eax,dword ptr [eax+48h]
    L_00456818:
        mov ecx,dword ptr [esp+4]
    L_0045681c:
        movzx eax,byte ptr [eax+ecx*2]
    L_00456820:
        and eax,1
    L_00456823:
        ret
    L_00456824:
        call asm_getptd_00456357
    L_00456829:
        mov eax,dword ptr [eax+64h]
    L_0045682c:
        cmp eax,dword ptr [data_0047320c]
    L_00456832:
        je short L_00456839
    L_00456834:
        call asm_updatetlocinfo_00455ade
    L_00456839:
        cmp dword ptr [eax+28h],1
    L_0045683d:
        jle short L_0045684f
    L_0045683f:
        push 2
    L_00456841:
        push dword ptr [esp+8]
    L_00456845:
        push eax
    L_00456846:
        call asm_isctype_mt_00455752
    L_0045684b:
        add esp,0Ch
    L_0045684e:
        ret
    L_0045684f:
        mov eax,dword ptr [eax+48h]
    L_00456852:
        mov ecx,dword ptr [esp+4]
    L_00456856:
        movzx eax,byte ptr [eax+ecx*2]
    L_0045685a:
        and eax,2
    L_0045685d:
        ret
    }
}
