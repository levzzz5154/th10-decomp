#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/score.hpp"

// 0x004091C0..0x004091D7: ?ReleaseFlaggedEntityArrays@ScoreRuntimeState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ReleaseFlaggedEntityArrays_ScoreRuntimeState_004091c0() {
    __asm {
    L_004091c0:
        test byte ptr [ebx+378Ch],1
    L_004091c7:
        TH10_REL8(0x74, 0x004091c7, VA_asm_target_00409219)
    L_004091c9:
        push esi
    L_004091ca:
        push edi
    L_004091cb:
        lea esi,[ebx+778h]
    L_004091d1:
        mov edi,8
    L_004091d6:
        TH10_REL8(0xeb, 0x004091d6, VA_asm_ReleaseFlaggedEntityArrays_ScoreRuntimeState_part_004091e0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_004091e0:
        mov ecx,dword ptr [data_00491c10]
    L_004091e6:
        mov eax,esi
    L_004091e8:
        call asm_FUN_004451c0_004451c0
    L_004091ed:
        add esi,3ACh
    L_004091f3:
        dec edi
    L_004091f4:
        jne short L_004091e0
    L_004091f6:
        lea esi,[ebx+24D8h]
    L_004091fc:
        mov edi,5
    L_00409201:
        mov ecx,dword ptr [data_00491c10]
    L_00409207:
        mov eax,esi
    L_00409209:
        call asm_FUN_004451c0_004451c0
    L_0040920e:
        add esi,3ACh
    L_00409214:
        dec edi
    L_00409215:
        jne short L_00409201
    L_00409217:
        pop edi
    L_00409218:
        pop esi
    L_00409219:
        mov eax,1
    L_0040921e:
        ret
    }
}
