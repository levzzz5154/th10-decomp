#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462D3C..0x00462D46: FUN_00462d3c
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462d3c_00462d3c() {
    __asm {
    L_00462d3c:
        mov dword ptr [ecx],46CA94h
    L_00462d42:
        jmp asm_exception_00462cac
    }
}
