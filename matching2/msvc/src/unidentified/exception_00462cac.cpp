#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462CAC..0x00462CC1: ~exception
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_exception_00462cac() {
    __asm {
    L_00462cac:
        cmp dword ptr [ecx+8],0
    L_00462cb0:
        mov dword ptr [ecx],46CA68h
    L_00462cb6:
        je short L_00462cc1
    L_00462cb8:
        push dword ptr [ecx+4]
    L_00462cbb:
        call asm_free_00452422
    L_00462cc0:
        pop ecx
    L_00462cc1:
        ret
    }
}
