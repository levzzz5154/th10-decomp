#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461D3F..0x00461D56: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00461d3f() {
    __asm {
    L_00461d3f:
        xor eax,eax
    L_00461d41:
        inc eax
    L_00461d42:
        ret
    L_00461d43:
        mov esp,dword ptr [ebp-18h]
    L_00461d46:
        call asm_resetstkoflw_00458d91
    L_00461d4b:
        xor edi,edi
    L_00461d4d:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00461d51:
        mov ebx,dword ptr [ebp-4Ch]
    L_00461d54:
        mov esi,dword ptr [ebp-54h]
    }
}
