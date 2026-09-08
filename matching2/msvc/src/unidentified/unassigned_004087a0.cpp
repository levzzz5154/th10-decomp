#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004087A0..0x004087B0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004087a0() {
    __asm {
    L_004087a0:
        mov ecx,dword ptr [esp+4]
    L_004087a4:
        mov dword ptr [eax+2Ch],ecx
    L_004087a7:
        or dword ptr [eax+35Ch],4
    L_004087ae:
        ret 4
    }
}
