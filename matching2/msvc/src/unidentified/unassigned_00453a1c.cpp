#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453A1C..0x00453A9A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00453a1c() {
    __asm {
    L_00453a1c:
        cmp dword ptr [data_00499344],3
    L_00453a23:
        jne short L_00453a8e
    L_00453a25:
        push ebx
    L_00453a26:
        xor ebx,ebx
    L_00453a28:
        cmp dword ptr [data_00499328],ebx
    L_00453a2e:
        push ebp
    L_00453a2f:
        mov ebp,dword ptr [data_004661e8]
    L_00453a35:
        jle short L_00453a7c
    L_00453a37:
        push esi
    L_00453a38:
        mov esi,dword ptr [data_0049932c]
    L_00453a3e:
        push edi
    L_00453a3f:
        mov edi,dword ptr [data_00466188]
    L_00453a45:
        add esi,0Ch
    L_00453a48:
        push 4000h
    L_00453a4d:
        push 100000h
    L_00453a52:
        push dword ptr [esi]
    L_00453a54:
        call edi
    L_00453a56:
        push 8000h
    L_00453a5b:
        push 0
    L_00453a5d:
        push dword ptr [esi]
    L_00453a5f:
        call edi
    L_00453a61:
        push dword ptr [esi+4]
    L_00453a64:
        push 0
    L_00453a66:
        push dword ptr [data_00499340]
    L_00453a6c:
        call ebp
    L_00453a6e:
        add esi,14h
    L_00453a71:
        inc ebx
    L_00453a72:
        cmp ebx,dword ptr [data_00499328]
    L_00453a78:
        jl short L_00453a48
    L_00453a7a:
        pop edi
    L_00453a7b:
        pop esi
    L_00453a7c:
        push dword ptr [data_0049932c]
    L_00453a82:
        push 0
    L_00453a84:
        push dword ptr [data_00499340]
    L_00453a8a:
        call ebp
    L_00453a8c:
        pop ebp
    L_00453a8d:
        pop ebx
    L_00453a8e:
        push dword ptr [data_00499340]
    L_00453a94:
        call dword ptr [data_00466190]
    L_00453a9a:
        ret
    }
}
