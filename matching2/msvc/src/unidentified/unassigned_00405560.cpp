#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405560..0x00405569: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405560() {
    __asm {
    L_00405560:
        mov eax,dword ptr [eax+378Ch]
    L_00405566:
        and eax,1
    L_00405569:
        ret
    }
}
