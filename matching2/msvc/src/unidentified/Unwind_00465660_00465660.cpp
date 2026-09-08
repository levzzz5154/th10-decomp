#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465660..0x0046566A: Unwind@00465660
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465660_00465660() {
    __asm {
    L_00465660:
        mov eax,dword ptr [ebp-10h]
    L_00465663:
        push eax
    L_00465664:
        call asm_free_004524a1
    L_00465669:
        pop ecx
    L_0046566a:
        ret
    }
}
