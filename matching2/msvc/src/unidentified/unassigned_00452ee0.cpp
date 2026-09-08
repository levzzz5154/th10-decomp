#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452EE0..0x00452EEA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00452ee0() {
    __asm {
    L_00452ee0:
        mov esp,dword ptr [ebp-18h]
    L_00452ee3:
        push dword ptr [ebp-1Ch]
    L_00452ee6:
        call asm_exit_004576fd
    }
}
