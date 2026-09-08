#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A980..0x0042A983: FUN_0042a980
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042a980_0042a980() {
    __asm {
    L_0042a980:
        mov dword ptr [eax+28h],ecx
    L_0042a983:
        ret
    }
}
