#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BA90..0x0042BA9C: FUN_0042ba90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042ba90_0042ba90() {
    __asm {
    L_0042ba90:
        mov eax,dword ptr [esp+4]
    L_0042ba94:
        mov dword ptr [ecx+344h],eax
    L_0042ba9a:
        ret 4
    }
}
