#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004652EB..0x004652F8: Unwind@004652eb
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004652eb_004652eb() {
    __asm {
    L_004652eb:
        mov ecx,dword ptr [ebp+4]
    L_004652ee:
        add ecx,3C0h
    L_004652f4:
        jmp asm_Entity_Destructor_00401ff0
    }
}
