#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004053B0..0x004053C6: FUN_004053b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004053b0_004053b0() {
    __asm {
    L_004053b0:
        mov ecx,dword ptr [esp+4]
    L_004053b4:
        mov edx,dword ptr [esp+8]
    L_004053b8:
        mov dword ptr [eax],ecx
    L_004053ba:
        mov ecx,dword ptr [esp+0Ch]
    L_004053be:
        mov dword ptr [eax+4],edx
    L_004053c1:
        mov dword ptr [eax+8],ecx
    L_004053c4:
        ret 0Ch
    }
}
