#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AC10..0x0040AC16: FUN_0040ac10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ac10_0040ac10() {
    __asm {
    L_0040ac10:
        mov dword ptr [eax+8974h],ecx
    L_0040ac16:
        ret
    }
}
