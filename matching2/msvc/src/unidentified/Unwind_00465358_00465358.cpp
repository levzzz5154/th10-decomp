#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465358..0x00465362: Unwind@00465358
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465358_00465358() {
    __asm {
    L_00465358:
        mov eax,dword ptr [ebp+4]
    L_0046535b:
        add eax,24h
    L_0046535e:
        jmp asm_D3DResourceList_ClearPending_00449a90
    }
}
