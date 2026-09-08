#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412D70..0x00412D7B: FUN_00412d70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412d70_00412d70() {
    __asm {
    L_00412d70:
        mov edx,dword ptr [eax]
    L_00412d72:
        mov dword ptr [ecx+8],edx
    L_00412d75:
        mov eax,dword ptr [eax+4]
    L_00412d78:
        mov dword ptr [ecx+0Ch],eax
    L_00412d7b:
        ret
    }
}
