#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004452E0..0x004452E9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004452e0() {
    __asm {
    L_004452e0:
        mov eax,dword ptr [eax+35Ch]
    L_004452e6:
        and eax,1
    L_004452e9:
        ret
    }
}
