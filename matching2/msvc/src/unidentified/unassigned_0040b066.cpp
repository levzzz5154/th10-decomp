#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B066..0x0040B06F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b066() {
    __asm {
    L_0040b066:
        int 3
    L_0040b067:
        int 3
    L_0040b068:
        int 3
    L_0040b069:
        int 3
    L_0040b06a:
        int 3
    L_0040b06b:
        int 3
    L_0040b06c:
        int 3
    L_0040b06d:
        int 3
    L_0040b06e:
        int 3
    L_0040b06f:
        int 3
    }
}
