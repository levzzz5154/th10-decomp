#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434B70..0x00434B7A: FUN_00434b70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00434b70_00434b70() {
    __asm {
    L_00434b70:
        mov dword ptr [eax+0D4h],0
    L_00434b7a:
        ret
    }
}
