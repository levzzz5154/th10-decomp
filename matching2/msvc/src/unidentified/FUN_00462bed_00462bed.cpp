#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462BED..0x00462BF0: FUN_00462bed
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462bed_00462bed() {
    __asm {
    L_00462bed:
        lea eax,[ecx+8]
    L_00462bf0:
        ret
    }
}
