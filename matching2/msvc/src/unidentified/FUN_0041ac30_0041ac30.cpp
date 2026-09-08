#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041AC30..0x0041AC3B: FUN_0041ac30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ac30_0041ac30() {
    __asm {
    L_0041ac30:
        mov edx,dword ptr [eax]
    L_0041ac32:
        mov dword ptr [ecx+8],edx
    L_0041ac35:
        mov eax,dword ptr [eax+4]
    L_0041ac38:
        mov dword ptr [ecx+0Ch],eax
    L_0041ac3b:
        ret
    }
}
