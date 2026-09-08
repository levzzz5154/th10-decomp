#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462D77..0x00462D81: FUN_00462d77
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462d77_00462d77() {
    __asm {
    L_00462d77:
        mov dword ptr [ecx],46CA94h
    L_00462d7d:
        jmp asm_exception_00462cac
    }
}
