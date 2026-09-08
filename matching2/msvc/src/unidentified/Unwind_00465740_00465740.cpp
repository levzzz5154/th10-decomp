#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465740..0x0046574D: Unwind@00465740
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465740_00465740() {
    __asm {
    L_00465740:
        mov ecx,dword ptr [ebp+4]
    L_00465743:
        add ecx,9A48h
    L_00465749:
        jmp asm_Entity_Destructor_00401ff0
    }
}
