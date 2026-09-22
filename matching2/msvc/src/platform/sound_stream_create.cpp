// BLOCKED (D3804): closest_byte_count=0/702; first_diff=0x0044C8F0;
// residual_class=private EAX/EDX/ECX/stack argument ABI, security-cookie/EH
// frame, ArchiveCursor_Open result ownership, COM vtable dispatch, and
// notification-buffer allocation sequencing. variants_tested=live Ghidra
// decompile for 0x0044C8F0 and real caller 0x0043D690, plus the readable
// segmented-stream model and callees 0x0044DBF0, 0x0044D6A0, operator_new,
// and release/query/set-notice slots; no standalone candidate was retained
// because its public ABI changed the frame, so the exact assembly baseline was
// restored. next_lever=schema2 native-LTCG cluster rooted at 0x0043D690 with
// this body, sound-thread caller, ArchiveCursor_Open, stream-record initializer,
// COM interface callees, and production stream layout co-compiled.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C8F0..0x0044CAC4: FUN_0044c8f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044c8f0_0044c8f0() {
    __asm {
    L_0044c8f0:
        push 0FFFFFFFFh
    L_0044c8f2:
        push 46533Bh
    L_0044c8f7:
        mov eax,dword ptr fs:[0]
    L_0044c8fd:
        push eax
    L_0044c8fe:
        mov dword ptr fs:[0],esp
    L_0044c905:
        sub esp,50h
    L_0044c908:
        mov eax,dword ptr [data_00473660]
    L_0044c90d:
        xor eax,esp
    L_0044c90f:
        push ebx
    L_0044c910:
        mov ebx,edx
    L_0044c912:
        mov edx,dword ptr [esp+6Ch]
    L_0044c916:
        mov dword ptr [esp+14h],ecx
    L_0044c91a:
        mov ecx,dword ptr [esp+70h]
    L_0044c91e:
        mov dword ptr [esp+40h],edx
    L_0044c922:
        mov edx,dword ptr [esp+74h]
    L_0044c926:
        mov dword ptr [esp+44h],ecx
    L_0044c92a:
        mov ecx,dword ptr [esp+78h]
    L_0044c92e:
        push ebp
    L_0044c92f:
        mov ebp,dword ptr [esp+80h]
    L_0044c936:
        mov dword ptr [esp+54h],eax
    L_0044c93a:
        mov eax,dword ptr [esp+68h]
    L_0044c93e:
        push esi
    L_0044c93f:
        mov esi,dword ptr [esp+90h]
    L_0044c946:
        mov dword ptr [esp+50h],edx
    L_0044c94a:
        mov edx,dword ptr [eax]
    L_0044c94c:
        mov dword ptr [esp+54h],ecx
    L_0044c950:
        xor ecx,ecx
    L_0044c952:
        cmp edx,ecx
    L_0044c954:
        push edi
    L_0044c955:
        mov edi,dword ptr [esp+74h]
    L_0044c959:
        mov dword ptr [esp+1Ch],eax
    L_0044c95d:
        jne short L_0044c969
    L_0044c95f:
        mov eax,800401F0h
    L_0044c964:
        jmp asm_target_0044cb8e
    L_0044c969:
        push 94h
    L_0044c96e:
        mov dword ptr [esp+1Ch],ecx
    L_0044c972:
        mov dword ptr [esp+14h],ecx
    L_0044c976:
        call asm_operator_new_00452493
    L_0044c97b:
        xor ecx,ecx
    L_0044c97d:
        add esp,4
    L_0044c980:
        cmp eax,ecx
    L_0044c982:
        je short L_0044c998
    L_0044c984:
        mov dword ptr [eax+90h],ecx
    L_0044c98a:
        mov dword ptr [eax],ecx
    L_0044c98c:
        mov dword ptr [eax+2Ch],ecx
    L_0044c98f:
        mov dword ptr [eax+7Ch],ecx
    L_0044c992:
        mov dword ptr [esp+14h],eax
    L_0044c996:
        jmp short L_0044c99c
    L_0044c998:
        mov dword ptr [esp+14h],ecx
    L_0044c99c:
        mov edx,esi
    L_0044c99e:
        mov esi,dword ptr [esp+14h]
    L_0044c9a2:
        mov eax,1
    L_0044c9a7:
        mov ecx,edi
    L_0044c9a9:
        call asm_ArchiveCursor_Open_0044dbf0
    L_0044c9ae:
        test eax,eax
    L_0044c9b0:
        je short L_0044c9ea
    L_0044c9b2:
        test esi,esi
    L_0044c9b4:
        je asm_target_0044cb12
    L_0044c9ba:
        cmp dword ptr [esi+78h],1
    L_0044c9be:
        jne short L_0044c9d7
    L_0044c9c0:
        mov edx,dword ptr [esi+8Ch]
    L_0044c9c6:
        push edx
    L_0044c9c7:
        call dword ptr [data_004660cc]
    L_0044c9cd:
        mov dword ptr [esi+8Ch],0FFFFFFFFh
    L_0044c9d7:
        push esi
    L_0044c9d8:
        call asm_free_004524a1
    L_0044c9dd:
        add esp,4
    L_0044c9e0:
        mov eax,80004005h
    L_0044c9e5:
        jmp asm_target_0044cb8e
    L_0044c9ea:
        mov esi,dword ptr [esp+8Ch]
    L_0044c9f1:
        mov ecx,dword ptr [esp+4Ch]
    L_0044c9f5:
        mov edx,dword ptr [esp+50h]
    L_0044c9f9:
        xor eax,eax
    L_0044c9fb:
        mov dword ptr [esp+28h],eax
    L_0044c9ff:
        mov dword ptr [esp+2Ch],eax
    L_0044ca03:
        mov dword ptr [esp+30h],eax
    L_0044ca07:
        mov dword ptr [esp+34h],eax
    L_0044ca0b:
        mov dword ptr [esp+38h],eax
    L_0044ca0f:
        mov dword ptr [esp+3Ch],eax
    L_0044ca13:
        mov dword ptr [esp+40h],eax
    L_0044ca17:
        mov edi,ebp
    L_0044ca19:
        mov dword ptr [esp+44h],eax
    L_0044ca1d:
        imul edi,esi
    L_0044ca20:
        mov dword ptr [esp+48h],eax
    L_0044ca24:
        mov eax,dword ptr [esp+54h]
    L_0044ca28:
        mov dword ptr [esp+3Ch],ecx
    L_0044ca2c:
        mov ecx,dword ptr [esp+58h]
    L_0044ca30:
        mov dword ptr [esp+40h],edx
    L_0044ca34:
        mov edx,dword ptr [esp+14h]
    L_0044ca38:
        mov dword ptr [esp+48h],ecx
    L_0044ca3c:
        mov ecx,dword ptr [esp+1Ch]
    L_0044ca40:
        mov dword ptr [esp+44h],eax
    L_0044ca44:
        mov dword ptr [esp+28h],24h
    L_0044ca4c:
        or ebx,18188h
    L_0044ca52:
        mov dword ptr [esp+2Ch],ebx
    L_0044ca56:
        mov dword ptr [esp+30h],edi
    L_0044ca5a:
        mov eax,dword ptr [edx+90h]
    L_0044ca60:
        add eax,20h
    L_0044ca63:
        mov dword ptr [esp+38h],eax
    L_0044ca67:
        mov eax,dword ptr [ecx]
    L_0044ca69:
        mov edx,dword ptr [eax]
    L_0044ca6b:
        push 0
    L_0044ca6d:
        lea ecx,[esp+1Ch]
    L_0044ca71:
        push ecx
    L_0044ca72:
        lea ecx,[esp+30h]
    L_0044ca76:
        push ecx
    L_0044ca77:
        push eax
    L_0044ca78:
        call dword ptr [edx+0Ch]
    L_0044ca7b:
        test eax,eax
    L_0044ca7d:
        jl asm_target_0044cb12
    L_0044ca83:
        mov eax,dword ptr [esp+18h]
    L_0044ca87:
        mov edx,dword ptr [eax]
    L_0044ca89:
        lea ecx,[esp+10h]
    L_0044ca8d:
        push ecx
    L_0044ca8e:
        push 46743Ch
    L_0044ca93:
        push eax
    L_0044ca94:
        call dword ptr [edx]
    L_0044ca96:
        test eax,eax
    L_0044ca98:
        TH10_REL8(0x7c, 0x0044ca98, VA_asm_target_0044cb12)
    L_0044ca9a:
        lea edx,[ebp*8]
    L_0044caa1:
        push edx
    L_0044caa2:
        call asm_operator_new_00452493
    L_0044caa7:
        mov ebx,eax
    L_0044caa9:
        add esp,4
    L_0044caac:
        test ebx,ebx
    L_0044caae:
        jne short L_0044caba
    L_0044cab0:
        mov eax,8007000Eh
    L_0044cab5:
        jmp asm_target_0044cb8e
    L_0044caba:
        xor eax,eax
    L_0044cabc:
        test ebp,ebp
    L_0044cabe:
        TH10_REL8(0x76, 0x0044cabe, VA_asm_target_0044cae5)
    L_0044cac0:
        lea ecx,[esi-1]
    L_0044cac3:
        TH10_REL8(0xeb, 0x0044cac3, VA_asm_FUN_0044c8f0_part_0044cad0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x64
        _emit 0x24
        _emit 0x00

    L_0044cad0:
        mov edx,dword ptr [esp+90h]
    L_0044cad7:
        mov dword ptr [ebx+eax*8],ecx
    L_0044cada:
        mov dword ptr [ebx+eax*8+4],edx
    L_0044cade:
        inc eax
    L_0044cadf:
        add ecx,esi
    L_0044cae1:
        cmp eax,ebp
    L_0044cae3:
        jb short L_0044cad0
    L_0044cae5:
        mov eax,dword ptr [esp+10h]
    L_0044cae9:
        mov ecx,dword ptr [eax]
    L_0044caeb:
        push ebx
    L_0044caec:
        push ebp
    L_0044caed:
        push eax
    L_0044caee:
        call dword ptr [ecx+0Ch]
    L_0044caf1:
        xor ebp,ebp
    L_0044caf3:
        cmp eax,ebp
    L_0044caf5:
        mov eax,dword ptr [esp+10h]
    L_0044caf9:
        jge short L_0044cb19
    L_0044cafb:
        cmp eax,ebp
    L_0044cafd:
        je short L_0044cb09
    L_0044caff:
        mov edx,dword ptr [eax]
    L_0044cb01:
        push eax
    L_0044cb02:
        call dword ptr [edx+8]
    L_0044cb05:
        mov dword ptr [esp+10h],ebp
    L_0044cb09:
        push ebx
    L_0044cb0a:
        call asm_free_004524a1
    L_0044cb0f:
        add esp,4
    L_0044cb12:
        mov eax,80004005h
    L_0044cb17:
        jmp short L_0044cb8e
    L_0044cb19:
        cmp eax,ebp
    L_0044cb1b:
        je short L_0044cb27
    L_0044cb1d:
        mov ecx,dword ptr [eax]
    L_0044cb1f:
        push eax
    L_0044cb20:
        call dword ptr [ecx+8]
    L_0044cb23:
        mov dword ptr [esp+10h],ebp
    L_0044cb27:
        push ebx
    L_0044cb28:
        call asm_free_004524a1
    L_0044cb2d:
        push 78h
    L_0044cb2f:
        call asm_operator_new_00452493
    L_0044cb34:
        add esp,8
    L_0044cb37:
        mov dword ptr [esp+24h],eax
    L_0044cb3b:
        cmp eax,ebp
    L_0044cb3d:
        mov dword ptr [esp+68h],ebp
    L_0044cb41:
        je short L_0044cb58
    L_0044cb43:
        mov edx,dword ptr [esp+14h]
    L_0044cb47:
        mov ecx,dword ptr [esp+18h]
    L_0044cb4b:
        push esi
    L_0044cb4c:
        push edx
    L_0044cb4d:
        push edi
    L_0044cb4e:
        push ecx
    L_0044cb4f:
        mov esi,eax
    L_0044cb51:
        call asm_Recovery_InitializeSingleInterface_0044d6a0
    L_0044cb56:
        jmp short L_0044cb5a
    L_0044cb58:
        xor eax,eax
    L_0044cb5a:
        mov edx,dword ptr [esp+20h]
    L_0044cb5e:
        mov dword ptr [edx],eax
    L_0044cb60:
        lea edi,[eax+34h]
    L_0044cb63:
        mov ecx,9
    L_0044cb68:
        lea esi,[esp+28h]
    L_0044cb6c:
        rep movsd
    L_0044cb6e:
        mov eax,dword ptr [edx]
    L_0044cb70:
        mov ecx,dword ptr [esp+1Ch]
    L_0044cb74:
        mov dword ptr [eax+58h],ecx
    L_0044cb77:
        mov eax,dword ptr [edx]
    L_0044cb79:
        mov ecx,dword ptr [esp+90h]
    L_0044cb80:
        mov dword ptr [eax+70h],ecx
    L_0044cb83:
        mov edx,dword ptr [edx]
    L_0044cb85:
        mov dword ptr [edx+74h],0
    L_0044cb8c:
        xor eax,eax
    L_0044cb8e:
        mov ecx,dword ptr [esp+60h]
    L_0044cb92:
        pop edi
    L_0044cb93:
        pop esi
    L_0044cb94:
        pop ebp
    L_0044cb95:
        mov dword ptr fs:[0],ecx
    L_0044cb9c:
        mov ecx,dword ptr [esp+50h]
    L_0044cba0:
        pop ebx
    L_0044cba1:
        xor ecx,esp
    L_0044cba3:
        call asm_security_check_cookie_00458ea5
    L_0044cba8:
        add esp,5Ch
    L_0044cbab:
        ret 28h
    }
}
