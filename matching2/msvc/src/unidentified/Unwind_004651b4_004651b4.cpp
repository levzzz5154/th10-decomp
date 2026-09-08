#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004651B4..0x004651BB: Unwind@004651b4
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004651b4_004651b4() {
    __asm {
    L_004651b4:
        mov ecx,dword ptr [ebp-10h]
    L_004651b7:
        jmp asm_exception_00462cac
    }
}
