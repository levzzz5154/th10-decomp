#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C850..0x0042C894: GameProgress_HasAnyPlayRecord
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameProgress_HasAnyPlayRecord_0042c850() {
    __asm {
    L_0042c850:
        mov cl,byte ptr [eax+1D888h]
    L_0042c856:
        test cl,cl
    L_0042c858:
        jne short L_0042c88f
    L_0042c85a:
        mov cl,byte ptr [eax+1D889h]
    L_0042c860:
        test cl,cl
    L_0042c862:
        jne short L_0042c88f
    L_0042c864:
        mov cl,byte ptr [eax+1D88Ah]
    L_0042c86a:
        test cl,cl
    L_0042c86c:
        jne short L_0042c88f
    L_0042c86e:
        mov cl,byte ptr [eax+1D88Bh]
    L_0042c874:
        test cl,cl
    L_0042c876:
        jne short L_0042c88f
    L_0042c878:
        mov cl,byte ptr [eax+1D88Ch]
    L_0042c87e:
        test cl,cl
    L_0042c880:
        jne short L_0042c88f
    L_0042c882:
        mov cl,byte ptr [eax+1D88Dh]
    L_0042c888:
        test cl,cl
    L_0042c88a:
        jne short L_0042c88f
    L_0042c88c:
        xor eax,eax
    L_0042c88e:
        ret
    L_0042c88f:
        mov eax,1
    L_0042c894:
        ret
    }
}

// 0x0042C8C0..0x0042C8F8: ?GameProgress_UnlockAllStages@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameProgress_UnlockAllStages_0042c8c0() {
    __asm {
    L_0042c8c0:
        mov ecx,1010101h
    L_0042c8c5:
        mov dword ptr [eax+1D882h],ecx
    L_0042c8cb:
        mov dword ptr [eax+1D886h],ecx
    L_0042c8d1:
        push esi
    L_0042c8d2:
        mov dword ptr [eax+1D88Ah],ecx
    L_0042c8d8:
        push edi
    L_0042c8d9:
        mov dword ptr [eax+1D88Eh],ecx
    L_0042c8df:
        lea esi,[eax+4E9h]
    L_0042c8e5:
        mov edi,6
    L_0042c8ea:
        lea ebx,[ebx+force_disp32_zero]
    L_0042c8f0:
        mov eax,esi
    L_0042c8f2:
        mov edx,4
    L_0042c8f7:
        TH10_REL8(0xeb, 0x0042c8f7, VA_asm_GameProgress_UnlockAllStages_part_0042c900)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0042c900:
        mov ecx,6
    L_0042c905:
        mov byte ptr [eax],1
    L_0042c908:
        add eax,8
    L_0042c90b:
        dec ecx
    L_0042c90c:
        jne short L_0042c905
    L_0042c90e:
        dec edx
    L_0042c90f:
        jne short L_0042c900
    L_0042c911:
        add esi,437Ch
    L_0042c917:
        dec edi
    L_0042c918:
        TH10_REL8(0x75, 0x0042c918, VA_asm_target_0042c8f0)
    L_0042c91a:
        pop edi
    L_0042c91b:
        pop esi
    L_0042c91c:
        ret
    }
}
