#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436CA0..0x00436CE7: FUN_00436ca0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436ca0_00436ca0() {
    __asm {
    L_00436ca0:
        mov eax,ecx
    L_00436ca2:
        shr eax,14h
    L_00436ca5:
        mov edx,ecx
    L_00436ca7:
        and eax,0Fh
    L_00436caa:
        shr edx,0Ch
    L_00436cad:
        shl eax,4
    L_00436cb0:
        and edx,0Fh
    L_00436cb3:
        or eax,edx
    L_00436cb5:
        mov edx,dword ptr [esi+120h]
    L_00436cbb:
        shr ecx,4
    L_00436cbe:
        and ecx,0Fh
    L_00436cc1:
        shl eax,4
    L_00436cc4:
        push edi
    L_00436cc5:
        mov edi,dword ptr [esi+10Ch]
    L_00436ccb:
        or eax,ecx
    L_00436ccd:
        xor ecx,ecx
    L_00436ccf:
        test edi,edi
    L_00436cd1:
        jle short L_00436ce6
    L_00436cd3:
        mov word ptr [edx],ax
    L_00436cd6:
        mov edi,dword ptr [esi+10Ch]
    L_00436cdc:
        add ecx,2
    L_00436cdf:
        add edx,2
    L_00436ce2:
        cmp ecx,edi
    L_00436ce4:
        jl short L_00436cd3
    L_00436ce6:
        pop edi
    L_00436ce7:
        ret
    }
}
