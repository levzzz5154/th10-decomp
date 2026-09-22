#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3903): closest_byte_count=20/149; first_diff=0x00448862;
// residual_class=private EAX manager receiver, list/node traversal, callback
// dispatch ABI, and compiler register/save order across the animation table.
// variants_tested=MSVC 13.10 typed standalone loop candidate (161-byte extent,
// 20/149 same-position bytes) plus exact naked baseline; candidate was restored.
// next_lever=caller-inclusive schema2 native-LTCG cluster with the real manager
// owner and 0x00448BB0/0x0043EE30 callees visible to register allocation.
// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00448860..0x004488F4: ?AnimationManager_UpdatePrimary@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_UpdatePrimary_00448860() {
    __asm {
    L_00448860:
        sub esp,50h
    L_00448863:
        push ebp
    L_00448864:
        push edi
    L_00448865:
        mov edi,eax
    L_00448867:
        xor ebp,ebp
    L_00448869:
        xor eax,eax
    L_0044886b:
        lea ecx,[edi+72DAE4h]
    L_00448871:
        mov dword ptr [esp+eax*4+8],ecx
    L_00448875:
        mov dword ptr [ecx+1Ch],ebp
    L_00448878:
        inc eax
    L_00448879:
        add ecx,3ACh
    L_0044887f:
        cmp eax,13h
    L_00448882:
        jl short L_00448871
    L_00448884:
        mov eax,dword ptr [edi+72DAD4h]
    L_0044888a:
        cmp eax,ebp
    L_0044888c:
        je short L_004488ea
    L_0044888e:
        push ebx
    L_0044888f:
        push esi
    L_00448890:
        mov esi,dword ptr [eax]
    L_00448892:
        mov ebx,dword ptr [eax+4]
    L_00448895:
        test dword ptr [esi+35Ch],4000000h
    L_0044889f:
        je short L_004488a8
    L_004488a1:
        call asm_FUN_00448bb0_00448bb0
    L_004488a6:
        jmp short L_004488db
    L_004488a8:
        mov eax,dword ptr [esi+398h]
    L_004488ae:
        cmp eax,ebp
    L_004488b0:
        je short L_004488b6
    L_004488b2:
        mov ecx,esi
    L_004488b4:
        call eax
    L_004488b6:
        push esi
    L_004488b7:
        call asm_FUN_0043ee30_0043ee30
    L_004488bc:
        test eax,eax
    L_004488be:
        je short L_004488c7
    L_004488c0:
        call asm_FUN_00448bb0_00448bb0
    L_004488c5:
        jmp short L_004488db
    L_004488c7:
        mov eax,dword ptr [esi+20h]
    L_004488ca:
        mov ecx,dword ptr [esp+eax*4+10h]
    L_004488ce:
        mov dword ptr [ecx+1Ch],esi
    L_004488d1:
        mov edx,dword ptr [esi+20h]
    L_004488d4:
        mov dword ptr [esp+edx*4+10h],esi
    L_004488d8:
        mov dword ptr [esi+1Ch],ebp
    L_004488db:
        mov edx,dword ptr [edi+64h]
    L_004488de:
        inc edx
    L_004488df:
        cmp ebx,ebp
    L_004488e1:
        mov dword ptr [edi+64h],edx
    L_004488e4:
        mov eax,ebx
    L_004488e6:
        jne short L_00448890
    L_004488e8:
        pop esi
    L_004488e9:
        pop ebx
    L_004488ea:
        pop edi
    L_004488eb:
        mov eax,1
    L_004488f0:
        pop ebp
    L_004488f1:
        add esp,50h
    L_004488f4:
        ret
    }
}
