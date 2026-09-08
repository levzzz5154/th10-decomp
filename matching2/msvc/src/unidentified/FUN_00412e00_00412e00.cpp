#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412E00..0x00412E07: FUN_00412e00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412e00_00412e00() {
    __asm {
    L_00412e00:
        mov dword ptr [eax+34h],0
    L_00412e07:
        ret
    }
}
