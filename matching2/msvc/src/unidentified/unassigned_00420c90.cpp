#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420C90..0x00420CC3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00420c90() {
    __asm {
    L_00420c90:
        cmp dword ptr [edi+750h],1
    L_00420c97:
        je short L_00420cc1
    L_00420c99:
        push esi
    L_00420c9a:
        mov esi,dword ptr [data_00491c10]
    L_00420ca0:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00420ca5:
        mov eax,dword ptr [edi+8]
    L_00420ca8:
        push 1
    L_00420caa:
        push 1Ch
    L_00420cac:
        mov dword ptr [edi+750h],1
    L_00420cb6:
        mov ecx,dword ptr [eax]
    L_00420cb8:
        push eax
    L_00420cb9:
        call dword ptr [ecx+0E4h]
    L_00420cbf:
        pop esi
    L_00420cc0:
        ret
    L_00420cc1:
        xor eax,eax
    L_00420cc3:
        ret
    }
}
