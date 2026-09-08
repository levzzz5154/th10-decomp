#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413240..0x00413242: FUN_00413240
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413240_00413240() {
    __asm {
    L_00413240:
        mov eax,ecx
    L_00413242:
        ret
    }
}
