#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424440..0x00424450: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00424440() {
    __asm {
    L_00424440:
        mov ecx,dword ptr [eax+4]
    L_00424443:
        push esi
    L_00424444:
        mov esi,dword ptr [eax]
    L_00424446:
        xor edx,edx
    L_00424448:
        cmp ecx,esi
    L_0042444a:
        setne dl
    L_0042444d:
        pop esi
    L_0042444e:
        mov eax,edx
    L_00424450:
        ret
    }
}
