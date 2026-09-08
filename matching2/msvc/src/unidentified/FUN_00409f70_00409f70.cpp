#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409F70..0x00409F76: FUN_00409f70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409f70_00409f70() {
    __asm {
    L_00409f70:
        mov ecx,dword ptr [eax+54h]
    L_00409f73:
        mov eax,dword ptr [ecx+8]
    L_00409f76:
        ret
    }
}
