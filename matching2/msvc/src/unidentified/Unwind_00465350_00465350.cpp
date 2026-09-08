#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465350..0x00465357: Unwind@00465350
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465350_00465350() {
    __asm {
    L_00465350:
        mov eax,dword ptr [ebp+4]
    L_00465353:
        jmp asm_D3DResourceList_ClearPending_00449a90
    }
}
