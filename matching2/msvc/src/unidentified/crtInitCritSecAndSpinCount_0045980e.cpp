#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045980E..0x0045986A: ___crtInitCritSecAndSpinCount
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_crtInitCritSecAndSpinCount_0045980e() {
    __asm {
    L_0045980e:
        push 10h
    L_00459810:
        push 46B090h
    L_00459815:
        call asm_SEH_prolog_00454bbc
    L_0045981a:
        mov eax,dword ptr [data_004775c4]
    L_0045981f:
        test eax,eax
    L_00459821:
        jne short L_0045985a
    L_00459823:
        cmp dword ptr [data_00477470],1
    L_0045982a:
        je short L_00459850
    L_0045982c:
        push 46AA5Ch
    L_00459831:
        call dword ptr [data_00466198]
    L_00459837:
        test eax,eax
    L_00459839:
        je short L_00459850
    L_0045983b:
        push 46B064h
    L_00459840:
        push eax
    L_00459841:
        call dword ptr [data_00466158]
    L_00459847:
        mov dword ptr [data_004775c4],eax
    L_0045984c:
        test eax,eax
    L_0045984e:
        jne short L_0045985a
    L_00459850:
        mov eax,4597FEh
    L_00459855:
        mov dword ptr [data_004775c4],eax
    L_0045985a:
        and dword ptr [ebp-4],0
    L_0045985e:
        push dword ptr [ebp+0Ch]
    L_00459861:
        push dword ptr [ebp+8]
    L_00459864:
        call eax
    L_00459866:
        mov dword ptr [ebp-20h],eax
    L_00459869:
        TH10_REL8(0xeb, 0x00459869, VA_asm_crtInitCritSecAndSpinCount_part_0045988f)
    }
}

// 0x0045988F..0x00459898: ___crtInitCritSecAndSpinCount
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_crtInitCritSecAndSpinCount_part_0045988f() {
    __asm {
    L_0045988f:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00459893:
        call asm_SEH_epilog_00454bf7
    L_00459898:
        ret
    }
}
