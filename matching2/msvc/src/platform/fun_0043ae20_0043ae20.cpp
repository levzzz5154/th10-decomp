// BLOCKED (D3605): closest_byte_count=2/129; first_diff=0x0043AE20.
// residual_class=private EDI receiver, EDX/ESI handoff to FUN_0043AEB0,
// import thunk calling convention, and caller-dependent saved-register shape.
// variants_tested=live Ghidra decompilation, callers 0x0043A910/0x0043A9B0/
// 0x00438F19, and MSVC 13.10 typed MIDI-state cdecl candidates (140-byte
// stack-layout variant and 121-byte corrected-layout variant; 2/121
// same-position bytes); exact naked baseline probe=129/129. next_lever=
// native-LTCG cluster with FUN_0043AEB0 and the GameMain caller, preserving
// EDI state and import-slot bindings.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438AD0..0x0043900C: GameMain
// Naked body preserves the retail register/stack ABI.

// 0x0043AE20..0x0043AEA0: FUN_0043ae20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043ae20_0043ae20() {
    __asm {
    L_0043ae20:
        mov eax,dword ptr [edi+138h]
    L_0043ae26:
        test eax,eax
    L_0043ae28:
        jne short L_0043ae2e
    L_0043ae2a:
        or eax,0FFFFFFFFh
    L_0043ae2d:
        ret
    L_0043ae2e:
        push ebx
    L_0043ae2f:
        push ebp
    L_0043ae30:
        push esi
    L_0043ae31:
        lea ebx,[edi+14h]
    L_0043ae34:
        mov ebp,20h
    L_0043ae39:
        lea esp,[esp+force_disp32_zero]
    L_0043ae40:
        mov esi,dword ptr [ebx]
    L_0043ae42:
        test esi,esi
    L_0043ae44:
        je short L_0043ae4d
    L_0043ae46:
        mov edx,edi
    L_0043ae48:
        call asm_FUN_0043aeb0_0043aeb0
    L_0043ae4d:
        add ebx,4
    L_0043ae50:
        dec ebp
    L_0043ae51:
        jne short L_0043ae40
    L_0043ae53:
        mov eax,dword ptr [edi+4]
    L_0043ae56:
        test eax,eax
    L_0043ae58:
        je short L_0043ae61
    L_0043ae5a:
        push eax
    L_0043ae5b:
        call dword ptr [data_00466288]
    L_0043ae61:
        mov eax,dword ptr [edi+8]
    L_0043ae64:
        push eax
    L_0043ae65:
        call dword ptr [data_00466274]
    L_0043ae6b:
        xor esi,esi
    L_0043ae6d:
        mov dword ptr [edi+4],esi
    L_0043ae70:
        mov eax,dword ptr [edi+13Ch]
    L_0043ae76:
        cmp eax,esi
    L_0043ae78:
        je short L_0043ae94
    L_0043ae7a:
        push eax
    L_0043ae7b:
        call dword ptr [data_004662a8]
    L_0043ae81:
        mov ecx,dword ptr [edi+13Ch]
    L_0043ae87:
        push ecx
    L_0043ae88:
        call dword ptr [data_004662a4]
    L_0043ae8e:
        mov dword ptr [edi+13Ch],esi
    L_0043ae94:
        pop esi
    L_0043ae95:
        pop ebp
    L_0043ae96:
        mov dword ptr [edi+10h],0FFFFFFFFh
    L_0043ae9d:
        xor eax,eax
    L_0043ae9f:
        pop ebx
    L_0043aea0:
        ret
    }
}
