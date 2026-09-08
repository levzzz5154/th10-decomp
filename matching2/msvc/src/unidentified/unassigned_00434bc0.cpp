#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434BC0..0x00434BD3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00434bc0() {
    __asm {
    L_00434bc0:
        mov ecx,dword ptr [eax+0D4h]
    L_00434bc6:
        mov dword ptr [eax+ecx*4+90h],edx
    L_00434bcd:
        inc dword ptr [eax+0D4h]
    L_00434bd3:
        ret
    }
}
