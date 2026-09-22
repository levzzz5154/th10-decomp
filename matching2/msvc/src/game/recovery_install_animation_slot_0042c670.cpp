#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// BLOCKED (D2802): closest_byte_count=67/95; first_diff=0x0042C670;
// residual_class=private-EDI-index/hidden-global+callee ABI: the readable
// install model omitted the retail hidden global load and used ordinary
// argument/callee conventions, changing the final indexed store schedule.
// variants_tested=typed stdcall install model and exact retail overlay;
// next_lever=resolve private EDI index delivery and the 0x00449950,
// 0x00449870, and 0x004489D0 callee contracts in a native caller context.
// 0x0042C670..0x0042C6CE: ?Recovery_InstallAnimationSlot@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InstallAnimationSlot_0042c670() {
    __asm {
    L_0042c670:
        push ebx
    L_0042c671:
        push ebp
    L_0042c672:
        mov ebp,dword ptr [esp+0Ch]
    L_0042c676:
        mov eax,dword ptr [ebp+14h]
    L_0042c679:
        push esi
    L_0042c67a:
        mov esi,dword ptr [data_00491c10]
    L_0042c680:
        mov dword ptr [esp+10h],eax
    L_0042c684:
        call asm_FUN_00449950_00449950
    L_0042c689:
        mov ecx,dword ptr [esp+10h]
    L_0042c68d:
        mov ebx,eax
    L_0042c68f:
        mov edx,dword ptr [ebx+35Ch]
    L_0042c695:
        push edi
    L_0042c696:
        or edx,40000000h
    L_0042c69c:
        push ebx
    L_0042c69d:
        mov dword ptr [ebx+20h],0Fh
    L_0042c6a4:
        mov dword ptr [ebx+35Ch],edx
    L_0042c6aa:
        call asm_FUN_00449870_00449870
    L_0042c6af:
        mov edx,dword ptr [data_00491c10]
    L_0042c6b5:
        lea eax,[esp+10h]
    L_0042c6b9:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0042c6be:
        mov ecx,dword ptr [esp+10h]
    L_0042c6c2:
        pop esi
    L_0042c6c3:
        mov dword ptr [ebp+edi*4+2C4h],ecx
    L_0042c6ca:
        pop ebp
    L_0042c6cb:
        pop ebx
    L_0042c6cc:
        ret 4
    }
}
