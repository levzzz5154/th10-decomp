#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004383F0..0x004383F4: FUN_004383f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004383f0_004383f0() {
    __asm {
    L_004383f0:
        mov eax,ecx
    L_004383f2:
        ret 4
    }
}
