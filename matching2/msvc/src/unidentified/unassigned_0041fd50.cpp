#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FD50..0x0041FD6A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041fd50() {
    __asm {
    L_0041fd50:
        push esi
    L_0041fd51:
        call asm_FUN_0041fb50_0041fb50
    L_0041fd56:
        test byte ptr [esp+4],1
    L_0041fd5b:
        je short L_0041fd66
    L_0041fd5d:
        push esi
    L_0041fd5e:
        call asm_free_004524a1
    L_0041fd63:
        add esp,4
    L_0041fd66:
        mov eax,esi
    L_0041fd68:
        ret 4
    }
}
