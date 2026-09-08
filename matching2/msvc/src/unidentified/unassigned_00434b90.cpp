#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434B90..0x00434B94: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00434b90() {
    __asm {
    L_00434b90:
        mov eax,dword ptr [eax]
    L_00434b92:
        add eax,ecx
    L_00434b94:
        ret
    }
}
