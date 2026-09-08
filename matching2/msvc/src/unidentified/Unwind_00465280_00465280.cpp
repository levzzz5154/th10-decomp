#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465280..0x0046528A: Unwind@00465280
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465280_00465280() {
    __asm {
    L_00465280:
        mov ecx,dword ptr [ebp+4]
    L_00465283:
        add ecx,14h
    L_00465286:
        jmp asm_Entity_Destructor_00401ff0
    }
}
