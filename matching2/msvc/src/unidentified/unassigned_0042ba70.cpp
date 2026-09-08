#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BA70..0x0042BA80: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042ba70() {
    __asm {
    L_0042ba70:
        mov ecx,dword ptr [esp+4]
    L_0042ba74:
        mov dword ptr [eax+4Ch],ecx
    L_0042ba77:
        or dword ptr [eax+35Ch],8
    L_0042ba7e:
        ret 4
    }
}
