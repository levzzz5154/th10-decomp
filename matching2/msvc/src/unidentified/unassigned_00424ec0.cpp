#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424EC0..0x00424EC2: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00424ec0() {
    __asm {
    L_00424ec0:
        xor eax,eax
    L_00424ec2:
        ret
    }
}
