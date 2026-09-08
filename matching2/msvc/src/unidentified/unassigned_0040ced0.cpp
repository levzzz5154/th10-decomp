#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CED0..0x0040CEDC: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040ced0() {
    __asm {
    L_0040ced0:
        mov eax,dword ptr [eax+378Ch]
    L_0040ced6:
        shr eax,3
    L_0040ced9:
        and eax,1
    L_0040cedc:
        ret
    }
}
