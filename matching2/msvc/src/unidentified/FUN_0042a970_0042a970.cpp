#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A970..0x0042A973: FUN_0042a970
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042a970_0042a970() {
    __asm {
    L_0042a970:
        mov dword ptr [eax+2Ch],ecx
    L_0042a973:
        ret
    }
}
