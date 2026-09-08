#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004203A0..0x004203BD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004203a0() {
    __asm {
    L_004203a0:
        push esi
    L_004203a1:
        mov esi,eax
    L_004203a3:
        call asm_TimerWin32_Release_004203c0
    L_004203a8:
        test byte ptr [esp+8],1
    L_004203ad:
        je short L_004203b8
    L_004203af:
        push esi
    L_004203b0:
        call asm_free_004524a1
    L_004203b5:
        add esp,4
    L_004203b8:
        mov eax,esi
    L_004203ba:
        pop esi
    L_004203bb:
        ret 4
    }
}
