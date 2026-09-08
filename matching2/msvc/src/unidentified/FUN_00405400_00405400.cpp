#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405400..0x00405402: FUN_00405400
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405400_00405400() {
    __asm {
    L_00405400:
        mov eax,ecx
    L_00405402:
        ret
    }
}
