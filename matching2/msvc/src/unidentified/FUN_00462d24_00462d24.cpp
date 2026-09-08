#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462D24..0x00462D3B: FUN_00462d24
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462d24_00462d24() {
    __asm {
    L_00462d24:
        push esi
    L_00462d25:
        push dword ptr [esp+8]
    L_00462d29:
        mov esi,ecx
    L_00462d2b:
        call asm_FUN_00462c5a_00462c5a
    L_00462d30:
        mov dword ptr [esi],46CA94h
    L_00462d36:
        mov eax,esi
    L_00462d38:
        pop esi
    L_00462d39:
        ret 4
    }
}
