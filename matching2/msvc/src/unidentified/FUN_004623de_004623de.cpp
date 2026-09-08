#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004623DE..0x004623E8: FUN_004623de
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004623de_004623de() {
    __asm {
    L_004623de:
        mov dword ptr [ecx],46C9F4h
    L_004623e4:
        jmp asm_FUN_00462371_00462371
    }
}
