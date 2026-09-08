#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FF30..0x0041FF36: FUN_0041ff30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ff30_0041ff30() {
    __asm {
    L_0041ff30:
        mov dword ptr [eax+390h],ecx
    L_0041ff36:
        ret
    }
}
