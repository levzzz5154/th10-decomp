#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421D00..0x00421D14: FUN_00421d00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421d00_00421d00() {
    __asm {
    L_00421d00:
        mov dword ptr [eax+38Ch],0FFFFFFFEh
    L_00421d0a:
        mov dword ptr [eax+390h],0
    L_00421d14:
        ret
    }
}
