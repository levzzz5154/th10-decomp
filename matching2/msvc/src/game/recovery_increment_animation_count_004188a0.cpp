#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x004188A0..0x0041892C: Recovery_IncrementAnimationCount
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_IncrementAnimationCount_004188a0() {
    __asm {
    L_004188a0:
        push ecx
    L_004188a1:
        push esi
    L_004188a2:
        mov esi,dword ptr [eax+30h]
    L_004188a5:
        add esi,ecx
    L_004188a7:
        mov ecx,esi
    L_004188a9:
        cmp ecx,9
    L_004188ac:
        mov dword ptr [eax+30h],esi
    L_004188af:
        jle short L_004188cb
    L_004188b1:
        mov dword ptr [eax+30h],9
    L_004188b8:
        mov ecx,dword ptr [data_00474c70]
    L_004188be:
        mov eax,dword ptr [data_0047770c]
    L_004188c3:
        call asm_Animation_SetActiveCount_00413790
    L_004188c8:
        pop esi
    L_004188c9:
        pop ecx
    L_004188ca:
        ret
    L_004188cb:
        push edi
    L_004188cc:
        push 0
    L_004188ce:
        mov edi,2Ch
    L_004188d3:
        mov ecx,492590h
    L_004188d8:
        call asm_AnimationManager_QueueResource_0043dc90
    L_004188dd:
        mov edi,dword ptr [data_0047770c]
    L_004188e3:
        mov edx,dword ptr [edi+9E18h]
    L_004188e9:
        lea esi,[edi+9E18h]
    L_004188ef:
        push edx
    L_004188f0:
        mov edx,dword ptr [data_00491c10]
    L_004188f6:
        call asm_AnimationManager_SetFlag_004492a0
    L_004188fb:
        push 0Fh
    L_004188fd:
        mov dword ptr [esi],0
    L_00418903:
        mov eax,dword ptr [edi+9EC8h]
    L_00418909:
        push 4Bh
    L_0041890b:
        push eax
    L_0041890c:
        lea edi,[esp+14h]
    L_00418910:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00418915:
        mov ecx,dword ptr [eax]
    L_00418917:
        mov eax,dword ptr [data_0047770c]
    L_0041891c:
        mov dword ptr [esi],ecx
    L_0041891e:
        mov ecx,dword ptr [data_00474c70]
    L_00418924:
        pop edi
    L_00418925:
        call asm_Animation_SetActiveCount_00413790
    L_0041892a:
        pop esi
    L_0041892b:
        pop ecx
    L_0041892c:
        ret
    }
}
