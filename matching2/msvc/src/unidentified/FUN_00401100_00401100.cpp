#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401100..0x00401102: FUN_00401100
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401100_00401100() {
    __asm {
    L_00401100:
        mov eax,ecx
    L_00401102:
        ret
    }
}
