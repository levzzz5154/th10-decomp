#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004176E0..0x004176E3: FUN_004176e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004176e0_004176e0() {
    __asm {
    L_004176e0:
        mov eax,dword ptr [eax+4]
    L_004176e3:
        ret
    }
}
