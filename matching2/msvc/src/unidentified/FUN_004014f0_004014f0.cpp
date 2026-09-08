#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004014F0..0x00401509: FUN_004014f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004014f0_004014f0() {
    __asm {
    L_004014f0:
        xor eax,eax
    L_004014f2:
        mov dword ptr [ecx+896Ch],eax
    L_004014f8:
        mov dword ptr [ecx+8970h],eax
    L_004014fe:
        inc dword ptr [ecx+8990h]
    L_00401504:
        mov eax,1
    L_00401509:
        ret
    }
}
