#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462D47..0x00462D76: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00462d47() {
    __asm {
    L_00462d47:
        push esi
    L_00462d48:
        push dword ptr [esp+8]
    L_00462d4c:
        mov esi,ecx
    L_00462d4e:
        call asm_FUN_00462d0b_00462d0b
    L_00462d53:
        mov dword ptr [esi],46CAA0h
    L_00462d59:
        mov eax,esi
    L_00462d5b:
        pop esi
    L_00462d5c:
        ret 4
    L_00462d5f:
        push esi
    L_00462d60:
        push dword ptr [esp+8]
    L_00462d64:
        mov esi,ecx
    L_00462d66:
        call asm_FUN_00462d24_00462d24
    L_00462d6b:
        mov dword ptr [esi],46CAA0h
    L_00462d71:
        mov eax,esi
    L_00462d73:
        pop esi
    L_00462d74:
        ret 4
    }
}
