#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417660..0x0041766F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417660() {
    __asm {
    L_00417660:
        mov edx,dword ptr [ecx]
    L_00417662:
        mov ecx,dword ptr [esp+4]
    L_00417666:
        xor eax,eax
    L_00417668:
        cmp edx,ecx
    L_0041766a:
        setne al
    L_0041766d:
        ret 4
    }
}
