// BLOCKED (D3702): closest_byte_count=0/335; first_diff=extent (candidate
// extent 284 vs retail 335).
// residual_class=abi+structural: readable cdecl candidate emitted a 284-byte
// body while retail requires ESI live-in state, x87 easing arithmetic, and
// private animation/polar-vector helper conventions.
// variants_tested=live Ghidra decompile, archived EaseStepCommon model, and
// MSVC 13.10 readable candidate probe (284-byte extent vs 335-byte retail).
// next_lever=native-LTCG cluster with the actual bullet runtime caller and
// production enemy-state layout.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00407560..0x00407690: FUN_00407560
// Naked body preserves the retail register/stack ABI.

// 0x004078E0..0x00407A2E: FUN_004078e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004078e0_004078e0() {
    __asm {
    L_004078e0:
        push ecx
    L_004078e1:
        mov eax,dword ptr [esi+6D8h]
    L_004078e7:
        cmp dword ptr [esi+6B4h],eax
    L_004078ed:
        mov dword ptr [esp],eax
    L_004078f0:
        jl asm_target_0040799b
    L_004078f6:
        push ebx
    L_004078f7:
        push edi
    L_004078f8:
        mov edi,dword ptr [esi+458h]
    L_004078fe:
        xor ebx,ebx
    L_00407900:
        cmp edi,ebx
    L_00407902:
        jl short L_0040790f
    L_00407904:
        push ebx
    L_00407905:
        mov ecx,492590h
    L_0040790a:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0040790f:
        mov edx,dword ptr [esi+6E0h]
    L_00407915:
        mov ecx,dword ptr [esi+6DCh]
    L_0040791b:
        inc edx
    L_0040791c:
        mov eax,edx
    L_0040791e:
        cmp eax,ecx
    L_00407920:
        mov dword ptr [esi+6E0h],edx
    L_00407926:
        jl short L_00407932
    L_00407928:
        and dword ptr [esi+43Ch],0FFFFFEFFh
    L_00407932:
        mov eax,dword ptr [esi+6C8h]
    L_00407938:
        fld dword ptr [esi+6C4h]
    L_0040793e:
        fst dword ptr [esi+3D8h]
    L_00407944:
        mov dword ptr [esi+3E4h],eax
    L_0040794a:
        mov eax,dword ptr [esi+6C0h]
    L_00407950:
        fstp dword ptr [esp+8]
    L_00407954:
        test al,1
    L_00407956:
        jne short L_00407981
    L_00407958:
        or eax,1
    L_0040795b:
        mov dword ptr [esi+6B4h],ebx
    L_00407961:
        mov dword ptr [esi+6B0h],0FFF0BDC1h
    L_0040796b:
        mov dword ptr [esi+6B8h],ebx
    L_00407971:
        mov dword ptr [esi+6BCh],476F78h
    L_0040797b:
        mov dword ptr [esi+6C0h],eax
    L_00407981:
        pop edi
    L_00407982:
        mov dword ptr [esi+6B4h],ebx
    L_00407988:
        mov dword ptr [esi+6B8h],ebx
    L_0040798e:
        mov dword ptr [esi+6B0h],0FFFFFFFFh
    L_00407998:
        pop ebx
    L_00407999:
        jmp short L_004079b3
    L_0040799b:
        fld dword ptr [esi+3D8h]
    L_004079a1:
        fld st(0)
    L_004079a3:
        fmul dword ptr [esi+6B8h]
    L_004079a9:
        fidiv dword ptr [esp]
    L_004079ac:
        fsubr st,st(1)
    L_004079ae:
        fstp dword ptr [esp]
    L_004079b1:
        fstp st(0)
    L_004079b3:
        mov ecx,dword ptr [esp]
    L_004079b6:
        mov edx,dword ptr [esi+3E4h]
    L_004079bc:
        push ecx
    L_004079bd:
        push edx
    L_004079be:
        lea ecx,[esi+3C0h]
    L_004079c4:
        call asm_Score_SetPolarVector_00408750
    L_004079c9:
        mov edx,dword ptr [esi+6B4h]
    L_004079cf:
        mov ecx,dword ptr [esi+6BCh]
    L_004079d5:
        mov dword ptr [esi+6B0h],edx
    L_004079db:
        fld dword ptr [ecx]
    L_004079dd:
        fcomp dword ptr [data_00470b68]
    L_004079e3:
        fnstsw ax
    L_004079e5:
        test ah,41h
    L_004079e8:
        jne short L_00407a14
    L_004079ea:
        fld dword ptr [ecx]
    L_004079ec:
        fcomp dword ptr [data_00470b64]
    L_004079f2:
        fnstsw ax
    L_004079f4:
        test ah,5
    L_004079f7:
        jp short L_00407a14
    L_004079f9:
        fld dword ptr [esi+6B8h]
    L_004079ff:
        inc edx
    L_00407a00:
        fadd dword ptr [data_00470afc]
    L_00407a06:
        mov dword ptr [esi+6B4h],edx
    L_00407a0c:
        fstp dword ptr [esi+6B8h]
    L_00407a12:
        pop ecx
    L_00407a13:
        ret
    L_00407a14:
        fld dword ptr [ecx]
    L_00407a16:
        fadd dword ptr [esi+6B8h]
    L_00407a1c:
        fst dword ptr [esi+6B8h]
    L_00407a22:
        call asm_FUN_00463b2c_00463b2c
    L_00407a27:
        mov dword ptr [esi+6B4h],eax
    L_00407a2d:
        pop ecx
    L_00407a2e:
        ret
    }
}
