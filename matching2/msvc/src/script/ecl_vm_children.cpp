#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED (D2801): closest_byte_count=0/146; first_diff=unmeasured;
// residual_class=private_abi: legacy EclVm_TickChildren semantics are known,
// but no readable native-LTCG body was retained without perturbing the EDI
// owner and userpurge stack ABI.
// variants_tested=legacy semantic control-flow transcription and Ghidra ABI
// audit; no candidate survived byte comparison.
// next_lever=co-compile the 0x0040DC80 caller with explicit owner/register
// context, then tune the first-pass temporary and list-unlink declaration
// order against the 0x0044FD20 branch boundary.

// 0x0044FD10..0x0044FDA1: EclVm_TickChildren
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EclVm_TickChildren_0044fd10() {
    __asm {
    L_0044fd10:
        push ebx
    L_0044fd11:
        push ebp
    L_0044fd12:
        push esi
    L_0044fd13:
        lea esi,[edi+1030h]
    L_0044fd19:
        test esi,esi
    L_0044fd1b:
        mov ebp,1
    L_0044fd20:
        je short L_0044fd8b
    L_0044fd22:
        test ebp,ebp
    L_0044fd24:
        mov eax,dword ptr [esi]
    L_0044fd26:
        mov ebx,dword ptr [esi+4]
    L_0044fd29:
        mov dword ptr [edi+4],eax
    L_0044fd2c:
        je short L_0044fd40
    L_0044fd2e:
        mov ecx,dword ptr [esp+10h]
    L_0044fd32:
        push ecx
    L_0044fd33:
        call asm_FUN_0044e1a0_0044e1a0
    L_0044fd38:
        test eax,eax
    L_0044fd3a:
        jne short L_0044fd99
    L_0044fd3c:
        xor ebp,ebp
    L_0044fd3e:
        jmp short L_0044fd85
    L_0044fd40:
        mov edx,dword ptr [esp+10h]
    L_0044fd44:
        push edx
    L_0044fd45:
        call asm_FUN_0044e1a0_0044e1a0
    L_0044fd4a:
        test eax,eax
    L_0044fd4c:
        je short L_0044fd85
    L_0044fd4e:
        mov eax,dword ptr [edi+4]
    L_0044fd51:
        push eax
    L_0044fd52:
        call asm_free_004524a1
    L_0044fd57:
        mov eax,dword ptr [esi+4]
    L_0044fd5a:
        xor ecx,ecx
    L_0044fd5c:
        add esp,4
    L_0044fd5f:
        cmp eax,ecx
    L_0044fd61:
        je short L_0044fd69
    L_0044fd63:
        mov edx,dword ptr [esi+8]
    L_0044fd66:
        mov dword ptr [eax+8],edx
    L_0044fd69:
        mov eax,dword ptr [esi+8]
    L_0044fd6c:
        cmp eax,ecx
    L_0044fd6e:
        je short L_0044fd76
    L_0044fd70:
        mov edx,dword ptr [esi+4]
    L_0044fd73:
        mov dword ptr [eax+4],edx
    L_0044fd76:
        push esi
    L_0044fd77:
        mov dword ptr [esi+4],ecx
    L_0044fd7a:
        mov dword ptr [esi+8],ecx
    L_0044fd7d:
        call asm_free_004524a1
    L_0044fd82:
        add esp,4
    L_0044fd85:
        test ebx,ebx
    L_0044fd87:
        mov esi,ebx
    L_0044fd89:
        jne short L_0044fd22
    L_0044fd8b:
        pop esi
    L_0044fd8c:
        lea eax,[edi+8]
    L_0044fd8f:
        pop ebp
    L_0044fd90:
        mov dword ptr [edi+4],eax
    L_0044fd93:
        xor eax,eax
    L_0044fd95:
        pop ebx
    L_0044fd96:
        ret 4
    L_0044fd99:
        pop esi
    L_0044fd9a:
        pop ebp
    L_0044fd9b:
        or eax,0FFFFFFFFh
    L_0044fd9e:
        pop ebx
    L_0044fd9f:
        ret 4
    }
}
