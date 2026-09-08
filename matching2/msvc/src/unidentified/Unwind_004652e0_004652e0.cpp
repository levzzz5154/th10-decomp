#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004652E0..0x004652EA: Unwind@004652e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004652e0_004652e0() {
    __asm {
    L_004652e0:
        mov ecx,dword ptr [ebp+4]
    L_004652e3:
        add ecx,14h
    L_004652e6:
        jmp asm_Entity_Destructor_00401ff0
    }
}
