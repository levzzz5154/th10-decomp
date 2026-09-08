#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004556FB..0x00455707: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004556fb() {
    __asm {
    L_004556fb:
        jmp short L_00455704
    L_004556fd:
        xor eax,eax
    L_004556ff:
        inc eax
    L_00455700:
        ret
    L_00455701:
        mov esp,dword ptr [ebp-18h]
    L_00455704:
        or dword ptr [ebp-4],0FFFFFFFFh
    }
}
