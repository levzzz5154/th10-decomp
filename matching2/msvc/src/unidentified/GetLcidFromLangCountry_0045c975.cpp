#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045C975..0x0045C9FA: _GetLcidFromLangCountry
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GetLcidFromLangCountry_0045c975() {
    __asm {
    L_0045c975:
        push dword ptr [data_00477644]
    L_0045c97b:
        call asm_strlen_00456720
    L_0045c980:
        push dword ptr [data_0047763c]
    L_0045c986:
        sub eax,3
    L_0045c989:
        neg eax
    L_0045c98b:
        sbb eax,eax
    L_0045c98d:
        inc eax
    L_0045c98e:
        mov dword ptr [data_00477634],eax
    L_0045c993:
        call asm_strlen_00456720
    L_0045c998:
        sub eax,3
    L_0045c99b:
        neg eax
    L_0045c99d:
        sbb eax,eax
    L_0045c99f:
        and dword ptr [data_0047762c],0
    L_0045c9a6:
        inc eax
    L_0045c9a7:
        cmp dword ptr [data_00477634],0
    L_0045c9ae:
        pop ecx
    L_0045c9af:
        pop ecx
    L_0045c9b0:
        mov dword ptr [data_00477638],eax
    L_0045c9b5:
        je short L_0045c9c3
    L_0045c9b7:
        mov dword ptr [data_00477640],2
    L_0045c9c1:
        jmp short L_0045c9d3
    L_0045c9c3:
        mov edx,dword ptr [data_00477644]
    L_0045c9c9:
        call asm_GetPrimaryLen_0045c527
    L_0045c9ce:
        mov dword ptr [data_00477640],eax
    L_0045c9d3:
        push 1
    L_0045c9d5:
        push 45C651h
    L_0045c9da:
        call dword ptr [data_00466058]
    L_0045c9e0:
        mov eax,dword ptr [data_00477628]
    L_0045c9e5:
        test ah,1
    L_0045c9e8:
        je short L_0045c9f3
    L_0045c9ea:
        test ah,2
    L_0045c9ed:
        je short L_0045c9f3
    L_0045c9ef:
        test al,7
    L_0045c9f1:
        jne short L_0045c9fa
    L_0045c9f3:
        and dword ptr [data_00477628],0
    L_0045c9fa:
        ret
    }
}
