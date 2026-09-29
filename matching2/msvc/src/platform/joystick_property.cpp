// This is DirectSound primary-buffer format setup, not a joystick property.
// Tested candidate: reference/semantic_candidates/sound_primary_format.cpp.
// 436 comparisons pass; see recovery_notes/sound_primary_format_0044c7e0.md.
// The register-role guesses in the historical blocker below are superseded.
// BLOCKED (D3703): closest_byte_count=0/260; first_diff=unmeasured;
// residual_class=production-valid native-LTCG ownership is unavailable because
// the exclusive region remains kind=asm in regions.json; the readable
// joystick property body needs the real ESI receiver plus BX/EDI register
// inputs, COM interface vtable layout, and security-cookie frame.
// variants_tested=live Ghidra decompile at 0x0044C7E0 and existing joystick
// native-LTCG receiver cluster at 0x0044C770/0x0044C790; no target body was
// retained because its required production cluster would overlap the existing
// 0x0044C7E0 context address.
// next_lever=promote 0x0044C7E0 to a semantic cluster-owned region and
// co-compile the real sound-device caller with the property owner and COM
// callees; do not alter regions.json in this assignment.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C7E0..0x0044C8E3: Input_SetJoystickPropertyRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Input_SetJoystickPropertyRetail_0044c7e0() {
    __asm {
    L_0044c7e0:
        sub esp,40h
    L_0044c7e3:
        mov eax,dword ptr [data_00473660]
    L_0044c7e8:
        xor eax,esp
    L_0044c7ea:
        mov dword ptr [esp+3Ch],eax
    L_0044c7ee:
        mov eax,dword ptr [esp+44h]
    L_0044c7f2:
        mov eax,dword ptr [eax]
    L_0044c7f4:
        test eax,eax
    L_0044c7f6:
        push esi
    L_0044c7f7:
        mov esi,ecx
    L_0044c7f9:
        mov dword ptr [esp+4],0
    L_0044c801:
        jne short L_0044c81a
    L_0044c803:
        mov eax,800401F0h
    L_0044c808:
        pop esi
    L_0044c809:
        mov ecx,dword ptr [esp+3Ch]
    L_0044c80d:
        xor ecx,esp
    L_0044c80f:
        call asm_security_check_cookie_00458ea5
    L_0044c814:
        add esp,40h
    L_0044c817:
        ret 4
    L_0044c81a:
        xor ecx,ecx
    L_0044c81c:
        mov dword ptr [esp+1Ch],ecx
    L_0044c820:
        mov dword ptr [esp+20h],ecx
    L_0044c824:
        mov dword ptr [esp+24h],ecx
    L_0044c828:
        mov dword ptr [esp+28h],ecx
    L_0044c82c:
        mov dword ptr [esp+2Ch],ecx
    L_0044c830:
        mov dword ptr [esp+30h],ecx
    L_0044c834:
        mov dword ptr [esp+34h],ecx
    L_0044c838:
        mov dword ptr [esp+38h],ecx
    L_0044c83c:
        push ecx
    L_0044c83d:
        mov dword ptr [esp+40h],ecx
    L_0044c841:
        mov dword ptr [esp+28h],ecx
    L_0044c845:
        mov dword ptr [esp+30h],ecx
    L_0044c849:
        lea ecx,[esp+8]
    L_0044c84d:
        push ecx
    L_0044c84e:
        lea ecx,[esp+24h]
    L_0044c852:
        push ecx
    L_0044c853:
        mov dword ptr [esp+28h],24h
    L_0044c85b:
        mov dword ptr [esp+2Ch],1
    L_0044c863:
        mov edx,dword ptr [eax]
    L_0044c865:
        push eax
    L_0044c866:
        call dword ptr [edx+0Ch]
    L_0044c869:
        test eax,eax
    L_0044c86b:
        jl short L_0044c8d2
    L_0044c86d:
        xor edx,edx
    L_0044c86f:
        mov dword ptr [esp+8],edx
    L_0044c873:
        mov dword ptr [esp+0Ch],edx
    L_0044c877:
        mov dword ptr [esp+10h],edx
    L_0044c87b:
        mov dword ptr [esp+14h],edx
    L_0044c87f:
        mov word ptr [esp+16h],si
    L_0044c884:
        shr si,3
    L_0044c888:
        mov word ptr [esp+18h],dx
    L_0044c88d:
        lea edx,[esp+8]
    L_0044c891:
        push edx
    L_0044c892:
        mov word ptr [esp+0Ch],1
    L_0044c899:
        mov word ptr [esp+0Eh],bx
    L_0044c89e:
        mov dword ptr [esp+10h],edi
    L_0044c8a2:
        imul esi,ebx
    L_0044c8a5:
        movzx eax,si
    L_0044c8a8:
        imul eax,edi
    L_0044c8ab:
        mov dword ptr [esp+14h],eax
    L_0044c8af:
        mov eax,dword ptr [esp+8]
    L_0044c8b3:
        mov word ptr [esp+18h],si
    L_0044c8b8:
        mov ecx,dword ptr [eax]
    L_0044c8ba:
        push eax
    L_0044c8bb:
        call dword ptr [ecx+38h]
    L_0044c8be:
        test eax,eax
    L_0044c8c0:
        jl short L_0044c8d2
    L_0044c8c2:
        mov eax,dword ptr [esp+4]
    L_0044c8c6:
        test eax,eax
    L_0044c8c8:
        je short L_0044c8d0
    L_0044c8ca:
        mov ecx,dword ptr [eax]
    L_0044c8cc:
        push eax
    L_0044c8cd:
        call dword ptr [ecx+8]
    L_0044c8d0:
        xor eax,eax
    L_0044c8d2:
        mov ecx,dword ptr [esp+40h]
    L_0044c8d6:
        pop esi
    L_0044c8d7:
        xor ecx,esp
    L_0044c8d9:
        call asm_security_check_cookie_00458ea5
    L_0044c8de:
        add esp,40h
    L_0044c8e1:
        ret 4
    }
}
