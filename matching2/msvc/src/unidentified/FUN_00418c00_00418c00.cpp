#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418C00..0x00418C05: FUN_00418c00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00418c00_00418c00() {
    __asm {
    L_00418c00:
        mov eax,dword ptr [data_00491fc4]
    L_00418c05:
        ret
    }
}
