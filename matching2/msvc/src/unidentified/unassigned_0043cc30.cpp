#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043CC30..0x0043CC3C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043cc30() {
    __asm {
    L_0043cc30:
        mov dword ptr [eax+5224h],2
    L_0043cc3a:
        xor eax,eax
    L_0043cc3c:
        ret
    }
}
