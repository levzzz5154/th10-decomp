#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040678E..0x00406797: ?Player_ForwardAxisWrap@@
// Naked body preserves the retail register/stack ABI.

// 0x004074B0..0x00407553: PlayerAnimation_AdvanceFrame
// Naked body preserves the retail register/stack ABI.
// BLOCKED (D3704): closest_byte_count=0/164; first_diff=0x004074B0;
// residual_class=ESI receiver ABI, x87 evaluation ordering, and private
// player-animation layout; variants_tested=["live Ghidra decompile at
// 0x004074B0", "live caller 0x00406240", "MSVC 13.10 schema-2 baseline
// probe"]; next_lever=native-LTCG cluster with caller 0x00406240, typed
// Player layout, and co-compiled SetPolarVector/NormalizeFrame callees.
extern "C" __declspec(naked) void __cdecl asm_PlayerAnimation_AdvanceFrame_004074b0() {
    __asm {
    L_004074b0:
        cmp dword ptr [esi+618h],10h
    L_004074b7:
        jg short L_004074e9
    L_004074b9:
        fld dword ptr [esi+61Ch]
    L_004074bf:
        mov eax,dword ptr [esi+3E4h]
    L_004074c5:
        fmul dword ptr [data_00470c6c]
    L_004074cb:
        push ecx
    L_004074cc:
        lea ecx,[esi+3C0h]
    L_004074d2:
        fsubr dword ptr [data_00470c68]
    L_004074d8:
        fadd dword ptr [esi+3D8h]
    L_004074de:
        fstp dword ptr [esp]
    L_004074e1:
        push eax
    L_004074e2:
        call asm_Score_SetPolarVector_00408750
    L_004074e7:
        jmp short L_004074f0
    L_004074e9:
        xor dword ptr [esi+43Ch],1
    L_004074f0:
        mov edx,dword ptr [esi+618h]
    L_004074f6:
        mov ecx,dword ptr [esi+620h]
    L_004074fc:
        mov dword ptr [esi+614h],edx
    L_00407502:
        fld dword ptr [ecx]
    L_00407504:
        fcomp dword ptr [data_00470b68]
    L_0040750a:
        fnstsw ax
    L_0040750c:
        test ah,41h
    L_0040750f:
        jne short L_0040753a
    L_00407511:
        fld dword ptr [ecx]
    L_00407513:
        fcomp dword ptr [data_00470b64]
    L_00407519:
        fnstsw ax
    L_0040751b:
        test ah,5
    L_0040751e:
        jp short L_0040753a
    L_00407520:
        fld dword ptr [esi+61Ch]
    L_00407526:
        inc edx
    L_00407527:
        fadd dword ptr [data_00470afc]
    L_0040752d:
        mov dword ptr [esi+618h],edx
    L_00407533:
        fstp dword ptr [esi+61Ch]
    L_00407539:
        ret
    L_0040753a:
        fld dword ptr [ecx]
    L_0040753c:
        fadd dword ptr [esi+61Ch]
    L_00407542:
        fst dword ptr [esi+61Ch]
    L_00407548:
        call asm_FUN_00463b2c_00463b2c
    L_0040754d:
        mov dword ptr [esi+618h],eax
    L_00407553:
        ret
    }
}
