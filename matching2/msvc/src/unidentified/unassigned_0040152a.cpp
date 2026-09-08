#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040152A..0x0040152F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040152a() {
    __asm {
    L_0040152a:
        int 3
    L_0040152b:
        int 3
    L_0040152c:
        int 3
    L_0040152d:
        int 3
    L_0040152e:
        int 3
    L_0040152f:
        int 3
    }
}
