#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C84C..0x0041C84F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041c84c() {
    __asm {
    L_0041c84c:
        int 3
    L_0041c84d:
        int 3
    L_0041c84e:
        int 3
    L_0041c84f:
        int 3
    }
}
