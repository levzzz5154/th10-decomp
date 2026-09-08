#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465840..0x0046584A: Unwind@00465840
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465840_00465840() {
    __asm {
    L_00465840:
        mov eax,dword ptr [ebp-10h]
    L_00465843:
        push eax
    L_00465844:
        call asm_free_004524a1
    L_00465849:
        pop ecx
    L_0046584a:
        ret
    }
}
