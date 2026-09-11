#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004066E0..0x00406765: FUN_004066e0
// Naked body preserves the retail register/stack ABI.

// 0x004066E0..0x00406765: FUN_004066e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004066e0_004066e0() {
    __asm {
    L_004066e0:
        push esi
    L_004066e1:
        mov esi,dword ptr [eax+ecx*4+14h]
    L_004066e5:
        test esi,esi
    L_004066e7:
        je short L_0040675f
    L_004066e9:
        lea esp,[esp+force_disp32_zero]
    L_004066f0:
        fld dword ptr [esi+3B4h]
    L_004066f6:
        fadd dword ptr [data_00470b4c]
    L_004066fc:
        fstp dword ptr [esi+33Ch]
    L_00406702:
        fld dword ptr [esi+3B8h]
    L_00406708:
        fadd dword ptr [data_00470b48]
    L_0040670e:
        fstp dword ptr [esi+340h]
    L_00406714:
        mov edx,dword ptr [esi+3BCh]
    L_0040671a:
        mov dword ptr [esi+344h],edx
    L_00406720:
        test dword ptr [esi+364h],8000000h
    L_0040672a:
        je short L_00406747
    L_0040672c:
        mov eax,dword ptr [esi+3E4h]
    L_00406732:
        push 3FC90FDBh
    L_00406737:
        push eax
    L_00406738:
        call asm_Angle_NormalizeSum_0044bc10
    L_0040673d:
        fstp dword ptr [esi+34h]
    L_00406740:
        or dword ptr [esi+364h],4
    L_00406747:
        mov ecx,dword ptr [data_00491c10]
    L_0040674d:
        lea eax,[esi+8]
    L_00406750:
        call asm_FUN_004451c0_004451c0
    L_00406755:
        mov esi,dword ptr [esi+44Ch]
    L_0040675b:
        test esi,esi
    L_0040675d:
        jne short L_004066f0
    L_0040675f:
        mov eax,1
    L_00406764:
        pop esi
    L_00406765:
        ret
    }
}
