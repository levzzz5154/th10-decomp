#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004458F0..0x004458F2: FUN_004458f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004458f0_004458f0() {
    __asm {
    L_004458f0:
        mov eax,ecx
    L_004458f2:
        ret
    }
}
