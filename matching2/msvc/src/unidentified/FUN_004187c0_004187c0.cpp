#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004187C0..0x004187C6: FUN_004187c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004187c0_004187c0() {
    __asm {
    L_004187c0:
        push ecx
    L_004187c1:
        call asm_FUN_00418190_00418190
    L_004187c6:
        ret
    }
}
