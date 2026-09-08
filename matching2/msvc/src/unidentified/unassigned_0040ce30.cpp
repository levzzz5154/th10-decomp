#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CE30..0x0040CE3D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040ce30() {
    __asm {
    L_0040ce30:
        mov edx,dword ptr [ecx+9EB8h]
    L_0040ce36:
        xor eax,eax
    L_0040ce38:
        test edx,edx
    L_0040ce3a:
        setne al
    L_0040ce3d:
        ret
    }
}
