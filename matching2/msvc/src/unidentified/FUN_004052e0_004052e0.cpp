#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004052E0..0x004052F4: FUN_004052e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004052e0_004052e0() {
    __asm {
    L_004052e0:
        mov dword ptr [eax+73245Ch],0
    L_004052ea:
        mov dword ptr [eax+732458h],80808080h
    L_004052f4:
        ret
    }
}
