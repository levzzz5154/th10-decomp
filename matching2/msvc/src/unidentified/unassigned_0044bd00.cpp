#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044BD00..0x0044BD0F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044bd00() {
    __asm {
    L_0044bd00:
        push 0
    L_0044bd02:
        push eax
    L_0044bd03:
        call dword ptr [data_00466200]
    L_0044bd09:
        neg eax
    L_0044bd0b:
        sbb eax,eax
    L_0044bd0d:
        neg eax
    L_0044bd0f:
        ret
    }
}
