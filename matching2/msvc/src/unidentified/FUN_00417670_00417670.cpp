#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417670..0x00417675: FUN_00417670
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00417670_00417670() {
    __asm {
    L_00417670:
        mov eax,dword ptr [data_00491fc4]
    L_00417675:
        ret
    }
}
