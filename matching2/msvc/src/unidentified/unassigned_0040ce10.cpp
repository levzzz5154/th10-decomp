#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CE10..0x0040CE24: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040ce10() {
    __asm {
    L_0040ce10:
        fld dword ptr [esp+4]
    L_0040ce14:
        mov dword ptr [ecx+eax*8+9E98h],edx
    L_0040ce1b:
        fstp dword ptr [ecx+eax*8+9E94h]
    L_0040ce22:
        ret 4
    }
}
