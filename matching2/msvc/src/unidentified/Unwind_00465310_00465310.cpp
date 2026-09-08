#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465310..0x0046531A: Unwind@00465310
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465310_00465310() {
    __asm {
    L_00465310:
        mov eax,dword ptr [ebp-48h]
    L_00465313:
        push eax
    L_00465314:
        call asm_free_004524a1
    L_00465319:
        pop ecx
    L_0046531a:
        ret
    }
}
