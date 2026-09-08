#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00446210..0x00446212: FUN_00446210
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00446210_00446210() {
    __asm {
    L_00446210:
        mov eax,ecx
    L_00446212:
        ret
    }
}
