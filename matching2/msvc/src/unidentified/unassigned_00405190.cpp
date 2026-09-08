#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405190..0x004051A0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405190() {
    __asm {
    L_00405190:
        mov ecx,dword ptr [esp+4]
    L_00405194:
        mov dword ptr [eax+3Ch],ecx
    L_00405197:
        or dword ptr [eax+35Ch],8
    L_0040519e:
        ret 4
    }
}
