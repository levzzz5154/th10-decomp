#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413050..0x00413060: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413050() {
    __asm {
    L_00413050:
        mov edx,dword ptr [ecx+4]
    L_00413053:
        mov ecx,dword ptr [esp+4]
    L_00413057:
        xor eax,eax
    L_00413059:
        cmp edx,ecx
    L_0041305b:
        setl al
    L_0041305e:
        ret 4
    }
}
