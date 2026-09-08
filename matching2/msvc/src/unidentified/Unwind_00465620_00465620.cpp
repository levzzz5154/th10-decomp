#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465620..0x0046562D: Unwind@00465620
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465620_00465620() {
    __asm {
    L_00465620:
        mov ecx,dword ptr [ebp+4]
    L_00465623:
        add ecx,5AB0h
    L_00465629:
        jmp asm_Platform_StopWorkerNoDelete_0044c130
    }
}
