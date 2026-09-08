#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465330..0x0046533A: Unwind@00465330
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465330_00465330() {
    __asm {
    L_00465330:
        mov eax,dword ptr [ebp-48h]
    L_00465333:
        push eax
    L_00465334:
        call asm_free_004524a1
    L_00465339:
        pop ecx
    L_0046533a:
        ret
    }
}
