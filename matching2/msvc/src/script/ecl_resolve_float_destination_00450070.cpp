#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF70..0x0044E195: EclVm_StartChildRetail
// Naked body preserves the retail register/stack ABI.

// 0x00450070..0x004500CC: ?ECL_ResolveFloatDestination@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResolveFloatDestination_00450070() {
    __asm {
    L_00450070:
        push esi
    L_00450071:
        push edi
    L_00450072:
        mov esi,eax
    L_00450074:
        mov edx,dword ptr [esi+4]
    L_00450077:
        movzx eax,word ptr [edx+8]
    L_0045007b:
        mov edi,1
    L_00450080:
        shl edi,cl
    L_00450082:
        test eax,edi
    L_00450084:
        je short L_004500c8
    L_00450086:
        fld dword ptr [edx+ecx*4+10h]
    L_0045008a:
        fcomp dword ptr [data_00470b04]
    L_00450090:
        fld dword ptr [edx+ecx*4+10h]
    L_00450094:
        fnstsw ax
    L_00450096:
        test ah,1
    L_00450099:
        jne short L_004500b2
    L_0045009b:
        add esi,8
    L_0045009e:
        call asm_FUN_00463b2c_00463b2c
    L_004500a3:
        mov ecx,eax
    L_004500a5:
        mov eax,dword ptr [esi+1004h]
    L_004500ab:
        add eax,ecx
    L_004500ad:
        pop edi
    L_004500ae:
        add eax,esi
    L_004500b0:
        pop esi
    L_004500b1:
        ret
    L_004500b2:
        mov esi,dword ptr [esi+1014h]
    L_004500b8:
        mov edi,dword ptr [esi]
    L_004500ba:
        call asm_FUN_00463b2c_00463b2c
    L_004500bf:
        push eax
    L_004500c0:
        mov ecx,esi
    L_004500c2:
        call dword ptr [edi+10h]
    L_004500c5:
        pop edi
    L_004500c6:
        pop esi
    L_004500c7:
        ret
    L_004500c8:
        pop edi
    L_004500c9:
        xor eax,eax
    L_004500cb:
        pop esi
    L_004500cc:
        ret
    }
}
