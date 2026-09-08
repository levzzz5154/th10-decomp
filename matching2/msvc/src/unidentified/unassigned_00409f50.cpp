#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409F50..0x00409F5F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00409f50() {
    __asm {
    L_00409f50:
        push edi
    L_00409f51:
        xor eax,eax
    L_00409f53:
        mov ecx,10h
    L_00409f58:
        mov edi,edx
    L_00409f5a:
        rep stosd
    L_00409f5c:
        mov eax,edx
    L_00409f5e:
        pop edi
    L_00409f5f:
        ret
    }
}
