#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041AF90..0x0041AFAA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041af90() {
    __asm {
    L_0041af90:
        push esi
    L_0041af91:
        call asm_FUN_0041adf0_0041adf0
    L_0041af96:
        test byte ptr [esp+4],1
    L_0041af9b:
        je short L_0041afa6
    L_0041af9d:
        push esi
    L_0041af9e:
        call asm_free_004524a1
    L_0041afa3:
        add esp,4
    L_0041afa6:
        mov eax,esi
    L_0041afa8:
        ret 4
    }
}
