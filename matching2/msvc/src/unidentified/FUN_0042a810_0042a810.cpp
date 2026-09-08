#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A810..0x0042A816: FUN_0042a810
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042a810_0042a810() {
    __asm {
    L_0042a810:
        mov dword ptr [eax],52455355h
    L_0042a816:
        ret
    }
}
