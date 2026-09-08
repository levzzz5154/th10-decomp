#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CE80..0x0040CE8A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040ce80() {
    __asm {
    L_0040ce80:
        mov edx,dword ptr [ecx+28h]
    L_0040ce83:
        xor eax,eax
    L_0040ce85:
        test edx,edx
    L_0040ce87:
        setne al
    L_0040ce8a:
        ret
    }
}
