#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462DBD..0x00462DD8: FUN_00462dbd
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462dbd_00462dbd() {
    __asm {
    L_00462dbd:
        push esi
    L_00462dbe:
        mov esi,ecx
    L_00462dc0:
        call asm_FUN_00462d00_00462d00
    L_00462dc5:
        test byte ptr [esp+8],1
    L_00462dca:
        je short L_00462dd3
    L_00462dcc:
        push esi
    L_00462dcd:
        call asm_free_004524a1
    L_00462dd2:
        pop ecx
    L_00462dd3:
        mov eax,esi
    L_00462dd5:
        pop esi
    L_00462dd6:
        ret 4
    }
}
