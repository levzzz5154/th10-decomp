#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004557FC..0x004558CB: ___freetlocinfo
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_freetlocinfo_004557fc() {
    __asm {
    L_004557fc:
        push esi
    L_004557fd:
        mov esi,dword ptr [esp+8]
    L_00455801:
        mov eax,dword ptr [esi+3Ch]
    L_00455804:
        push edi
    L_00455805:
        xor edi,edi
    L_00455807:
        cmp eax,dword ptr [data_00477624]
    L_0045580d:
        je short L_00455872
    L_0045580f:
        cmp eax,edi
    L_00455811:
        je short L_00455872
    L_00455813:
        mov eax,dword ptr [esi+2Ch]
    L_00455816:
        cmp dword ptr [eax],edi
    L_00455818:
        jne short L_00455872
    L_0045581a:
        mov eax,dword ptr [esi+34h]
    L_0045581d:
        cmp eax,edi
    L_0045581f:
        je short L_0045583d
    L_00455821:
        cmp dword ptr [eax],edi
    L_00455823:
        jne short L_0045583d
    L_00455825:
        cmp eax,dword ptr [data_004981c8]
    L_0045582b:
        je short L_0045583d
    L_0045582d:
        push eax
    L_0045582e:
        call asm_free_00452422
    L_00455833:
        push dword ptr [esi+3Ch]
    L_00455836:
        call asm_free_lconv_mon_0045b81b
    L_0045583b:
        pop ecx
    L_0045583c:
        pop ecx
    L_0045583d:
        mov eax,dword ptr [esi+30h]
    L_00455840:
        cmp eax,edi
    L_00455842:
        je short L_00455860
    L_00455844:
        cmp dword ptr [eax],edi
    L_00455846:
        jne short L_00455860
    L_00455848:
        cmp eax,dword ptr [data_004981d0]
    L_0045584e:
        je short L_00455860
    L_00455850:
        push eax
    L_00455851:
        call asm_free_00452422
    L_00455856:
        push dword ptr [esi+3Ch]
    L_00455859:
        call asm_free_lconv_num_0045b5bc
    L_0045585e:
        pop ecx
    L_0045585f:
        pop ecx
    L_00455860:
        push dword ptr [esi+2Ch]
    L_00455863:
        call asm_free_00452422
    L_00455868:
        push dword ptr [esi+3Ch]
    L_0045586b:
        call asm_free_00452422
    L_00455870:
        pop ecx
    L_00455871:
        pop ecx
    L_00455872:
        mov eax,dword ptr [esi+40h]
    L_00455875:
        cmp eax,dword ptr [data_004981c4]
    L_0045587b:
        je short L_0045589b
    L_0045587d:
        cmp eax,edi
    L_0045587f:
        je short L_0045589b
    L_00455881:
        cmp dword ptr [eax],edi
    L_00455883:
        jne short L_0045589b
    L_00455885:
        push eax
    L_00455886:
        call asm_free_00452422
    L_0045588b:
        mov eax,dword ptr [esi+44h]
    L_0045588e:
        sub eax,0FEh
    L_00455893:
        push eax
    L_00455894:
        call asm_free_00452422
    L_00455899:
        pop ecx
    L_0045589a:
        pop ecx
    L_0045589b:
        mov eax,dword ptr [esi+50h]
    L_0045589e:
        cmp eax,dword ptr [data_00477620]
    L_004558a4:
        je short L_004558c2
    L_004558a6:
        cmp eax,edi
    L_004558a8:
        je short L_004558c2
    L_004558aa:
        cmp dword ptr [eax+0B4h],edi
    L_004558b0:
        jne short L_004558c2
    L_004558b2:
        push eax
    L_004558b3:
        call asm_free_lc_time_0045b39a
    L_004558b8:
        push dword ptr [esi+50h]
    L_004558bb:
        call asm_free_00452422
    L_004558c0:
        pop ecx
    L_004558c1:
        pop ecx
    L_004558c2:
        push esi
    L_004558c3:
        call asm_free_00452422
    L_004558c8:
        pop ecx
    L_004558c9:
        pop edi
    L_004558ca:
        pop esi
    L_004558cb:
        ret
    }
}
