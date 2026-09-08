#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465880..0x0046588A: Unwind@00465880
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465880_00465880() {
    __asm {
    L_00465880:
        mov eax,dword ptr [ebp-10h]
    L_00465883:
        push eax
    L_00465884:
        call asm_free_004524a1
    L_00465889:
        pop ecx
    L_0046588a:
        ret
    }
}
