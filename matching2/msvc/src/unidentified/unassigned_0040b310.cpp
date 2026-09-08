#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B310..0x0040B312: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b310() {
    __asm {
    L_0040b310:
        xor eax,eax
    L_0040b312:
        ret
    }
}
