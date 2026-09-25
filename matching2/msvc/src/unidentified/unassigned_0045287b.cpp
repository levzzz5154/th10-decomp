#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045287B..0x00452921: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) __int64 __cdecl asm_unassigned_0045287b(const char* text) {
    __asm {
    L_0045287b:
        push ebx
    L_0045287c:
        push ebp
    L_0045287d:
        push esi
    L_0045287e:
        push edi
    L_0045287f:
        call asm_getptd_00456357
    L_00452884:
        mov edi,dword ptr [eax+64h]
    L_00452887:
        cmp edi,dword ptr [data_0047320c]
    L_0045288d:
        je short L_00452896
    L_0045288f:
        call asm_updatetlocinfo_00455ade
    L_00452894:
        mov edi,eax
    L_00452896:
        mov esi,dword ptr [esp+14h]
    L_0045289a:
        cmp dword ptr [edi+28h],1
    L_0045289e:
        movzx eax,byte ptr [esi]
    L_004528a1:
        jle short L_004528b1
    L_004528a3:
        push 8
    L_004528a5:
        push eax
    L_004528a6:
        push edi
    L_004528a7:
        call asm_isctype_mt_00455752
    L_004528ac:
        add esp,0Ch
    L_004528af:
        jmp short L_004528bb
    L_004528b1:
        mov ecx,dword ptr [edi+48h]
    L_004528b4:
        movzx eax,byte ptr [ecx+eax*2]
    L_004528b8:
        and eax,8
    L_004528bb:
        test eax,eax
    L_004528bd:
        je short L_004528c2
    L_004528bf:
        inc esi
    L_004528c0:
        jmp short L_0045289a
    L_004528c2:
        movzx edi,byte ptr [esi]
    L_004528c5:
        inc esi
    L_004528c6:
        cmp edi,2Dh
    L_004528c9:
        mov ebx,edi
    L_004528cb:
        je short L_004528d2
    L_004528cd:
        cmp edi,2Bh
    L_004528d0:
        jne short L_004528d6
    L_004528d2:
        movzx edi,byte ptr [esi]
    L_004528d5:
        inc esi
    L_004528d6:
        xor eax,eax
    L_004528d8:
        xor edx,edx
    L_004528da:
        cmp edi,30h
    L_004528dd:
        jl short L_004528e9
    L_004528df:
        cmp edi,39h
    L_004528e2:
        jg short L_004528e9
    L_004528e4:
        sub edi,30h
    L_004528e7:
        jmp short L_004528ec
    L_004528e9:
        or edi,0FFFFFFFFh
    L_004528ec:
        cmp edi,0FFFFFFFFh
    L_004528ef:
        je short L_00452911
    L_004528f1:
        push 0
    L_004528f3:
        push 0Ah
    L_004528f5:
        push edx
    L_004528f6:
        push eax
    L_004528f7:
        call asm_allmul_00456640
    L_004528fc:
        mov ecx,eax
    L_004528fe:
        mov ebp,edx
    L_00452900:
        mov eax,edi
    L_00452902:
        movzx edi,byte ptr [esi]
    L_00452905:
        cdq
    L_00452906:
        add ecx,eax
    L_00452908:
        adc ebp,edx
    L_0045290a:
        mov eax,ecx
    L_0045290c:
        mov edx,ebp
    L_0045290e:
        inc esi
    L_0045290f:
        jmp short L_004528da
    L_00452911:
        pop edi
    L_00452912:
        pop esi
    L_00452913:
        pop ebp
    L_00452914:
        cmp ebx,2Dh
    L_00452917:
        pop ebx
    L_00452918:
        jne short L_00452921
    L_0045291a:
        neg eax
    L_0045291c:
        adc edx,0
    L_0045291f:
        neg edx
    L_00452921:
        ret
    }
}
