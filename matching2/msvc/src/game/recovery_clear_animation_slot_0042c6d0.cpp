#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0042C6D0..0x0042C722: ?Recovery_ClearAnimationSlot@@
// BLOCKED: closest_byte_count=61/83, first_diff=0x0042C6E4,
// residual_class=private_abi_register_allocation_and_shrink_wrap_tail_merge,
// variants_tested=9_successful_LTCG_schema1_private_member_candidates,
// next_lever=derive_original_EC_zero_and_duplicate_store_source_shape_without_new_flags
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ClearAnimationSlot_0042c6d0() {
    __asm {
    L_0042c6d0:
        mov eax,dword ptr [edi+esi*4+2C4h]
    L_0042c6d7:
        mov edx,dword ptr [data_00491c10]
    L_0042c6dd:
        push eax
    L_0042c6de:
        call asm_AnimationManager_Find_004491c0
    L_0042c6e3:
        xor ecx,ecx
    L_0042c6e5:
        cmp eax,ecx
    L_0042c6e7:
        je short L_0042c71b
    L_0042c6e9:
        push ebx
    L_0042c6ea:
        cmp dword ptr [eax+18h],ecx
    L_0042c6ed:
        mov edx,1
    L_0042c6f2:
        mov word ptr [eax+304h],dx
    L_0042c6f9:
        jne short L_0042c712
    L_0042c6fb:
        mov eax,dword ptr [eax+14h]
    L_0042c6fe:
        cmp eax,ecx
    L_0042c700:
        je short L_0042c712
    L_0042c702:
        mov ebx,dword ptr [eax]
    L_0042c704:
        mov word ptr [ebx+304h],dx
    L_0042c70b:
        mov eax,dword ptr [eax+4]
    L_0042c70e:
        cmp eax,ecx
    L_0042c710:
        jne short L_0042c702
    L_0042c712:
        mov dword ptr [edi+esi*4+2C4h],ecx
    L_0042c719:
        pop ebx
    L_0042c71a:
        ret
    L_0042c71b:
        mov dword ptr [edi+esi*4+2C4h],ecx
    L_0042c722:
        ret
    }
}
