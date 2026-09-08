#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441FE0..0x00441FE3: FUN_00441fe0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00441fe0_00441fe0() {
    __asm {
    L_00441fe0:
        mov dword ptr [ecx+28h],eax
    L_00441fe3:
        ret
    }
}
