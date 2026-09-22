// BLOCKED (D2702): closest_byte_count=181; first_diff=unmeasured;
// residual_class=source-shape+ABI: retail keeps the manager in EDX (with an
// unused promoted ECX live-in), scans 32 packed 0x6C-byte slots, performs a
// redundant second clear after the 0x6C-byte wipe, and stores two stack
// arguments through an embedded x87 timer initialization sequence.  The
// ordinary pool/slot model captures the fields but has not produced a
// measured compiler candidate for this exact register and clear schedule.
// variants_tested=exact retail wrapper, the legacy EffectIndicatorPool slot
// model, the EmbeddedTimer_SetCountdown sibling pattern, both real allocation
// callers, and live-Ghidra boundary/caller/global audits;
// next_lever=compile the manager/slot allocator with a native-LTCG context
// that pins the manager in EDX and preserves the redundant clear and x87 timer
// stores, then measure the 181-byte extent; retain this exact wrapper until
// that ABI/source-shape cluster succeeds.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427B50..0x00427C04: EffectIndicatorPool_AllocateRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EffectIndicatorPool_AllocateRetail_00427b50() {
    __asm {
    L_00427b50:
        push ebp
    L_00427b51:
        mov ebp,dword ptr [esp+8]
    L_00427b55:
        add edx,350Ch
    L_00427b5b:
        xor eax,eax
    L_00427b5d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00427b60:
        test byte ptr [edx+68h],1
    L_00427b64:
        je short L_00427b75
    L_00427b66:
        inc eax
    L_00427b67:
        add edx,6Ch
    L_00427b6a:
        cmp eax,20h
    L_00427b6d:
        jl short L_00427b60
    L_00427b6f:
        mov eax,edx
    L_00427b71:
        pop ebp
    L_00427b72:
        ret 14h
    L_00427b75:
        push esi
    L_00427b76:
        push edi
    L_00427b77:
        xor eax,eax
    L_00427b79:
        mov ecx,1Bh
    L_00427b7e:
        mov edi,edx
    L_00427b80:
        rep stosd
    L_00427b82:
        or dword ptr [edx+68h],3
    L_00427b86:
        lea esi,[edx+18h]
    L_00427b89:
        mov edi,esi
    L_00427b8b:
        mov ecx,0Bh
    L_00427b90:
        rep stosd
    L_00427b92:
        mov eax,dword ptr [ebp]
    L_00427b95:
        mov dword ptr [esi],eax
    L_00427b97:
        mov ecx,dword ptr [ebp+4]
    L_00427b9a:
        mov dword ptr [esi+4],ecx
    L_00427b9d:
        mov eax,dword ptr [ebp+8]
    L_00427ba0:
        mov ecx,dword ptr [esp+14h]
    L_00427ba4:
        mov dword ptr [esi+8],eax
    L_00427ba7:
        mov eax,dword ptr [esp+18h]
    L_00427bab:
        mov dword ptr [edx],ecx
    L_00427bad:
        mov dword ptr [edx+4],eax
    L_00427bb0:
        mov eax,dword ptr [edx+54h]
    L_00427bb3:
        pop edi
    L_00427bb4:
        xor ecx,ecx
    L_00427bb6:
        test al,1
    L_00427bb8:
        pop esi
    L_00427bb9:
        jne short L_00427bd5
    L_00427bbb:
        or eax,1
    L_00427bbe:
        mov dword ptr [edx+48h],ecx
    L_00427bc1:
        mov dword ptr [edx+44h],0FFF0BDC1h
    L_00427bc8:
        mov dword ptr [edx+4Ch],ecx
    L_00427bcb:
        mov dword ptr [edx+50h],476F78h
    L_00427bd2:
        mov dword ptr [edx+54h],eax
    L_00427bd5:
        mov eax,dword ptr [esp+14h]
    L_00427bd9:
        fild dword ptr [esp+14h]
    L_00427bdd:
        mov dword ptr [edx+48h],eax
    L_00427be0:
        dec eax
    L_00427be1:
        mov dword ptr [edx+44h],eax
    L_00427be4:
        fstp dword ptr [edx+4Ch]
    L_00427be7:
        mov eax,dword ptr [esp+18h]
    L_00427beb:
        mov dword ptr [edx+58h],eax
    L_00427bee:
        mov dword ptr [edx+5Ch],ecx
    L_00427bf1:
        mov dword ptr [edx+60h],0F423Fh
    L_00427bf8:
        mov dword ptr [edx+64h],4
    L_00427bff:
        mov eax,edx
    L_00427c01:
        pop ebp
    L_00427c02:
        ret 14h
    }
}
