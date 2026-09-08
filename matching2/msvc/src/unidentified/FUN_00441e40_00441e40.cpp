#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441E40..0x00441E4E: FUN_00441e40
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00441e40_00441e40() {
    __asm {
    L_00441e40:
        mov dword ptr [eax],ecx
    L_00441e42:
        mov ecx,dword ptr [esp+4]
    L_00441e46:
        mov dword ptr [eax+4],edx
    L_00441e49:
        mov dword ptr [eax+8],ecx
    L_00441e4c:
        ret 4
    }
}
