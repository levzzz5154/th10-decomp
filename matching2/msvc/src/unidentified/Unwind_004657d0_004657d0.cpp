#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004657D0..0x004657DA: Unwind@004657d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004657d0_004657d0() {
    __asm {
    L_004657d0:
        mov ecx,dword ptr [ebp+4]
    L_004657d3:
        add ecx,10h
    L_004657d6:
        jmp asm_Platform_StopWorkerNoDelete_0044c130
    }
}
