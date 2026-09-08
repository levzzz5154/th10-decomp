#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465820..0x0046582A: Unwind@00465820
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465820_00465820() {
    __asm {
    L_00465820:
        mov eax,dword ptr [ebp-10h]
    L_00465823:
        push eax
    L_00465824:
        call asm_free_004524a1
    L_00465829:
        pop ecx
    L_0046582a:
        ret
    }
}
