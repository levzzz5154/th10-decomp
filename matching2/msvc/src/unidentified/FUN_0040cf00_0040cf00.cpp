#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CF00..0x0040CF09: FUN_0040cf00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040cf00_0040cf00() {
    __asm {
    L_0040cf00:
        mov eax,dword ptr [esp+4]
    L_0040cf04:
        mov dword ptr [ecx+3Ch],eax
    L_0040cf07:
        ret 4
    }
}
