// BLOCKED (D3904): closest_byte_count=0/124; first_diff=extent (readable
// candidate emitted 110 bytes versus the 124-byte retail body).
// residual_class=ESI player receiver, EBX position pointer, stage-flag
// branch shape, and private FUN_00408100/FUN_0041C800 call ABIs; real caller
// is UpdatePlayer 0x00405750. variants_tested=live Ghidra decompile/caller
// inspection and MSVC 13.10 typed player candidate (110-byte body), with
// exact naked baseline restored. next_lever=schema-2 native-LTCG cluster
// retaining UpdatePlayer and both callee edges.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404530..0x004045A6: FUN_00404530
// Naked body preserves the retail register/stack ABI.

// 0x00405AC0..0x00405B3B: Player_Draw
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_Draw_00405ac0() {
    __asm {
    L_00405ac0:
        mov eax,dword ptr [esi+28h]
    L_00405ac3:
        test eax,eax
    L_00405ac5:
        je short L_00405b39
    L_00405ac7:
        mov ecx,dword ptr [data_004776f4]
    L_00405acd:
        mov eax,dword ptr [ecx+378Ch]
    L_00405ad3:
        test al,1
    L_00405ad5:
        push ebx
    L_00405ad6:
        je short L_00405ae8
    L_00405ad8:
        mov edx,dword ptr [ecx+3788h]
    L_00405ade:
        cmp edx,5Dh
    L_00405ae1:
        jl short L_00405ae8
    L_00405ae3:
        cmp edx,60h
    L_00405ae6:
        jle short L_00405af1
    L_00405ae8:
        cmp dword ptr [ecx+3788h],6Dh
    L_00405aef:
        jne short L_00405aff
    L_00405af1:
        not eax
    L_00405af3:
        push 0
    L_00405af5:
        and eax,1
    L_00405af8:
        push eax
    L_00405af9:
        mov eax,dword ptr [esi+3Ch]
    L_00405afc:
        push eax
    L_00405afd:
        jmp short L_00405b0b
    L_00405aff:
        mov ecx,dword ptr [esi+3Ch]
    L_00405b02:
        not eax
    L_00405b04:
        push 1
    L_00405b06:
        and eax,1
    L_00405b09:
        push eax
    L_00405b0a:
        push ecx
    L_00405b0b:
        mov eax,dword ptr [data_004776f0]
    L_00405b10:
        lea ebx,[esi+30h]
    L_00405b13:
        call asm_FUN_00408100_00408100
    L_00405b18:
        mov edx,dword ptr [data_004776f4]
    L_00405b1e:
        mov eax,dword ptr [edx+378Ch]
    L_00405b24:
        mov ecx,dword ptr [esi+3Ch]
    L_00405b27:
        not eax
    L_00405b29:
        and eax,1
    L_00405b2c:
        push eax
    L_00405b2d:
        mov eax,dword ptr [data_0047781c]
    L_00405b32:
        push ecx
    L_00405b33:
        call asm_ScoreRecords_CopyVectorAndEvaluate_0041c800
    L_00405b38:
        pop ebx
    L_00405b39:
        xor eax,eax
    L_00405b3b:
        ret
    }
}
