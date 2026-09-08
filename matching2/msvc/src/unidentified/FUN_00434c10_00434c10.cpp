#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434C10..0x00434C1F: FUN_00434c10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00434c10_00434c10() {
    __asm {
    L_00434c10:
        mov eax,ecx
    L_00434c12:
        xor ecx,ecx
    L_00434c14:
        mov dword ptr [eax],ecx
    L_00434c16:
        mov dword ptr [eax+4],ecx
    L_00434c19:
        mov dword ptr [eax+8],ecx
    L_00434c1c:
        mov dword ptr [eax+0Ch],ecx
    L_00434c1f:
        ret
    }
}
