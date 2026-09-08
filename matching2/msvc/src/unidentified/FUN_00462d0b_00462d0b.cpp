#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462D0B..0x00462D23: FUN_00462d0b
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462d0b_00462d0b() {
    __asm {
    L_00462d0b:
        push esi
    L_00462d0c:
        lea eax,[esp+8]
    L_00462d10:
        push eax
    L_00462d11:
        mov esi,ecx
    L_00462d13:
        call asm_FUN_00462c12_00462c12
    L_00462d18:
        mov dword ptr [esi],46CA94h
    L_00462d1e:
        mov eax,esi
    L_00462d20:
        pop esi
    L_00462d21:
        ret 4
    }
}
