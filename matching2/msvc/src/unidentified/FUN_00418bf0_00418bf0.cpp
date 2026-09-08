#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418BF0..0x00418BF3: FUN_00418bf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00418bf0_00418bf0() {
    __asm {
    L_00418bf0:
        mov dword ptr [eax+34h],ecx
    L_00418bf3:
        ret
    }
}
