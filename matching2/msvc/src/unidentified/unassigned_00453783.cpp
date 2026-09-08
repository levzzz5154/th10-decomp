#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453783..0x004537DB: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00453783() {
    __asm {
    L_00453783:
        pop ecx
    L_00453784:
        pop ecx
    L_00453785:
        ret
    L_00453786:
        push 0
    L_00453788:
        call dword ptr [data_00466198]
    L_0045378e:
        cmp word ptr [eax],5A4Dh
    L_00453793:
        jne short L_004537b4
    L_00453795:
        mov ecx,dword ptr [eax+3Ch]
    L_00453798:
        add ecx,eax
    L_0045379a:
        cmp dword ptr [ecx],4550h
    L_004537a0:
        jne short L_004537b4
    L_004537a2:
        movzx eax,word ptr [ecx+18h]
    L_004537a6:
        cmp eax,10Bh
    L_004537ab:
        je short L_004537ca
    L_004537ad:
        cmp eax,20Bh
    L_004537b2:
        je short L_004537b7
    L_004537b4:
        xor eax,eax
    L_004537b6:
        ret
    L_004537b7:
        xor eax,eax
    L_004537b9:
        cmp dword ptr [ecx+84h],0Eh
    L_004537c0:
        jbe short L_004537db
    L_004537c2:
        cmp dword ptr [ecx+0F8h],eax
    L_004537c8:
        jmp short L_004537d8
    L_004537ca:
        xor eax,eax
    L_004537cc:
        cmp dword ptr [ecx+74h],0Eh
    L_004537d0:
        jbe short L_004537db
    L_004537d2:
        cmp dword ptr [ecx+0E8h],eax
    L_004537d8:
        setne al
    L_004537db:
        ret
    }
}
