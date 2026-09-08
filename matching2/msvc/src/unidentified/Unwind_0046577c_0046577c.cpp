#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046577C..0x00465789: Unwind@0046577c
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_0046577c_0046577c() {
    __asm {
    L_0046577c:
        mov ecx,dword ptr [ebp+4]
    L_0046577f:
        add ecx,3AD130h
    L_00465785:
        jmp asm_Entity_Destructor_00401ff0
    }
}
