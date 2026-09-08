#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421C70..0x00421C88: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421c70() {
    __asm {
    L_00421c70:
        lea eax,[esi+esi*2]
    L_00421c73:
        lea ecx,[edi+eax*8+64Ch]
    L_00421c7a:
        push ecx
    L_00421c7b:
        call dword ptr [data_004660b0]
    L_00421c81:
        inc byte ptr [esi+edi+6F4h]
    L_00421c88:
        ret
    }
}
