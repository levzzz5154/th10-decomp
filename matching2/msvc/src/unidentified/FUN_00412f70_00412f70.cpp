#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412F70..0x00412F7F: FUN_00412f70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412f70_00412f70() {
    __asm {
    L_00412f70:
        mov ecx,dword ptr [esp+4]
    L_00412f74:
        mov edx,dword ptr [esp+8]
    L_00412f78:
        mov dword ptr [eax],ecx
    L_00412f7a:
        mov dword ptr [eax+4],edx
    L_00412f7d:
        ret 8
    }
}
