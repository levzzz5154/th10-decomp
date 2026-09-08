#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412F20..0x00412F29: FUN_00412f20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412f20_00412f20() {
    __asm {
    L_00412f20:
        mov eax,dword ptr [esp+4]
    L_00412f24:
        mov dword ptr [ecx+0Ch],eax
    L_00412f27:
        ret 4
    }
}
