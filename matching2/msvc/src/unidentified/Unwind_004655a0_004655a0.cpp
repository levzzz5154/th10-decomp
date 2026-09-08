#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004655A0..0x004655AA: Unwind@004655a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004655a0_004655a0() {
    __asm {
    L_004655a0:
        mov eax,dword ptr [ebp-10h]
    L_004655a3:
        push eax
    L_004655a4:
        call asm_free_004524a1
    L_004655a9:
        pop ecx
    L_004655aa:
        ret
    }
}
