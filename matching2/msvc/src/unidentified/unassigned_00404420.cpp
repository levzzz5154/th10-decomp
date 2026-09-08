#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404420..0x0040444E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00404420() {
    __asm {
    L_00404420:
        mov eax,dword ptr [esi+2A38h]
    L_00404426:
        push edi
    L_00404427:
        mov edi,dword ptr [data_00491c10]
    L_0040442d:
        push eax
    L_0040442e:
        mov edx,edi
    L_00404430:
        mov dword ptr [esi+1EE4h],0
    L_0040443a:
        call asm_AnimationManager_SetFlag_004492a0
    L_0040443f:
        mov ecx,dword ptr [esi+2A3Ch]
    L_00404445:
        push ecx
    L_00404446:
        mov edx,edi
    L_00404448:
        call asm_AnimationManager_SetFlag_004492a0
    L_0040444d:
        pop edi
    L_0040444e:
        ret
    }
}
