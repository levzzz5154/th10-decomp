#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00448980..0x004489C2: ?AnimationManager_RenderBucket@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_RenderBucket_00448980() {
    __asm {
    L_00448980:
        imul eax,3ACh
    L_00448986:
        push esi
    L_00448987:
        mov esi,dword ptr [eax+edi+72DB00h]
    L_0044898e:
        test esi,esi
    L_00448990:
        je short L_004489bc
    L_00448992:
        test dword ptr [esi+35Ch],4000000h
    L_0044899c:
        jne short L_004489b5
    L_0044899e:
        mov eax,dword ptr [esi+39Ch]
    L_004489a4:
        test eax,eax
    L_004489a6:
        je short L_004489ac
    L_004489a8:
        mov ecx,esi
    L_004489aa:
        call eax
    L_004489ac:
        mov eax,esi
    L_004489ae:
        mov ecx,edi
    L_004489b0:
        call asm_FUN_004451c0_004451c0
    L_004489b5:
        mov esi,dword ptr [esi+1Ch]
    L_004489b8:
        test esi,esi
    L_004489ba:
        jne short L_00448992
    L_004489bc:
        mov eax,1
    L_004489c1:
        pop esi
    L_004489c2:
        ret
    }
}
