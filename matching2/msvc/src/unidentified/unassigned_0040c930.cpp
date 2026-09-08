#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C930..0x0040C939: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c930() {
    __asm {
    L_0040c930:
        mov edx,dword ptr [ecx]
    L_0040c932:
        xor eax,eax
    L_0040c934:
        test edx,edx
    L_0040c936:
        setg al
    L_0040c939:
        ret
    }
}
