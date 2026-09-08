#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004558CC..0x0045598C: ___updatetlocinfo_lk
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_updatetlocinfo_lk_004558cc() {
    __asm {
    L_004558cc:
        push esi
    L_004558cd:
        call asm_getptd_00456357
    L_004558d2:
        mov esi,eax
    L_004558d4:
        mov ecx,dword ptr [esi+64h]
    L_004558d7:
        cmp ecx,dword ptr [data_0047320c]
    L_004558dd:
        je asm_target_00455988
    L_004558e3:
        xor edx,edx
    L_004558e5:
        cmp ecx,edx
    L_004558e7:
        je short L_00455918
    L_004558e9:
        mov eax,dword ptr [ecx+2Ch]
    L_004558ec:
        dec dword ptr [ecx]
    L_004558ee:
        cmp eax,edx
    L_004558f0:
        je short L_004558f4
    L_004558f2:
        dec dword ptr [eax]
    L_004558f4:
        mov eax,dword ptr [ecx+34h]
    L_004558f7:
        cmp eax,edx
    L_004558f9:
        je short L_004558fd
    L_004558fb:
        dec dword ptr [eax]
    L_004558fd:
        mov eax,dword ptr [ecx+30h]
    L_00455900:
        cmp eax,edx
    L_00455902:
        je short L_00455906
    L_00455904:
        dec dword ptr [eax]
    L_00455906:
        mov eax,dword ptr [ecx+40h]
    L_00455909:
        cmp eax,edx
    L_0045590b:
        je short L_0045590f
    L_0045590d:
        dec dword ptr [eax]
    L_0045590f:
        mov eax,dword ptr [ecx+4Ch]
    L_00455912:
        dec dword ptr [eax+0B4h]
    L_00455918:
        mov eax,dword ptr [data_0047320c]
    L_0045591d:
        mov dword ptr [esi+64h],eax
    L_00455920:
        mov eax,dword ptr [data_0047320c]
    L_00455925:
        inc dword ptr [eax]
    L_00455927:
        mov eax,dword ptr [data_0047320c]
    L_0045592c:
        cmp dword ptr [eax+2Ch],edx
    L_0045592f:
        je short L_0045593b
    L_00455931:
        mov eax,dword ptr [eax+2Ch]
    L_00455934:
        inc dword ptr [eax]
    L_00455936:
        mov eax,dword ptr [data_0047320c]
    L_0045593b:
        cmp dword ptr [eax+34h],edx
    L_0045593e:
        je short L_0045594a
    L_00455940:
        mov eax,dword ptr [eax+34h]
    L_00455943:
        inc dword ptr [eax]
    L_00455945:
        mov eax,dword ptr [data_0047320c]
    L_0045594a:
        cmp dword ptr [eax+30h],edx
    L_0045594d:
        je short L_00455959
    L_0045594f:
        mov eax,dword ptr [eax+30h]
    L_00455952:
        inc dword ptr [eax]
    L_00455954:
        mov eax,dword ptr [data_0047320c]
    L_00455959:
        cmp dword ptr [eax+40h],edx
    L_0045595c:
        je short L_00455968
    L_0045595e:
        mov eax,dword ptr [eax+40h]
    L_00455961:
        inc dword ptr [eax]
    L_00455963:
        mov eax,dword ptr [data_0047320c]
    L_00455968:
        mov eax,dword ptr [eax+4Ch]
    L_0045596b:
        inc dword ptr [eax+0B4h]
    L_00455971:
        cmp ecx,edx
    L_00455973:
        je short L_00455988
    L_00455975:
        cmp dword ptr [ecx],edx
    L_00455977:
        jne short L_00455988
    L_00455979:
        cmp ecx,4731B8h
    L_0045597f:
        je short L_00455988
    L_00455981:
        push ecx
    L_00455982:
        call asm_freetlocinfo_004557fc
    L_00455987:
        pop ecx
    L_00455988:
        mov eax,dword ptr [esi+64h]
    L_0045598b:
        pop esi
    L_0045598c:
        ret
    }
}
