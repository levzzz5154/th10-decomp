#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00427AE0..0x00427B42: ?Recovery_SwitchPlaybackState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_SwitchPlaybackState_00427ae0() {
    __asm {
    L_00427ae0:
        mov eax,dword ptr [data_00477834]
    L_00427ae5:
        push ebx
    L_00427ae6:
        mov ebx,dword ptr [eax+4474h]
    L_00427aec:
        test ebx,ebx
    L_00427aee:
        mov eax,dword ptr [edi+84h]
    L_00427af4:
        push esi
    L_00427af5:
        jne short L_00427b1d
    L_00427af7:
        test eax,eax
    L_00427af9:
        je short L_00427b08
    L_00427afb:
        lea eax,[edi+68h]
    L_00427afe:
        mov esi,6
    L_00427b03:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00427b08:
        mov ecx,dword ptr [edi+3Ch]
    L_00427b0b:
        mov dword ptr [edi+4Ch],ecx
    L_00427b0e:
        mov edx,dword ptr [edi+40h]
    L_00427b11:
        mov dword ptr [edi+50h],edx
    L_00427b14:
        pop esi
    L_00427b15:
        mov dword ptr [edi+84h],ebx
    L_00427b1b:
        pop ebx
    L_00427b1c:
        ret
    L_00427b1d:
        test eax,eax
    L_00427b1f:
        jne short L_00427b2e
    L_00427b21:
        lea eax,[edi+68h]
    L_00427b24:
        mov esi,3
    L_00427b29:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00427b2e:
        mov eax,dword ptr [edi+4Ch]
    L_00427b31:
        mov dword ptr [edi+34h],eax
    L_00427b34:
        mov ecx,dword ptr [edi+50h]
    L_00427b37:
        mov dword ptr [edi+38h],ecx
    L_00427b3a:
        pop esi
    L_00427b3b:
        mov dword ptr [edi+84h],ebx
    L_00427b41:
        pop ebx
    L_00427b42:
        ret
    }
}
