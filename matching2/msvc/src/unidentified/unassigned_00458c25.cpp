#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00458C25..0x00458C38: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00458c25() {
    __asm {
    L_00458c25:
        mov eax,dword ptr [esp+4]
    L_00458c29:
        neg eax
    L_00458c2b:
        sbb eax,eax
    L_00458c2d:
        and eax,dword ptr [data_00499304]
    L_00458c33:
        mov dword ptr [data_00499300],eax
    L_00458c38:
        ret
    }
}
