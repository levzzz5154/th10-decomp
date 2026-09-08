#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C670..0x0040C67A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c670() {
    __asm {
    L_0040c670:
        mov edx,dword ptr [edx+4]
    L_0040c673:
        push eax
    L_0040c674:
        push ecx
    L_0040c675:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0040c67a:
        ret
    }
}
