#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B520..0x0040B525: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b520() {
    __asm {
    L_0040b520:
        add eax,1D86Ch
    L_0040b525:
        ret
    }
}
