#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405170..0x00405180: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405170() {
    __asm {
    L_00405170:
        mov ecx,dword ptr [esp+4]
    L_00405174:
        mov dword ptr [eax+40h],ecx
    L_00405177:
        or dword ptr [eax+35Ch],8
    L_0040517e:
        ret 4
    }
}
