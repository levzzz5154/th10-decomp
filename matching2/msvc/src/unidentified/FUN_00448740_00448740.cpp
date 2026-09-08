#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448740..0x0044876F: FUN_00448740
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448740_00448740() {
    __asm {
    L_00448740:
        mov eax,dword ptr [data_00491c10]
    L_00448745:
        xor edx,edx
    L_00448747:
        mov dword ptr [data_00491e64],0
    L_00448751:
        mov dword ptr [data_00491e68],0
    L_0044875b:
        push edi
    L_0044875c:
        mov dword ptr [eax+5Ch],edx
    L_0044875f:
        mov dword ptr [eax+60h],edx
    L_00448762:
        mov eax,0Eh
    L_00448767:
        mov edi,ecx
    L_00448769:
        call asm_AnimationManager_RenderBucket_00448980
    L_0044876e:
        pop edi
    L_0044876f:
        ret
    }
}
