#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441D60..0x00441D63: FUN_00441d60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00441d60_00441d60() {
    __asm {
    L_00441d60:
        mov eax,dword ptr [eax+34h]
    L_00441d63:
        ret
    }
}
