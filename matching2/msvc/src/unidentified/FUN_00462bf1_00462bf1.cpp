#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462BF1..0x00462BFB: FUN_00462bf1
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462bf1_00462bf1() {
    __asm {
    L_00462bf1:
        mov eax,ecx
    L_00462bf3:
        mov dword ptr [eax],46CA54h
    L_00462bf9:
        ret 4
    }
}
