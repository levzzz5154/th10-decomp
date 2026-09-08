#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00403057..0x0040305F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00403057() {
    __asm {
    L_00403057:
        int 3
    L_00403058:
        int 3
    L_00403059:
        int 3
    L_0040305a:
        int 3
    L_0040305b:
        int 3
    L_0040305c:
        int 3
    L_0040305d:
        int 3
    L_0040305e:
        int 3
    L_0040305f:
        int 3
    }
}
