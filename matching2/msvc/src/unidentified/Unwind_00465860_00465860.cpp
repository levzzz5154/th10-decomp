#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465860..0x0046586A: Unwind@00465860
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465860_00465860() {
    __asm {
    L_00465860:
        mov eax,dword ptr [ebp-10h]
    L_00465863:
        push eax
    L_00465864:
        call asm_free_004524a1
    L_00465869:
        pop ecx
    L_0046586a:
        ret
    }
}
