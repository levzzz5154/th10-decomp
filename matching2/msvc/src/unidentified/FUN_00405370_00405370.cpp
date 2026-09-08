#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405370..0x00405378: FUN_00405370
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405370_00405370() {
    __asm {
    L_00405370:
        mov eax,dword ptr [esp+4]
    L_00405374:
        mov dword ptr [ecx],eax
    L_00405376:
        ret 4
    }
}
