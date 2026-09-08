#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465190..0x00465197: Unwind@00465190
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465190_00465190() {
    __asm {
    L_00465190:
        mov ecx,dword ptr [ebp-10h]
    L_00465193:
        jmp asm_exception_00462cac
    }
}
