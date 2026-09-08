#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465680..0x0046568A: Unwind@00465680
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465680_00465680() {
    __asm {
    L_00465680:
        mov ecx,dword ptr [ebp+4]
    L_00465683:
        add ecx,10h
    L_00465686:
        jmp asm_Platform_StopWorkerNoDelete_0044c130
    }
}
