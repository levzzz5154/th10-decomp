#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F294..0x0045F29C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045f294() {
    __asm {
    L_0045f294:
        xor eax,eax
    L_0045f296:
        inc eax
    L_0045f297:
        ret
    L_0045f298:
        mov esp,dword ptr [ebp-18h]
    L_0045f29b:
        TH10_REL8(0xeb, 0x0045f29b, VA_asm_target_0045f28b)
    }
}
