#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405130..0x00405140: FUN_00405130
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405130_00405130() {
    __asm {
    L_00405130:
        mov edx,dword ptr [eax]
    L_00405132:
        mov dword ptr [ecx],edx
    L_00405134:
        mov edx,dword ptr [eax+4]
    L_00405137:
        mov dword ptr [ecx+4],edx
    L_0040513a:
        mov eax,dword ptr [eax+8]
    L_0040513d:
        mov dword ptr [ecx+8],eax
    L_00405140:
        ret
    }
}
