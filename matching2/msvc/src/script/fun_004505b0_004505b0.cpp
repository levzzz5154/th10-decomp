// BLOCKED (D2701): closest_byte_count=96; first_diff=unmeasured;
// residual_class=abi+copy-scheduling: retail receives the scratch VM in EAX,
// the type byte in DL, and size/source on the stack, then conditionally
// advances the typed frame and emits one rep-movsd/rep-movsb copy sequence.
// This mixed register/stack entry convention and its cursor lifetime are not
// expressible by the ordinary __cdecl wrapper.
// variants_tested=exact retail wrapper, the legacy ECL_WriteScratch semantic
// model, memcpy/intrinsic and explicit byte-copy source forms, and the
// neighboring push/pop scratch cluster models; no compiler-readable candidate
// was byte-measured.
// next_lever=build the scratch read/write helpers together in a native-LTCG
// cluster with a synthetic caller pinning EAX/DL and the two stack arguments,
// then measure the 96-byte body; retain this wrapper until that ABI and copy
// schedule are reproduced.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF70..0x0044E195: EclVm_StartChildRetail
// Naked body preserves the retail register/stack ABI.

// 0x004505B0..0x0045060F: FUN_004505b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004505b0_004505b0() {
    __asm {
    L_004505b0:
        mov ecx,dword ptr [eax+1000h]
    L_004505b6:
        push ebp
    L_004505b7:
        mov ebp,dword ptr [esp+8]
    L_004505bb:
        push esi
    L_004505bc:
        lea esi,[ecx+ebp]
    L_004505bf:
        cmp esi,1000h
    L_004505c5:
        jl short L_004505cf
    L_004505c7:
        pop esi
    L_004505c8:
        or eax,0FFFFFFFFh
    L_004505cb:
        pop ebp
    L_004505cc:
        ret 8
    L_004505cf:
        test dl,dl
    L_004505d1:
        je short L_004505dd
    L_004505d3:
        mov byte ptr [ecx+eax],dl
    L_004505d6:
        add dword ptr [eax+1000h],4
    L_004505dd:
        mov esi,dword ptr [esp+10h]
    L_004505e1:
        push edi
    L_004505e2:
        mov edi,dword ptr [eax+1000h]
    L_004505e8:
        mov ecx,ebp
    L_004505ea:
        mov edx,ecx
    L_004505ec:
        shr ecx,2
    L_004505ef:
        add edi,eax
    L_004505f1:
        rep movsd
    L_004505f3:
        mov ecx,edx
    L_004505f5:
        and ecx,3
    L_004505f8:
        rep movsb
    L_004505fa:
        mov ecx,dword ptr [eax+1000h]
    L_00450600:
        pop edi
    L_00450601:
        add ecx,ebp
    L_00450603:
        pop esi
    L_00450604:
        mov dword ptr [eax+1000h],ecx
    L_0045060a:
        xor eax,eax
    L_0045060c:
        pop ebp
    L_0045060d:
        ret 8
    }
}
