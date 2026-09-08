#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CF10..0x0040CF19: FUN_0040cf10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040cf10_0040cf10() {
    __asm {
    L_0040cf10:
        mov eax,dword ptr [esp+4]
    L_0040cf14:
        mov dword ptr [ecx+44h],eax
    L_0040cf17:
        ret 4
    }
}
