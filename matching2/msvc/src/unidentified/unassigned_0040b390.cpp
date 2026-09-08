#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B390..0x0040B390: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b390() {
    __asm {
    L_0040b390:
        ret
    }
}
