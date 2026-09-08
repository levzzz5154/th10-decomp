#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421F80..0x00421F92: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421f80() {
    __asm {
    L_00421f80:
        fld qword ptr [eax+24h]
    L_00421f83:
        fdiv qword ptr [eax+2Ch]
    L_00421f86:
        fmul dword ptr [data_00470b44]
    L_00421f8c:
        fsubr dword ptr [data_00470b44]
    L_00421f92:
        ret
    }
}
