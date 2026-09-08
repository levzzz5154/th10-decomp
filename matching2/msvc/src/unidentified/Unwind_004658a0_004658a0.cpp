#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004658A0..0x004658AA: Unwind@004658a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004658a0_004658a0() {
    __asm {
    L_004658a0:
        mov eax,dword ptr [ebp-10h]
    L_004658a3:
        push eax
    L_004658a4:
        call asm_free_004524a1
    L_004658a9:
        pop ecx
    L_004658aa:
        ret
    }
}
