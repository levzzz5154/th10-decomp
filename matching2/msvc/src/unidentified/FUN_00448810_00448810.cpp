#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448810..0x00448857: FUN_00448810
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448810_00448810() {
    __asm {
    L_00448810:
        push esi
    L_00448811:
        push edi
    L_00448812:
        mov edi,491E94h
    L_00448817:
        mov esi,ecx
    L_00448819:
        mov dword ptr [data_00491fac],edi
    L_0044881f:
        call asm_Camera_ApplyRetail_00421480
    L_00448824:
        mov edx,dword ptr [data_00491fac]
    L_0044882a:
        mov eax,dword ptr [data_00491c30]
    L_0044882f:
        mov ecx,dword ptr [eax]
    L_00448831:
        add edx,0CCh
    L_00448837:
        push edx
    L_00448838:
        push eax
    L_00448839:
        call dword ptr [ecx+0BCh]
    L_0044883f:
        mov eax,13h
    L_00448844:
        mov edi,esi
    L_00448846:
        mov dword ptr [data_00491fb0],1
    L_00448850:
        call asm_AnimationManager_RenderBucket_00448980
    L_00448855:
        pop edi
    L_00448856:
        pop esi
    L_00448857:
        ret
    }
}
