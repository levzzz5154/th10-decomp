#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418BE0..0x00418BE3: FUN_00418be0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00418be0_00418be0() {
    __asm {
    L_00418be0:
        mov dword ptr [eax+50h],ecx
    L_00418be3:
        ret
    }
}
