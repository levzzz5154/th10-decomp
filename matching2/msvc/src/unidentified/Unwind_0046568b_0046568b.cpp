#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046568B..0x00465695: Unwind@0046568b
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_0046568b_0046568b() {
    __asm {
    L_0046568b:
        mov ecx,dword ptr [ebp+4]
    L_0046568e:
        add ecx,30h
    L_00465691:
        jmp asm_Entity_Destructor_00401ff0
    }
}
