#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462D82..0x00462D9D: FUN_00462d82
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462d82_00462d82() {
    __asm {
    L_00462d82:
        push esi
    L_00462d83:
        mov esi,ecx
    L_00462d85:
        call asm_exception_00462cac
    L_00462d8a:
        test byte ptr [esp+8],1
    L_00462d8f:
        je short L_00462d98
    L_00462d91:
        push esi
    L_00462d92:
        call asm_free_004524a1
    L_00462d97:
        pop ecx
    L_00462d98:
        mov eax,esi
    L_00462d9a:
        pop esi
    L_00462d9b:
        ret 4
    }
}
