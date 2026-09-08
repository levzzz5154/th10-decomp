#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465230..0x0046523A: Unwind@00465230
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465230_00465230() {
    __asm {
    L_00465230:
        mov ecx,dword ptr [ebp+4]
    L_00465233:
        add ecx,18h
    L_00465236:
        jmp asm_Entity_Destructor_00401ff0
    }
}
