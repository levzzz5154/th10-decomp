#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418AD0..0x00418AE4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418ad0() {
    __asm {
    L_00418ad0:
        lea edx,[ecx*8]
    L_00418ad7:
        mov ecx,dword ptr [eax+60h]
    L_00418ada:
        xor edx,ecx
    L_00418adc:
        and edx,8
    L_00418adf:
        xor ecx,edx
    L_00418ae1:
        mov dword ptr [eax+60h],ecx
    L_00418ae4:
        ret
    }
}
