#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004243E0..0x004243EF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004243e0() {
    __asm {
    L_004243e0:
        mov edx,dword ptr [ecx]
    L_004243e2:
        mov ecx,dword ptr [esp+4]
    L_004243e6:
        xor eax,eax
    L_004243e8:
        cmp edx,ecx
    L_004243ea:
        setne al
    L_004243ed:
        ret 4
    }
}
