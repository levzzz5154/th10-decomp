#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x004243F0..0x00424430: Recovery_MarkAnimationTree
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_MarkAnimationTree_004243f0() {
    __asm {
    L_004243f0:
        mov eax,dword ptr [eax]
    L_004243f2:
        mov edx,dword ptr [data_00491c10]
    L_004243f8:
        push eax
    L_004243f9:
        call asm_AnimationManager_Find_004491c0
    L_004243fe:
        test eax,eax
    L_00424400:
        je short L_00424430
    L_00424402:
        mov edx,dword ptr [eax+18h]
    L_00424405:
        test edx,edx
    L_00424407:
        mov ecx,6
    L_0042440c:
        mov word ptr [eax+304h],cx
    L_00424413:
        jne short L_00424430
    L_00424415:
        mov eax,dword ptr [eax+14h]
    L_00424418:
        test eax,eax
    L_0042441a:
        je short L_00424430
    L_0042441c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00424420:
        mov edx,dword ptr [eax]
    L_00424422:
        mov word ptr [edx+304h],cx
    L_00424429:
        mov eax,dword ptr [eax+4]
    L_0042442c:
        test eax,eax
    L_0042442e:
        jne short L_00424420
    L_00424430:
        ret
    }
}
