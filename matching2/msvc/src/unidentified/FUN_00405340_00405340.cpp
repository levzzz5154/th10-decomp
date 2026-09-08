#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405340..0x00405350: FUN_00405340
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405340_00405340() {
    __asm {
    L_00405340:
        mov dword ptr [eax+73245Ch],1
    L_0040534a:
        mov dword ptr [eax+732458h],ecx
    L_00405350:
        ret
    }
}
