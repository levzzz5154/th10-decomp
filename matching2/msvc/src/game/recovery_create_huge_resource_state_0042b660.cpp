#include <string.h>

#include "asm_encoding.hpp"
// BLOCKED (D3903): closest_byte_count=23/71; first_diff=0x0042B668;
// residual_class=private EBX receiver for ResetAndPublish, EAX state/ESI
// return flow through RuntimeInitialize, and allocator/free helper ABI.
// variants_tested=MSVC 13.10 typed standalone candidate (65-byte extent,
// 23/71 same-position bytes) plus exact naked baseline; candidate was restored.
// next_lever=caller-inclusive schema2 native-LTCG cluster over 0x0042B660,
// 0x0042B430, 0x0042B4D0, 0x0042B570 with EBX/EAX register topology.
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0042B660..0x0042B6A6: Recovery_CreateHugeResourceState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_CreateHugeResourceState_0042b660() {
    __asm {
    L_0042b660:
        push esi
    L_0042b661:
        push 0B884h
    L_0042b666:
        call asm_operator_new_00452493
    L_0042b66b:
        add esp,4
    L_0042b66e:
        test eax,eax
    L_0042b670:
        je short L_0042b67f
    L_0042b672:
        push ebx
    L_0042b673:
        mov ebx,eax
    L_0042b675:
        call asm_EffectManager_ResetAndPublishRetail_0042b430
    L_0042b67a:
        mov esi,eax
    L_0042b67c:
        pop ebx
    L_0042b67d:
        jmp short L_0042b681
    L_0042b67f:
        xor esi,esi
    L_0042b681:
        mov eax,esi
    L_0042b683:
        call asm_EffectManagerRuntime_InitializeRetail_0042b4d0
    L_0042b688:
        test eax,eax
    L_0042b68a:
        je short L_0042b6a3
    L_0042b68c:
        test esi,esi
    L_0042b68e:
        je short L_0042b69f
    L_0042b690:
        push esi
    L_0042b691:
        call asm_FUN_0042b570_0042b570
    L_0042b696:
        push esi
    L_0042b697:
        call asm_free_004524a1
    L_0042b69c:
        add esp,4
    L_0042b69f:
        xor eax,eax
    L_0042b6a1:
        pop esi
    L_0042b6a2:
        ret
    L_0042b6a3:
        mov eax,esi
    L_0042b6a5:
        pop esi
    L_0042b6a6:
        ret
    }
}
