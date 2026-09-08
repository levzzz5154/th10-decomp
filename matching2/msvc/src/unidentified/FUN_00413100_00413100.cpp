#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413100..0x00413108: FUN_00413100
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413100_00413100() {
    __asm {
    L_00413100:
        mov eax,dword ptr [esp+4]
    L_00413104:
        mov dword ptr [ecx],eax
    L_00413106:
        ret 4
    }
}
