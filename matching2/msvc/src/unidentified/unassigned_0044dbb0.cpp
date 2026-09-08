#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DBB0..0x0044DBC0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044dbb0() {
    __asm {
    L_0044dbb0:
        xor ecx,ecx
    L_0044dbb2:
        mov dword ptr [eax+90h],ecx
    L_0044dbb8:
        mov dword ptr [eax],ecx
    L_0044dbba:
        mov dword ptr [eax+2Ch],ecx
    L_0044dbbd:
        mov dword ptr [eax+7Ch],ecx
    L_0044dbc0:
        ret
    }
}
