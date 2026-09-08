#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420D10..0x00420D43: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00420d10() {
    __asm {
    L_00420d10:
        cmp dword ptr [edi+754h],1
    L_00420d17:
        je short L_00420d41
    L_00420d19:
        push esi
    L_00420d1a:
        mov esi,dword ptr [data_00491c10]
    L_00420d20:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00420d25:
        mov eax,dword ptr [edi+8]
    L_00420d28:
        push 1
    L_00420d2a:
        push 0Eh
    L_00420d2c:
        mov dword ptr [edi+754h],1
    L_00420d36:
        mov ecx,dword ptr [eax]
    L_00420d38:
        push eax
    L_00420d39:
        call dword ptr [ecx+0E4h]
    L_00420d3f:
        pop esi
    L_00420d40:
        ret
    L_00420d41:
        xor eax,eax
    L_00420d43:
        ret
    }
}
