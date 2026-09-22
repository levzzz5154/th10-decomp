// BLOCKED (D3807): closest_byte_count=4/121; first_diff=0x00414570;
// residual_class=private EBX state receiver, ESI-preserved animation-slot
// helper ABI, the game-state manager +0x3AD0DC side slot, and helper-specific
// free-call cleanup. Live Ghidra decompilation confirms the branch and slot
// topology; the readable raw-layout candidate compiled to 107 bytes and only
// four comparable bytes, so it was restored.
// variants_tested=live Ghidra decompile at 0x00414570 and caller
// 0x00417EED; archived Recovery_ReleaseCompositeState raw-layout model;
// standalone MSVC 13.10 __fastcall candidate (107-byte extent, 4/121).
// next_lever=caller-inclusive schema-2 native-LTCG cluster over real callers
// 0x00414370/0x00417EED, this body, AnimationSlot_ReleaseRetail_004136C0,
// FUN_00447810, and the production manager/entity layouts; preserve EBX/ESI
// private flow and promote only after all 121 bytes are exact.

#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00414570..0x004145E8: Recovery_ReleaseCompositeState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ReleaseCompositeState_00414570() {
    __asm {
    L_00414570:
        push ebp
    L_00414571:
        push esi
    L_00414572:
        mov esi,dword ptr [ebx+9EB8h]
    L_00414578:
        xor ebp,ebp
    L_0041457a:
        cmp esi,ebp
    L_0041457c:
        je short L_00414592
    L_0041457e:
        call asm_AnimationSlot_ReleaseRetail_004136c0
    L_00414583:
        push esi
    L_00414584:
        call asm_free_004524a1
    L_00414589:
        add esp,4
    L_0041458c:
        mov dword ptr [ebx+9EB8h],ebp
    L_00414592:
        test byte ptr [data_00474ca0],9
    L_00414599:
        jne short L_004145e6
    L_0041459b:
        mov esi,dword ptr [data_00491c10]
    L_004145a1:
        add esi,3AD0DCh
    L_004145a7:
        push edi
    L_004145a8:
        mov edi,dword ptr [esi]
    L_004145aa:
        cmp edi,ebp
    L_004145ac:
        je short L_004145c0
    L_004145ae:
        call asm_FUN_00447810_00447810
    L_004145b3:
        mov eax,dword ptr [esi]
    L_004145b5:
        push eax
    L_004145b6:
        call asm_free_004524a1
    L_004145bb:
        add esp,4
    L_004145be:
        mov dword ptr [esi],ebp
    L_004145c0:
        mov eax,dword ptr [ebx+9EBCh]
    L_004145c6:
        cmp eax,ebp
    L_004145c8:
        mov dword ptr [ebx+9E80h],ebp
    L_004145ce:
        pop edi
    L_004145cf:
        je short L_004145e0
    L_004145d1:
        push eax
    L_004145d2:
        call asm_free_00452422
    L_004145d7:
        add esp,4
    L_004145da:
        mov dword ptr [ebx+9EBCh],ebp
    L_004145e0:
        mov dword ptr [ebx+9EBCh],ebp
    L_004145e6:
        pop esi
    L_004145e7:
        pop ebp
    L_004145e8:
        ret
    }
}
