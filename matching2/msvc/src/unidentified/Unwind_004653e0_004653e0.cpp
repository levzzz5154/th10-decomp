#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004653E0..0x004653EA: Unwind@004653e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004653e0_004653e0() {
    __asm {
    L_004653e0:
        mov ecx,dword ptr [ebp+4]
    L_004653e3:
        add ecx,10h
    L_004653e6:
        jmp asm_Platform_StopWorkerNoDelete_0044c130
    }
}
