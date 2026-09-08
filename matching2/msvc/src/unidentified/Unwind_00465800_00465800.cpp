#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465800..0x0046580A: Unwind@00465800
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465800_00465800() {
    __asm {
    L_00465800:
        mov eax,dword ptr [ebp-10h]
    L_00465803:
        push eax
    L_00465804:
        call asm_free_004524a1
    L_00465809:
        pop ecx
    L_0046580a:
        ret
    }
}
