#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004176C0..0x004176C2: FUN_004176c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004176c0_004176c0() {
    __asm {
    L_004176c0:
        mov dword ptr [eax],ecx
    L_004176c2:
        ret
    }
}
