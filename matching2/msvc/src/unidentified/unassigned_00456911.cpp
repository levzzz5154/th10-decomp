#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456911..0x00456A8A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00456911() {
    __asm {
    L_00456911:
        call asm_getptd_00456357
    L_00456916:
        mov eax,dword ptr [eax+64h]
    L_00456919:
        cmp eax,dword ptr [data_0047320c]
    L_0045691f:
        je short L_00456926
    L_00456921:
        call asm_updatetlocinfo_00455ade
    L_00456926:
        cmp dword ptr [eax+28h],1
    L_0045692a:
        jle short L_0045693c
    L_0045692c:
        push 10h
    L_0045692e:
        push dword ptr [esp+8]
    L_00456932:
        push eax
    L_00456933:
        call asm_isctype_mt_00455752
    L_00456938:
        add esp,0Ch
    L_0045693b:
        ret
    L_0045693c:
        mov eax,dword ptr [eax+48h]
    L_0045693f:
        mov ecx,dword ptr [esp+4]
    L_00456943:
        movzx eax,byte ptr [eax+ecx*2]
    L_00456947:
        and eax,10h
    L_0045694a:
        ret
    L_0045694b:
        call asm_getptd_00456357
    L_00456950:
        mov eax,dword ptr [eax+64h]
    L_00456953:
        cmp eax,dword ptr [data_0047320c]
    L_00456959:
        je short L_00456960
    L_0045695b:
        call asm_updatetlocinfo_00455ade
    L_00456960:
        cmp dword ptr [eax+28h],1
    L_00456964:
        jle short L_00456979
    L_00456966:
        push 107h
    L_0045696b:
        push dword ptr [esp+8]
    L_0045696f:
        push eax
    L_00456970:
        call asm_isctype_mt_00455752
    L_00456975:
        add esp,0Ch
    L_00456978:
        ret
    L_00456979:
        mov eax,dword ptr [eax+48h]
    L_0045697c:
        mov ecx,dword ptr [esp+4]
    L_00456980:
        movzx eax,word ptr [eax+ecx*2]
    L_00456984:
        and eax,107h
    L_00456989:
        ret
    L_0045698a:
        call asm_getptd_00456357
    L_0045698f:
        mov eax,dword ptr [eax+64h]
    L_00456992:
        cmp eax,dword ptr [data_0047320c]
    L_00456998:
        je short L_0045699f
    L_0045699a:
        call asm_updatetlocinfo_00455ade
    L_0045699f:
        cmp dword ptr [eax+28h],1
    L_004569a3:
        jle short L_004569b8
    L_004569a5:
        push 157h
    L_004569aa:
        push dword ptr [esp+8]
    L_004569ae:
        push eax
    L_004569af:
        call asm_isctype_mt_00455752
    L_004569b4:
        add esp,0Ch
    L_004569b7:
        ret
    L_004569b8:
        mov eax,dword ptr [eax+48h]
    L_004569bb:
        mov ecx,dword ptr [esp+4]
    L_004569bf:
        movzx eax,word ptr [eax+ecx*2]
    L_004569c3:
        and eax,157h
    L_004569c8:
        ret
    L_004569c9:
        call asm_getptd_00456357
    L_004569ce:
        mov eax,dword ptr [eax+64h]
    L_004569d1:
        cmp eax,dword ptr [data_0047320c]
    L_004569d7:
        je short L_004569de
    L_004569d9:
        call asm_updatetlocinfo_00455ade
    L_004569de:
        cmp dword ptr [eax+28h],1
    L_004569e2:
        jle short L_004569f7
    L_004569e4:
        push 117h
    L_004569e9:
        push dword ptr [esp+8]
    L_004569ed:
        push eax
    L_004569ee:
        call asm_isctype_mt_00455752
    L_004569f3:
        add esp,0Ch
    L_004569f6:
        ret
    L_004569f7:
        mov eax,dword ptr [eax+48h]
    L_004569fa:
        mov ecx,dword ptr [esp+4]
    L_004569fe:
        movzx eax,word ptr [eax+ecx*2]
    L_00456a02:
        and eax,117h
    L_00456a07:
        ret
    L_00456a08:
        call asm_getptd_00456357
    L_00456a0d:
        mov eax,dword ptr [eax+64h]
    L_00456a10:
        cmp eax,dword ptr [data_0047320c]
    L_00456a16:
        je short L_00456a1d
    L_00456a18:
        call asm_updatetlocinfo_00455ade
    L_00456a1d:
        cmp dword ptr [eax+28h],1
    L_00456a21:
        jle short L_00456a33
    L_00456a23:
        push 20h
    L_00456a25:
        push dword ptr [esp+8]
    L_00456a29:
        push eax
    L_00456a2a:
        call asm_isctype_mt_00455752
    L_00456a2f:
        add esp,0Ch
    L_00456a32:
        ret
    L_00456a33:
        mov eax,dword ptr [eax+48h]
    L_00456a36:
        mov ecx,dword ptr [esp+4]
    L_00456a3a:
        movzx eax,byte ptr [eax+ecx*2]
    L_00456a3e:
        and eax,20h
    L_00456a41:
        ret
    L_00456a42:
        cmp dword ptr [esp+4],80h
    L_00456a4a:
        sbb eax,eax
    L_00456a4c:
        neg eax
    L_00456a4e:
        ret
    L_00456a4f:
        mov eax,dword ptr [esp+4]
    L_00456a53:
        and eax,7Fh
    L_00456a56:
        ret
    L_00456a57:
        push dword ptr [esp+4]
    L_00456a5b:
        call asm_unassigned_004567ab
    L_00456a60:
        test eax,eax
    L_00456a62:
        pop ecx
    L_00456a63:
        jne short L_00456a6d
    L_00456a65:
        cmp dword ptr [esp+4],5Fh
    L_00456a6a:
        je short L_00456a6d
    L_00456a6c:
        ret
    L_00456a6d:
        xor eax,eax
    L_00456a6f:
        inc eax
    L_00456a70:
        ret
    L_00456a71:
        push dword ptr [esp+4]
    L_00456a75:
        call asm_target_0045694b
    L_00456a7a:
        test eax,eax
    L_00456a7c:
        pop ecx
    L_00456a7d:
        jne short L_00456a87
    L_00456a7f:
        cmp dword ptr [esp+4],5Fh
    L_00456a84:
        je short L_00456a87
    L_00456a86:
        ret
    L_00456a87:
        xor eax,eax
    L_00456a89:
        inc eax
    L_00456a8a:
        ret
    }
}
