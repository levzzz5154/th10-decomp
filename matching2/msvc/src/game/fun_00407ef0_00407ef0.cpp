// BLOCKED (D3702): closest_byte_count=0/306; first_diff=extent (candidate
// extent 176 vs retail 306).
// residual_class=abi+structural: readable cdecl candidate emitted a 176-byte
// body while retail requires ESI live-in state, x87 FPATAN/stack ordering,
// and private helper register conventions.
// variants_tested=live Ghidra decompile, archived Enemy_HomingStep model, and
// MSVC 13.10 readable candidate probe (176-byte extent vs 306-byte retail).
// next_lever=native-LTCG cluster with the actual bullet runtime caller and
// typed enemy state plus x87-compatible helper declarations.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00407560..0x00407690: FUN_00407560
// Naked body preserves the retail register/stack ABI.

// 0x00407EF0..0x00408021: FUN_00407ef0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00407ef0_00407ef0() {
    __asm {
    L_00407ef0:
        push ecx
    L_00407ef1:
        mov eax,dword ptr [esi+7B8h]
    L_00407ef7:
        cmp eax,dword ptr [esi+7DCh]
    L_00407efd:
        jl short L_00407f0e
    L_00407eff:
        and dword ptr [esi+43Ch],0FBFFFFFFh
    L_00407f09:
        jmp asm_target_00407fbc
    L_00407f0e:
        mov eax,dword ptr [data_00477834]
    L_00407f13:
        fld dword ptr [eax+3C0h]
    L_00407f19:
        fsub dword ptr [esi+3B4h]
    L_00407f1f:
        fld dword ptr [eax+3C4h]
    L_00407f25:
        fsub dword ptr [esi+3B8h]
    L_00407f2b:
        fld dword ptr [data_00470b04]
    L_00407f31:
        fld st(1)
    L_00407f33:
        fucompp
    L_00407f35:
        fnstsw ax
    L_00407f37:
        test ah,44h
    L_00407f3a:
        jp short L_00407f5a
    L_00407f3c:
        fld dword ptr [data_00470b04]
    L_00407f42:
        fld st(2)
    L_00407f44:
        fucompp
    L_00407f46:
        fnstsw ax
    L_00407f48:
        test ah,44h
    L_00407f4b:
        jp short L_00407f5a
    L_00407f4d:
        fstp st(0)
    L_00407f4f:
        mov dword ptr [esp],3FC90FDBh
    L_00407f56:
        fstp st(0)
    L_00407f58:
        jmp short L_00407f61
    L_00407f5a:
        fxch
    L_00407f5c:
        fpatan
    L_00407f5e:
        fstp dword ptr [esp]
    L_00407f61:
        mov ecx,dword ptr [esi+3E4h]
    L_00407f67:
        mov edx,dword ptr [esp]
    L_00407f6a:
        mov eax,dword ptr [esi+7CCh]
    L_00407f70:
        push ecx
    L_00407f71:
        push edx
    L_00407f72:
        push eax
    L_00407f73:
        call asm_Angle_NormalizeSum_0044bc10
    L_00407f78:
        push ecx
    L_00407f79:
        fstp dword ptr [esp]
    L_00407f7c:
        call asm_WrappedAngleDifference_00408660
    L_00407f81:
        fmul dword ptr [esi+7C8h]
    L_00407f87:
        push ecx
    L_00407f88:
        mov ecx,dword ptr [esi+3E4h]
    L_00407f8e:
        fmul dword ptr [data_00476f78]
    L_00407f94:
        fstp dword ptr [esp]
    L_00407f97:
        push ecx
    L_00407f98:
        call asm_Angle_NormalizeSum_0044bc10
    L_00407f9d:
        fst dword ptr [esp]
    L_00407fa0:
        mov edx,dword ptr [esi+3D8h]
    L_00407fa6:
        fstp dword ptr [esi+3E4h]
    L_00407fac:
        mov eax,dword ptr [esp]
    L_00407faf:
        push edx
    L_00407fb0:
        push eax
    L_00407fb1:
        lea ecx,[esi+3C0h]
    L_00407fb7:
        call asm_Score_SetPolarVector_00408750
    L_00407fbc:
        mov edx,dword ptr [esi+7B8h]
    L_00407fc2:
        mov ecx,dword ptr [esi+7C0h]
    L_00407fc8:
        mov dword ptr [esi+7B4h],edx
    L_00407fce:
        fld dword ptr [ecx]
    L_00407fd0:
        fcomp dword ptr [data_00470b68]
    L_00407fd6:
        fnstsw ax
    L_00407fd8:
        test ah,41h
    L_00407fdb:
        jne short L_00408007
    L_00407fdd:
        fld dword ptr [ecx]
    L_00407fdf:
        fcomp dword ptr [data_00470b64]
    L_00407fe5:
        fnstsw ax
    L_00407fe7:
        test ah,5
    L_00407fea:
        jp short L_00408007
    L_00407fec:
        fld dword ptr [esi+7BCh]
    L_00407ff2:
        inc edx
    L_00407ff3:
        fadd dword ptr [data_00470afc]
    L_00407ff9:
        mov dword ptr [esi+7B8h],edx
    L_00407fff:
        fstp dword ptr [esi+7BCh]
    L_00408005:
        pop ecx
    L_00408006:
        ret
    L_00408007:
        fld dword ptr [ecx]
    L_00408009:
        fadd dword ptr [esi+7BCh]
    L_0040800f:
        fst dword ptr [esi+7BCh]
    L_00408015:
        call asm_FUN_00463b2c_00463b2c
    L_0040801a:
        mov dword ptr [esi+7B8h],eax
    L_00408020:
        pop ecx
    L_00408021:
        ret
    }
}
