#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041AC20..0x0041AC2A: FUN_0041ac20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ac20_0041ac20() {
    __asm {
    L_0041ac20:
        mov edx,dword ptr [eax]
    L_0041ac22:
        mov dword ptr [ecx],edx
    L_0041ac24:
        mov eax,dword ptr [eax+4]
    L_0041ac27:
        mov dword ptr [ecx+4],eax
    L_0041ac2a:
        ret
    }
}
