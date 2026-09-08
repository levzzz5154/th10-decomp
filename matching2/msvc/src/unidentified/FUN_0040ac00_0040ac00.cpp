#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AC00..0x0040AC02: FUN_0040ac00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ac00_0040ac00() {
    __asm {
    L_0040ac00:
        mov eax,dword ptr [eax]
    L_0040ac02:
        ret
    }
}
