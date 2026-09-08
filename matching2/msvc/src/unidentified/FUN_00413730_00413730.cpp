#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413730..0x00413736: FUN_00413730
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413730_00413730() {
    __asm {
    L_00413730:
        mov eax,dword ptr [eax+9E80h]
    L_00413736:
        ret
    }
}
