#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00403067..0x0040306F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00403067() {
    __asm {
    L_00403067:
        int 3
    L_00403068:
        int 3
    L_00403069:
        int 3
    L_0040306a:
        int 3
    L_0040306b:
        int 3
    L_0040306c:
        int 3
    L_0040306d:
        int 3
    L_0040306e:
        int 3
    L_0040306f:
        int 3
    }
}
