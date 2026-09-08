#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404C50..0x00404C56: FUN_00404c50
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00404c50_00404c50() {
    __asm {
    L_00404c50:
        mov dword ptr [ecx+88h],eax
    L_00404c56:
        ret
    }
}
