#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C800..0x0040C80E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c800() {
    __asm {
    L_0040c800:
        xor ecx,ecx
    L_0040c802:
        mov dword ptr [eax+1008h],ecx
    L_0040c808:
        mov dword ptr [eax+100Ch],ecx
    L_0040c80e:
        ret
    }
}
