#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417620..0x00417626: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417620() {
    __asm {
    L_00417620:
        movzx eax,word ptr [eax+2Ch]
    L_00417624:
        and eax,ecx
    L_00417626:
        ret
    }
}
