#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041AC10..0x0041AC13: FUN_0041ac10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ac10_0041ac10() {
    __asm {
    L_0041ac10:
        mov dword ptr [ecx+38h],eax
    L_0041ac13:
        ret
    }
}
