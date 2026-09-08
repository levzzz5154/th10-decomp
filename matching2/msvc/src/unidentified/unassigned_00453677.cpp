#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453677..0x00453681: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00453677() {
    __asm {
    L_00453677:
        mov esp,dword ptr [ebp-18h]
    L_0045367a:
        push dword ptr [ebp-1Ch]
    L_0045367d:
        call asm_exit_004576fd
    }
}
