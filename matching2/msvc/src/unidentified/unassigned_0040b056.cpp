#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B056..0x0040B05F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b056() {
    __asm {
    L_0040b056:
        int 3
    L_0040b057:
        int 3
    L_0040b058:
        int 3
    L_0040b059:
        int 3
    L_0040b05a:
        int 3
    L_0040b05b:
        int 3
    L_0040b05c:
        int 3
    L_0040b05d:
        int 3
    L_0040b05e:
        int 3
    L_0040b05f:
        int 3
    }
}
