#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420D90..0x00420DB0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00420d90() {
    __asm {
    L_00420d90:
        push esi
    L_00420d91:
        mov esi,dword ptr [data_00491c10]
    L_00420d97:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00420d9c:
        mov eax,dword ptr [esp+8]
    L_00420da0:
        mov eax,dword ptr [eax+8]
    L_00420da3:
        mov ecx,dword ptr [eax]
    L_00420da5:
        pop esi
    L_00420da6:
        mov dword ptr [esp+4],eax
    L_00420daa:
        jmp dword ptr [ecx+0E4h]
    L_00420db0:
        ret
    }
}
