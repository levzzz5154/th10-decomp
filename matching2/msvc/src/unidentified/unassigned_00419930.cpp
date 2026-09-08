#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00419930..0x00419952: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00419930() {
    __asm {
    L_00419930:
        xor eax,eax
    L_00419932:
        test edx,edx
    L_00419934:
        jle short L_0041994c
    L_00419936:
        lea ecx,[edi+4]
    L_00419939:
        lea esp,[esp+force_disp32_zero]
    L_00419940:
        cmp dword ptr [ecx],esi
    L_00419942:
        je short L_0041994f
    L_00419944:
        inc eax
    L_00419945:
        add ecx,8
    L_00419948:
        cmp eax,edx
    L_0041994a:
        jl short L_00419940
    L_0041994c:
        xor eax,eax
    L_0041994e:
        ret
    L_0041994f:
        mov eax,dword ptr [edi+eax*8]
    L_00419952:
        ret
    }
}
