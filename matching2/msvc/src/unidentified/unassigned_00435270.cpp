#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00435270..0x0043527B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00435270() {
    __asm {
    L_00435270:
        mov ecx,dword ptr [eax]
    L_00435272:
        add ecx,4
    L_00435275:
        mov dword ptr [eax],ecx
    L_00435277:
        mov eax,ecx
    L_00435279:
        mov eax,dword ptr [eax]
    L_0043527b:
        ret
    }
}
