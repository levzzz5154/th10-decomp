#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042B9A0..0x0042B9A6: FUN_0042b9a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042b9a0_0042b9a0() {
    __asm {
    L_0042b9a0:
        mov eax,ecx
    L_0042b9a2:
        jmp asm_EffectPool_UpdateDrops_0042b6f0
    }
}
