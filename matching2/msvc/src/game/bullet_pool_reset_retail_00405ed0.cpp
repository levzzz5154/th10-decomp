#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402720..0x0040284F: FUN_00402720
// Naked body preserves the retail register/stack ABI.

// 0x00405ED0..0x00405EFC: BulletPool_ResetRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_BulletPool_ResetRetail_00405ed0() {
    __asm {
    L_00405ed0:
        mov edx,dword ptr [esi+3E0B50h]
    L_00405ed6:
        mov eax,dword ptr [data_00491c10]
    L_00405edb:
        push edi
    L_00405edc:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_00405ee1:
        lea edx,[esi+60h]
    L_00405ee4:
        mov ecx,0F82BCh
    L_00405ee9:
        xor eax,eax
    L_00405eeb:
        mov edi,edx
    L_00405eed:
        rep stosd
    L_00405eef:
        mov dword ptr [esi+10h],edx
    L_00405ef2:
        mov word ptr [esi+3E07A6h],5
    L_00405efb:
        pop edi
    L_00405efc:
        ret
    }
}
