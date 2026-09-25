// BLOCKED (D3703): closest_byte_count=15/53; first_diff=0x00420CD1;
// residual_class=native-LTCG selected ESI for the state receiver in the
// isolated typed probe (51-byte body), while retail requires EDI and the
// production RenderStageState/AnimationManager caller pressure that controls
// branch layout and helper sequencing.
// variants_tested=live Ghidra decompile at 0x00420CD0; existing native-LTCG
// render cluster fog anchor; isolated MSVC 13.10 typed fog-state probe with
// data_00491C10 and the 0x00442F50 Flush binding; unchanged production
// manifest validation.
// next_lever=co-compile the real 0x00439390 frame caller, RenderStageState
// body, and AnimationManager::Flush under schema-2 native-LTCG, then promote
// this region to semantic ownership; do not alter regions.json in this
// assignment.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420CD0..0x00420D04: FUN_00420cd0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00420cd0_00420cd0() {
    __asm {
    L_00420cd0:
        mov eax,dword ptr [edi+750h]
    L_00420cd6:
        test eax,eax
    L_00420cd8:
        je short L_00420d02
    L_00420cda:
        push esi
    L_00420cdb:
        mov esi,dword ptr [data_00491c10]
    L_00420ce1:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00420ce6:
        mov eax,dword ptr [edi+8]
    L_00420ce9:
        push 0
    L_00420ceb:
        push 1Ch
    L_00420ced:
        mov dword ptr [edi+750h],0
    L_00420cf7:
        mov ecx,dword ptr [eax]
    L_00420cf9:
        push eax
    L_00420cfa:
        call dword ptr [ecx+0E4h]
    L_00420d00:
        pop esi
    L_00420d01:
        ret
    L_00420d02:
        xor eax,eax
    L_00420d04:
        ret
    }
}
