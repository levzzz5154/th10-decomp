#include "../../../include/asm_encoding.hpp"
#include "../../../include/asm_symbols.hpp"

// Caller-inclusive native LTCG now reproduces 265/287 bytes, with the first
// difference at 0x0043E8B1. The complete 287-byte candidate has the right
// object=EAX, resource=EDX, index=ECX entry and real stack-object VM call.
// Its script/index homes are EDI/ESI instead of retail ESI/EDI. Paired script
// fields and slot references restore the retail mask/clock store schedule.
// The real 36-byte handle caller is recovered in ordinary C++ separately.
// Its native scope sees this candidate as an unselected semantic ABI anchor;
// this assembly region remains the genuine callee until all 287 bytes match.
// Next lever: scalar lifetime/flag-helper pressure that retains EBP while
// allocating the script to ESI and index/temporary flags to EDI.
// See reference/recovery_notes/animation_object_change_script_0043e8b0.md.

// 0x0043E8B0..0x0043E9CE: ?AnimationObject_ChangeScript@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationObject_ChangeScript_0043e8b0() {
    __asm {
    L_0043e8b0:
        push esi
    L_0043e8b1:
        push edi
    L_0043e8b2:
        mov edi,ecx
    L_0043e8b4:
        mov ecx,dword ptr [edx+11Ch]
    L_0043e8ba:
        mov esi,dword ptr [ecx+edi*4]
    L_0043e8bd:
        xor ecx,ecx
    L_0043e8bf:
        cmp esi,ecx
    L_0043e8c1:
        je asm_target_0043e9cc
    L_0043e8c7:
        push ebp
    L_0043e8c8:
        cmp dword ptr [edx+124h],ecx
    L_0043e8ce:
        jne asm_target_0043e9cb
    L_0043e8d4:
        mov word ptr [eax+38Ah],di
    L_0043e8db:
        mov edi,dword ptr [eax+35Ch]
    L_0043e8e1:
        test edi,200h
    L_0043e8e7:
        mov dword ptr [eax+308h],edx
    L_0043e8ed:
        je short L_0043e90a
    L_0043e8ef:
        fld dword ptr [eax+3Ch]
    L_0043e8f2:
        or edi,8
    L_0043e8f5:
        fmul dword ptr [data_00470b60]
    L_0043e8fb:
        xor edi,200h
    L_0043e901:
        mov dword ptr [eax+35Ch],edi
    L_0043e907:
        fstp dword ptr [eax+3Ch]
    L_0043e90a:
        mov word ptr [eax+35Ch],7
    L_0043e913:
        mov dword ptr [eax+2FCh],0FFFFFFFFh
    L_0043e91d:
        mov dword ptr [eax+60h],ecx
    L_0043e920:
        mov dword ptr [eax+64h],ecx
    L_0043e923:
        mov edi,0FFF0BDC1h
    L_0043e928:
        mov dword ptr [eax+5Ch],edi
    L_0043e92b:
        mov dword ptr [eax+0B4h],ecx
    L_0043e931:
        mov dword ptr [eax+100h],ecx
    L_0043e937:
        mov dword ptr [eax+12Ch],ecx
    L_0043e93d:
        mov dword ptr [eax+178h],ecx
    L_0043e943:
        mov dword ptr [eax+1B4h],ecx
    L_0043e949:
        mov dword ptr [eax+200h],ecx
    L_0043e94f:
        mov dword ptr [eax+22Ch],ecx
    L_0043e955:
        mov bp,word ptr [edx]
    L_0043e958:
        mov word ptr [eax+386h],bp
    L_0043e95f:
        mov ebp,dword ptr [eax+35Ch]
    L_0043e965:
        and ebp,0FFFFF9FFh
    L_0043e96b:
        mov dword ptr [eax+308h],edx
    L_0043e971:
        mov dword ptr [eax+35Ch],ebp
    L_0043e977:
        mov dword ptr [eax+38Ch],esi
    L_0043e97d:
        mov dword ptr [eax+390h],esi
    L_0043e983:
        mov edx,dword ptr [eax+6Ch]
    L_0043e986:
        test dl,1
    L_0043e989:
        jne short L_0043e9a1
    L_0043e98b:
        or edx,1
    L_0043e98e:
        mov dword ptr [eax+60h],ecx
    L_0043e991:
        mov dword ptr [eax+5Ch],edi
    L_0043e994:
        mov dword ptr [eax+64h],ecx
    L_0043e997:
        mov dword ptr [eax+68h],476F78h
    L_0043e99e:
        mov dword ptr [eax+6Ch],edx
    L_0043e9a1:
        mov dword ptr [eax+60h],ecx
    L_0043e9a4:
        mov dword ptr [eax+64h],ecx
    L_0043e9a7:
        mov dword ptr [eax+5Ch],0FFFFFFFFh
    L_0043e9ae:
        mov esi,dword ptr [eax+35Ch]
    L_0043e9b4:
        and esi,0FFFFFFFEh
    L_0043e9b7:
        push eax
    L_0043e9b8:
        mov dword ptr [eax+35Ch],esi
    L_0043e9be:
        call asm_FUN_0043ee30_0043ee30
    L_0043e9c3:
        mov eax,dword ptr [g_sprt_ctrl]
    L_0043e9c8:
        inc dword ptr [eax+4Ch]
    L_0043e9cb:
        pop ebp
    L_0043e9cc:
        pop edi
    L_0043e9cd:
        pop esi
    L_0043e9ce:
        ret
    }
}
