#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041AC80..0x0041AC8F: FUN_0041ac80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ac80_0041ac80() {
    __asm {
    L_0041ac80:
        mov ecx,dword ptr [esp+4]
    L_0041ac84:
        mov edx,dword ptr [esp+8]
    L_0041ac88:
        mov dword ptr [eax],ecx
    L_0041ac8a:
        mov dword ptr [eax+4],edx
    L_0041ac8d:
        ret 8
    }
}
