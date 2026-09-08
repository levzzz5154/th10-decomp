#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004653C0..0x004653CA: Unwind@004653c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004653c0_004653c0() {
    __asm {
    L_004653c0:
        mov eax,dword ptr [ebp-10h]
    L_004653c3:
        push eax
    L_004653c4:
        call asm_free_004524a1
    L_004653c9:
        pop ecx
    L_004653ca:
        ret
    }
}
