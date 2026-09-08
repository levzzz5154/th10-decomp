#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418B10..0x00418B20: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418b10() {
    __asm {
    L_00418b10:
        mov ecx,dword ptr [eax+60h]
    L_00418b13:
        xor ecx,edx
    L_00418b15:
        mov edx,dword ptr [eax+60h]
    L_00418b18:
        and ecx,1
    L_00418b1b:
        xor edx,ecx
    L_00418b1d:
        mov dword ptr [eax+60h],edx
    L_00418b20:
        ret
    }
}
