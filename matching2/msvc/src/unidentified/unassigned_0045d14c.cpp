#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D14C..0x0045D15B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045d14c() {
    __asm {
    L_0045d14c:
        mov eax,dword ptr [data_00497f98]
    L_0045d151:
        neg eax
    L_0045d153:
        sbb eax,eax
    L_0045d155:
        and eax,dword ptr [data_004980a4]
    L_0045d15b:
        ret
    }
}
