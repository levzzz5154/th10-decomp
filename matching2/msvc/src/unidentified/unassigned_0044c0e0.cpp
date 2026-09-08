#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C0E0..0x0044C0F4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c0e0() {
    __asm {
    L_0044c0e0:
        xor ecx,ecx
    L_0044c0e2:
        mov dword ptr [eax],4703E4h
    L_0044c0e8:
        mov dword ptr [eax+4],ecx
    L_0044c0eb:
        mov dword ptr [eax+8],ecx
    L_0044c0ee:
        mov dword ptr [eax+0Ch],ecx
    L_0044c0f1:
        mov dword ptr [eax+10h],ecx
    L_0044c0f4:
        ret
    }
}
