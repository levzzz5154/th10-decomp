#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418B50..0x00418B54: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418b50() {
    __asm {
    L_00418b50:
        and dword ptr [eax+60h],0FFFFFFFBh
    L_00418b54:
        ret
    }
}
