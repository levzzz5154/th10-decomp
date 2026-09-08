#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452170..0x00452175: Ordinal_11
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Ordinal_11_00452170() {
    __asm {
    L_00452170:
        jmp dword ptr [data_00466008]
    }
}
