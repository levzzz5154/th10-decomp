#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004087C0..0x004087C8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004087c0() {
    __asm {
    L_004087c0:
        mov eax,dword ptr [eax+58h]
    L_004087c3:
        shr eax,1
    L_004087c5:
        and eax,1
    L_004087c8:
        ret
    }
}
