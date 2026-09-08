#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462BFC..0x00462C00: FUN_00462bfc
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462bfc_00462bfc() {
    __asm {
    L_00462bfc:
        mov eax,ecx
    L_00462bfe:
        ret 4
    }
}
