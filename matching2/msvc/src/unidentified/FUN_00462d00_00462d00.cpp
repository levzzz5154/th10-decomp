#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462D00..0x00462D0A: FUN_00462d00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462d00_00462d00() {
    __asm {
    L_00462d00:
        mov dword ptr [ecx],46CA88h
    L_00462d06:
        jmp asm_exception_00462cac
    }
}
