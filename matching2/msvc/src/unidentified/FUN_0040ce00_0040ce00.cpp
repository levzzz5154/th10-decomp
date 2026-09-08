#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CE00..0x0040CE06: FUN_0040ce00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ce00_0040ce00() {
    __asm {
    L_0040ce00:
        mov dword ptr [eax+9E90h],ecx
    L_0040ce06:
        ret
    }
}
