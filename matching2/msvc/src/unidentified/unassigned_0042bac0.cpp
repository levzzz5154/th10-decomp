#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BAC0..0x0042BACD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042bac0() {
    __asm {
    L_0042bac0:
        mov ecx,dword ptr [eax+4]
    L_0042bac3:
        mov edx,dword ptr [ecx+4]
    L_0042bac6:
        xor eax,eax
    L_0042bac8:
        test edx,edx
    L_0042baca:
        setne al
    L_0042bacd:
        ret
    }
}
