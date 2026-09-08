#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417700..0x00417707: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417700() {
    __asm {
    L_00417700:
        or dword ptr [eax+35Ch],2
    L_00417707:
        ret
    }
}
