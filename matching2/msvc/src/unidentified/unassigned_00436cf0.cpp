#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436CF0..0x00436D26: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00436cf0() {
    __asm {
    L_00436cf0:
        mov ecx,dword ptr [data_00474918]
    L_00436cf6:
        xor eax,eax
    L_00436cf8:
        cmp ecx,0FFFFFFFFh
    L_00436cfb:
        je short L_00436d14
    L_00436cfd:
        TH10_NOP_LEA_ECX_DISP8()
    L_00436d00:
        cmp ecx,edx
    L_00436d02:
        je short L_00436d14
    L_00436d04:
        inc eax
    L_00436d05:
        lea ecx,[eax+eax*2]
    L_00436d08:
        mov ecx,dword ptr [ecx*8+474918h]
    L_00436d0f:
        cmp ecx,0FFFFFFFFh
    L_00436d12:
        jne short L_00436d00
    L_00436d14:
        cmp edx,0FFFFFFFFh
    L_00436d17:
        jne short L_00436d1c
    L_00436d19:
        xor eax,eax
    L_00436d1b:
        ret
    L_00436d1c:
        lea eax,[eax+eax*2]
    L_00436d1f:
        lea eax,[eax*8+474918h]
    L_00436d26:
        ret
    }
}
