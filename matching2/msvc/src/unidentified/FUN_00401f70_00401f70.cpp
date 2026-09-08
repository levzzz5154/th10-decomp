#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401F70..0x00401F77: FUN_00401f70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401f70_00401f70() {
    __asm {
    L_00401f70:
        mov dword ptr [eax+44h],0
    L_00401f77:
        ret
    }
}
