#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004651FC..0x00465209: Unwind@004651fc
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004651fc_004651fc() {
    __asm {
    L_004651fc:
        mov ecx,dword ptr [ebp+4]
    L_004651ff:
        add ecx,3AD130h
    L_00465205:
        jmp asm_Entity_Destructor_00401ff0
    }
}
