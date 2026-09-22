// BLOCKED (D3504): closest_byte_count=0/167; first_diff=0x0042B9C0;
// residual_class=private EAX score/ESI queue/EDI position inputs with one
// caller-cleaned stack color argument, plus retail split-body digit loop,
// timer record layout, and caller-dependent register allocation.
// variants_tested=exact retail wrapper, live-Ghidra decompilation plus
// caller/callee graph, and a readable ScorePopupQueue/ScorePopupRecord
// candidate measured at 172 bytes (retail extent is 167); no cluster candidate
// was retained because the fixed-address region remains assembly-owned.
// next_lever=native-LTCG cluster over real caller 0x0041AFD0, this body, and
// the timer/record helpers, with EAX/ESI/EDI plus the RET-4 color argument
// visible to the compiler; then measure all 167 bytes.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042B9C0..0x0042B9EC: FUN_0042b9c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042b9c0_0042b9c0() {
    __asm {
    L_0042b9c0:
        mov ecx,dword ptr [esi+14h]
    L_0042b9c3:
        xor edx,edx
    L_0042b9c5:
        cmp ecx,2D0h
    L_0042b9cb:
        jl short L_0042b9d0
    L_0042b9cd:
        mov dword ptr [esi+14h],edx
    L_0042b9d0:
        mov ecx,dword ptr [esi+14h]
    L_0042b9d3:
        shl ecx,6
    L_0042b9d6:
        push ebx
    L_0042b9d7:
        lea ecx,[ecx+esi+3C4h]
    L_0042b9de:
        xor ebx,ebx
    L_0042b9e0:
        cmp eax,edx
    L_0042b9e2:
        mov byte ptr [ecx+38h],1
    L_0042b9e6:
        TH10_REL8(0x7c, 0x0042b9e6, VA_asm_target_0042ba62)
    L_0042b9e8:
        TH10_REL8(0x74, 0x0042b9e8, VA_asm_target_0042ba08)
    L_0042b9ea:
        push ebp
    L_0042b9eb:
        TH10_REL8(0xeb, 0x0042b9eb, VA_asm_FUN_0042b9c0_part_0042b9f0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042b9f0:
        cdq
    L_0042b9f1:
        mov ebp,0Ah
    L_0042b9f6:
        idiv ebp
    L_0042b9f8:
        inc ebx
    L_0042b9f9:
        test eax,eax
    L_0042b9fb:
        mov byte ptr [ebx+ecx-1],dl
    L_0042b9ff:
        jne short L_0042b9f0
    L_0042ba01:
        xor edx,edx
    L_0042ba03:
        test ebx,ebx
    L_0042ba05:
        pop ebp
    L_0042ba06:
        jne short L_0042ba10
    L_0042ba08:
        mov byte ptr [ecx],0
    L_0042ba0b:
        mov ebx,1
    L_0042ba10:
        mov eax,dword ptr [esp+8]
    L_0042ba14:
        mov byte ptr [ecx+39h],bl
    L_0042ba17:
        mov dword ptr [ecx+18h],eax
    L_0042ba1a:
        mov eax,dword ptr [ecx+2Ch]
    L_0042ba1d:
        test al,1
    L_0042ba1f:
        pop ebx
    L_0042ba20:
        jne short L_0042ba3c
    L_0042ba22:
        or eax,1
    L_0042ba25:
        mov dword ptr [ecx+20h],edx
    L_0042ba28:
        mov dword ptr [ecx+1Ch],0FFF0BDC1h
    L_0042ba2f:
        mov dword ptr [ecx+24h],edx
    L_0042ba32:
        mov dword ptr [ecx+28h],476F78h
    L_0042ba39:
        mov dword ptr [ecx+2Ch],eax
    L_0042ba3c:
        mov dword ptr [ecx+20h],edx
    L_0042ba3f:
        mov dword ptr [ecx+24h],edx
    L_0042ba42:
        mov dword ptr [ecx+1Ch],0FFFFFFFFh
    L_0042ba49:
        mov edx,dword ptr [edi]
    L_0042ba4b:
        add ecx,0Ch
    L_0042ba4e:
        mov dword ptr [ecx],edx
    L_0042ba50:
        mov eax,dword ptr [edi+4]
    L_0042ba53:
        mov dword ptr [ecx+4],eax
    L_0042ba56:
        mov edx,dword ptr [edi+8]
    L_0042ba59:
        mov dword ptr [ecx+8],edx
    L_0042ba5c:
        inc dword ptr [esi+14h]
    L_0042ba5f:
        ret 4
    L_0042ba62:
        mov byte ptr [ecx],0Ah
    L_0042ba65:
        jmp short L_0042ba0b
    }
}
