#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401FA0..0x00401FA2: FUN_00401fa0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401fa0_00401fa0() {
    __asm {
    L_00401fa0:
        mov eax,ecx
    L_00401fa2:
        ret
    }
}
