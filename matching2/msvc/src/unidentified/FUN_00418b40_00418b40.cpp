#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418B40..0x00418B43: FUN_00418b40
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00418b40_00418b40() {
    __asm {
    L_00418b40:
        mov dword ptr [eax+58h],ecx
    L_00418b43:
        ret
    }
}
