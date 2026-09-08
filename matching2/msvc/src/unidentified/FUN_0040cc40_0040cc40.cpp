#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CC40..0x0040CC46: FUN_0040cc40
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040cc40_0040cc40() {
    __asm {
    L_0040cc40:
        mov ecx,dword ptr [eax+4]
    L_0040cc43:
        mov eax,dword ptr [ecx+4]
    L_0040cc46:
        ret
    }
}
