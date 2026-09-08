#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413160..0x00413169: FUN_00413160
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413160_00413160() {
    __asm {
    L_00413160:
        mov eax,dword ptr [esp+4]
    L_00413164:
        mov dword ptr [ecx+18h],eax
    L_00413167:
        ret 4
    }
}
