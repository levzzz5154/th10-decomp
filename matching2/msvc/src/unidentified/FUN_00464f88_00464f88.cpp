#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00464F88..0x00464F9D: FUN_00464f88
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00464f88_00464f88() {
    __asm {
    L_00464f88:
        mov eax,dword ptr [esp+8]
    L_00464f8c:
        and eax,7FF00000h
    L_00464f91:
        cmp eax,7FF00000h
    L_00464f96:
        je short L_00464f99
    L_00464f98:
        ret
    L_00464f99:
        mov eax,dword ptr [esp+8]
    L_00464f9d:
        ret
    }
}
