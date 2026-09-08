#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420D50..0x00420D84: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00420d50() {
    __asm {
    L_00420d50:
        mov eax,dword ptr [edi+754h]
    L_00420d56:
        test eax,eax
    L_00420d58:
        je short L_00420d82
    L_00420d5a:
        push esi
    L_00420d5b:
        mov esi,dword ptr [data_00491c10]
    L_00420d61:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00420d66:
        mov eax,dword ptr [edi+8]
    L_00420d69:
        push 0
    L_00420d6b:
        push 0Eh
    L_00420d6d:
        mov dword ptr [edi+754h],0
    L_00420d77:
        mov ecx,dword ptr [eax]
    L_00420d79:
        push eax
    L_00420d7a:
        call dword ptr [ecx+0E4h]
    L_00420d80:
        pop esi
    L_00420d81:
        ret
    L_00420d82:
        xor eax,eax
    L_00420d84:
        ret
    }
}
