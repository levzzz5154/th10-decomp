#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004654C0..0x004654CD: Unwind@004654c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004654c0_004654c0() {
    __asm {
    L_004654c0:
        mov ecx,dword ptr [ebp+4]
    L_004654c3:
        add ecx,0D0h
    L_004654c9:
        jmp asm_Platform_StopWorkerNoDelete_0044c130
    }
}
