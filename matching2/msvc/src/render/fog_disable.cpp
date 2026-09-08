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
