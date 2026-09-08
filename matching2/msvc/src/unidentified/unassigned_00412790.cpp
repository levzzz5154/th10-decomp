#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412790..0x0041279B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412790() {
    __asm {
    L_00412790:
        add eax,24Ah
    L_00412795:
        shl eax,4
    L_00412798:
        mov dword ptr [eax+ecx],edx
    L_0041279b:
        ret
    }
}
