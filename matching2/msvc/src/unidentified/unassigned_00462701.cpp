#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462701..0x00462705: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00462701() {
    __asm {
    L_00462701:
        pop ebx
    L_00462702:
        leave
    L_00462703:
        ret 8
    }
}
