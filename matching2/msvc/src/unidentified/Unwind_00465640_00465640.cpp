#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465640..0x0046564A: Unwind@00465640
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465640_00465640() {
    __asm {
    L_00465640:
        mov eax,dword ptr [ebp-10h]
    L_00465643:
        push eax
    L_00465644:
        call asm_free_004524a1
    L_00465649:
        pop ecx
    L_0046564a:
        ret
    }
}
