#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040E770..0x00411D2E: FUN_0040e770
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040e770_0040e770() {
    __asm {
    L_0040e770:
        push ebp
    L_0040e771:
        mov ebp,esp
    L_0040e773:
        and esp,0FFFFFFF8h
    L_0040e776:
        sub esp,2C4h
    L_0040e77c:
        mov eax,dword ptr [data_00473660]
    L_0040e781:
        xor eax,ebp
    L_0040e783:
        push ebx
    L_0040e784:
        mov ebx,ecx
    L_0040e786:
        mov edx,dword ptr [ebx+14D8h]
    L_0040e78c:
        mov dword ptr [esp+2C4h],eax
    L_0040e793:
        mov eax,dword ptr [edx+4]
    L_0040e796:
        push esi
    L_0040e797:
        mov esi,dword ptr [eax+4]
    L_0040e79a:
        xor eax,eax
    L_0040e79c:
        mov ax,word ptr [esi+4]
    L_0040e7a0:
        movsx ecx,ax
    L_0040e7a3:
        add ecx,0FFFFFF00h
    L_0040e7a9:
        cmp ecx,0B4h
    L_0040e7af:
        push edi
    L_0040e7b0:
        mov dword ptr [esp+30h],ebx
    L_0040e7b4:
        mov dword ptr [esp+1Ch],esi
    L_0040e7b8:
        mov dword ptr [esp+10h],eax
    L_0040e7bc:
        ja asm_target_00411d18
    L_0040e7c2:
        movzx ecx,byte ptr [ecx+411EE0h]
    L_0040e7c9:
        jmp dword ptr [ecx*4+411D30h]
    L_0040e7d0:
        mov edx,dword ptr [data_00477704]
    L_0040e7d6:
        mov eax,dword ptr [edx+10h]
    L_0040e7d9:
        test eax,eax
    L_0040e7db:
        jne asm_target_00411d18
    L_0040e7e1:
        mov eax,dword ptr [esp+1Ch]
    L_0040e7e5:
        mov eax,dword ptr [eax+10h]
    L_0040e7e8:
        add eax,4
    L_0040e7eb:
        cdq
    L_0040e7ec:
        and edx,3
    L_0040e7ef:
        add eax,edx
    L_0040e7f1:
        mov esi,eax
    L_0040e7f3:
        xor eax,eax
    L_0040e7f5:
        mov ecx,10h
    L_0040e7fa:
        lea edi,[esp+248h]
    L_0040e801:
        rep stosd
    L_0040e803:
        mov eax,dword ptr [ebx+1444h]
    L_0040e809:
        mov edi,dword ptr [esp+1Ch]
    L_0040e80d:
        sar esi,2
    L_0040e810:
        test eax,40000h
    L_0040e815:
        mov dword ptr [esp+18h],esi
    L_0040e819:
        jne short L_0040e859
    L_0040e81b:
        mov edx,dword ptr [edi+esi*4+10h]
    L_0040e81f:
        mov ecx,dword ptr [ebx+2Ch]
    L_0040e822:
        push edx
    L_0040e823:
        push 1
    L_0040e825:
        mov eax,ebx
    L_0040e827:
        mov dword ptr [esp+18h],ecx
    L_0040e82b:
        call asm_Ecl_ForwardFloat_00412aa0
    L_0040e830:
        fadd dword ptr [esp+10h]
    L_0040e834:
        mov eax,dword ptr [ebx+30h]
    L_0040e837:
        mov dword ptr [esp+10h],eax
    L_0040e83b:
        fstp dword ptr [esp+248h]
    L_0040e842:
        mov ecx,dword ptr [edi+esi*4+14h]
    L_0040e846:
        push ecx
    L_0040e847:
        push 2
    L_0040e849:
        mov eax,ebx
    L_0040e84b:
        call asm_Ecl_ForwardFloat_00412aa0
    L_0040e850:
        fadd dword ptr [esp+10h]
    L_0040e854:
        jmp asm_target_0040e8fc
    L_0040e859:
        mov eax,dword ptr [edi+esi*4+10h]
    L_0040e85d:
        mov edx,dword ptr [ebx+2Ch]
    L_0040e860:
        push eax
    L_0040e861:
        push 1
    L_0040e863:
        mov eax,ebx
    L_0040e865:
        mov dword ptr [esp+18h],edx
    L_0040e869:
        call asm_Ecl_ForwardFloat_00412aa0
    L_0040e86e:
        fadd dword ptr [esp+10h]
    L_0040e872:
        mov edx,dword ptr [edi+esi*4+14h]
    L_0040e876:
        mov ecx,dword ptr [ebx+30h]
    L_0040e879:
        push edx
    L_0040e87a:
        fstp dword ptr [esp+28h]
    L_0040e87e:
        push 2
    L_0040e880:
        mov eax,ebx
    L_0040e882:
        mov dword ptr [esp+18h],ecx
    L_0040e886:
        call asm_Ecl_ForwardFloat_00412aa0
    L_0040e88b:
        fadd dword ptr [esp+10h]
    L_0040e88f:
        mov eax,dword ptr [ebx+34h]
    L_0040e892:
        xor ebx,ebx
    L_0040e894:
        mov esi,491C28h
    L_0040e899:
        fstp dword ptr [esp+28h]
    L_0040e89d:
        mov dword ptr [esp+2Ch],eax
    L_0040e8a1:
        call asm_GameThread_SelectRenderStageRetail_00401d20
    L_0040e8a6:
        push 474DF0h
    L_0040e8ab:
        push 491DC8h
    L_0040e8b0:
        push 491E08h
    L_0040e8b5:
        push 491E48h
    L_0040e8ba:
        lea ecx,[esp+34h]
    L_0040e8be:
        push ecx
    L_0040e8bf:
        lea edx,[esp+25Ch]
    L_0040e8c6:
        push edx
    L_0040e8c7:
        call asm_D3DXVec3Project_0045218e
    L_0040e8cc:
        fld dword ptr [esp+248h]
    L_0040e8d3:
        fsub dword ptr [data_00470b4c]
    L_0040e8d9:
        mov esi,dword ptr [esp+18h]
    L_0040e8dd:
        mov dword ptr [esp+250h],ebx
    L_0040e8e4:
        mov ebx,dword ptr [esp+30h]
    L_0040e8e8:
        fstp dword ptr [esp+248h]
    L_0040e8ef:
        fld dword ptr [esp+24Ch]
    L_0040e8f6:
        fsub dword ptr [data_00470b48]
    L_0040e8fc:
        mov edi,dword ptr [esp+1Ch]
    L_0040e900:
        mov ecx,dword ptr [ebx+14D8h]
    L_0040e906:
        fstp dword ptr [esp+24Ch]
    L_0040e90d:
        mov eax,dword ptr [edi+esi*4+18h]
    L_0040e911:
        mov edx,dword ptr [ecx+4]
    L_0040e914:
        push eax
    L_0040e915:
        push 3
    L_0040e917:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0040e91c:
        mov ecx,dword ptr [ebx+14D8h]
    L_0040e922:
        mov dword ptr [esp+25Ch],eax
    L_0040e929:
        mov eax,dword ptr [edi+esi*4+1Ch]
    L_0040e92d:
        mov edx,dword ptr [ecx+4]
    L_0040e930:
        push eax
    L_0040e931:
        push 4
    L_0040e933:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0040e938:
        mov dword ptr [esp+254h],eax
    L_0040e93f:
        mov esi,dword ptr [edi+esi*4+20h]
    L_0040e943:
        mov eax,dword ptr [ebx+14D8h]
    L_0040e949:
        mov edx,dword ptr [eax+4]
    L_0040e94c:
        push esi
    L_0040e94d:
        push 5
    L_0040e94f:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0040e954:
        lea esi,[ebx+0FCh]
    L_0040e95a:
        mov ecx,8
    L_0040e95f:
        lea edi,[esp+268h]
    L_0040e966:
        mov dword ptr [esp+258h],eax
    L_0040e96d:
        rep movsd
    L_0040e96f:
        jmp asm_target_0040ecfb
    L_0040e974:
        mov edx,dword ptr [data_00477704]
    L_0040e97a:
        mov eax,dword ptr [edx+10h]
    L_0040e97d:
        test eax,eax
    L_0040e97f:
        jne asm_target_00411d18
    L_0040e985:
        mov eax,dword ptr [esp+1Ch]
    L_0040e989:
        mov eax,dword ptr [eax+10h]
    L_0040e98c:
        add eax,4
    L_0040e98f:
        cdq
    L_0040e990:
        and edx,3
    L_0040e993:
        add eax,edx
    L_0040e995:
        mov esi,eax
    L_0040e997:
        xor eax,eax
    L_0040e999:
        mov ecx,10h
    L_0040e99e:
        lea edi,[esp+248h]
    L_0040e9a5:
        rep stosd
    L_0040e9a7:
        mov edi,dword ptr [esp+1Ch]
    L_0040e9ab:
        sar esi,2
    L_0040e9ae:
        mov ecx,dword ptr [edi+esi*4+10h]
    L_0040e9b2:
        push ecx
    L_0040e9b3:
        push 1
    L_0040e9b5:
        mov eax,ebx
    L_0040e9b7:
        call asm_Ecl_ForwardFloat_00412aa0
    L_0040e9bc:
        mov edx,dword ptr [edi+esi*4+14h]
    L_0040e9c0:
        push edx
    L_0040e9c1:
        fstp dword ptr [esp+24Ch]
    L_0040e9c8:
        push 2
    L_0040e9ca:
        mov eax,ebx
    L_0040e9cc:
        call asm_Ecl_ForwardFloat_00412aa0
    L_0040e9d1:
        jmp asm_target_0040e900
    L_0040e9d6:
        mov edx,dword ptr [data_00477704]
    L_0040e9dc:
        mov eax,dword ptr [edx+10h]
    L_0040e9df:
        test eax,eax
    L_0040e9e1:
        jne asm_target_00411d18
    L_0040e9e7:
        mov eax,dword ptr [esp+1Ch]
    L_0040e9eb:
        mov eax,dword ptr [eax+10h]
    L_0040e9ee:
        add eax,4
    L_0040e9f1:
        cdq
    L_0040e9f2:
        and edx,3
    L_0040e9f5:
        add eax,edx
    L_0040e9f7:
        mov esi,eax
    L_0040e9f9:
        xor eax,eax
    L_0040e9fb:
        mov ecx,10h
    L_0040ea00:
        lea edi,[esp+248h]
    L_0040ea07:
        rep stosd
    L_0040ea09:
        mov edi,dword ptr [esp+1Ch]
    L_0040ea0d:
        sar esi,2
    L_0040ea10:
        mov ecx,dword ptr [edi+esi*4+10h]
    L_0040ea14:
        push ecx
    L_0040ea15:
        push 1
    L_0040ea17:
        mov eax,ebx
    L_0040ea19:
        call asm_Ecl_ForwardFloat_00412aa0
    L_0040ea1e:
        mov edx,dword ptr [edi+esi*4+14h]
    L_0040ea22:
        fadd dword ptr [data_00491d7c]
    L_0040ea28:
        push edx
    L_0040ea29:
        push 2
    L_0040ea2b:
        mov eax,ebx
    L_0040ea2d:
        fstp dword ptr [esp+250h]
    L_0040ea34:
        call asm_Ecl_ForwardFloat_00412aa0
    L_0040ea39:
        mov eax,dword ptr [edi+esi*4+18h]
    L_0040ea3d:
        fadd dword ptr [data_00491d80]
    L_0040ea43:
        push eax
    L_0040ea44:
        push 3
    L_0040ea46:
        mov eax,ebx
    L_0040ea48:
        fstp dword ptr [esp+254h]
    L_0040ea4f:
        call asm_Ecl_ForwardFloat_00412aa0
    L_0040ea54:
        fstp dword ptr [esp+250h]
    L_0040ea5b:
        mov eax,dword ptr [edi+esi*4+1Ch]
    L_0040ea5f:
        mov ecx,dword ptr [ebx+14D8h]
    L_0040ea65:
        mov edx,dword ptr [ecx+4]
    L_0040ea68:
        push eax
    L_0040ea69:
        push 4
    L_0040ea6b:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0040ea70:
        mov ecx,dword ptr [ebx+14D8h]
    L_0040ea76:
        mov edx,dword ptr [ecx+4]
    L_0040ea79:
        mov dword ptr [esp+25Ch],eax
    L_0040ea80:
        mov eax,dword ptr [edi+esi*4+20h]
    L_0040ea84:
        push eax
    L_0040ea85:
        push 5
    L_0040ea87:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0040ea8c:
        mov esi,dword ptr [edi+esi*4+24h]
    L_0040ea90:
        mov dword ptr [esp+254h],eax
    L_0040ea97:
        mov eax,dword ptr [ebx+14D8h]
    L_0040ea9d:
        mov edx,dword ptr [eax+4]
    L_0040eaa0:
        push esi
    L_0040eaa1:
        push 6
    L_0040eaa3:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0040eaa8:
        mov edx,dword ptr [data_00477704]
    L_0040eaae:
        mov dword ptr [esp+258h],eax
    L_0040eab5:
        lea esi,[ebx+0FCh]
    L_0040eabb:
        mov ecx,8
    L_0040eac0:
        lea edi,[esp+268h]
    L_0040eac7:
        rep movsd
    L_0040eac9:
        mov ecx,dword ptr [esp+1Ch]
    L_0040eacd:
        mov esi,dword ptr [esp+264h]
    L_0040ead4:
        add ecx,14h
    L_0040ead7:
        push ecx
    L_0040ead8:
        or esi,1
    L_0040eadb:
        push edx
    L_0040eadc:
        lea eax,[esp+250h]
    L_0040eae3:
        mov dword ptr [esp+26Ch],esi
    L_0040eaea:
        call asm_FUN_0040cfb0_0040cfb0
    L_0040eaef:
        xor eax,eax
    L_0040eaf1:
        pop edi
    L_0040eaf2:
        pop esi
    L_0040eaf3:
        pop ebx
    L_0040eaf4:
        mov ecx,dword ptr [esp+2C0h]
    L_0040eafb:
        xor ecx,ebp
    L_0040eafd:
        call asm_security_check_cookie_00458ea5
    L_0040eb02:
        mov esp,ebp
    L_0040eb04:
        pop ebp
    L_0040eb05:
        ret
    L_0040eb06:
        mov eax,dword ptr [data_00477704]
    L_0040eb0b:
        mov ecx,dword ptr [eax+10h]
    L_0040eb0e:
        test ecx,ecx
    L_0040eb10:
        jne asm_target_00411d18
    L_0040eb16:
        mov ecx,dword ptr [esp+1Ch]
    L_0040eb1a:
        mov eax,dword ptr [ecx+10h]
    L_0040eb1d:
        add eax,4
    L_0040eb20:
        cdq
    L_0040eb21:
        and edx,3
    L_0040eb24:
        add eax,edx
    L_0040eb26:
        mov edx,dword ptr [ebx+2Ch]
    L_0040eb29:
        mov esi,eax
    L_0040eb2b:
        xor eax,eax
    L_0040eb2d:
        mov ecx,10h
    L_0040eb32:
        lea edi,[esp+248h]
    L_0040eb39:
        rep stosd
    L_0040eb3b:
        mov edi,dword ptr [esp+1Ch]
    L_0040eb3f:
        sar esi,2
    L_0040eb42:
        mov eax,dword ptr [edi+esi*4+10h]
    L_0040eb46:
        push eax
    L_0040eb47:
        push 1
    L_0040eb49:
        mov eax,ebx
    L_0040eb4b:
        mov dword ptr [esp+18h],edx
    L_0040eb4f:
        call asm_Ecl_ForwardFloat_00412aa0
    L_0040eb54:
        mov edx,dword ptr [edi+esi*4+14h]
    L_0040eb58:
        fadd dword ptr [esp+10h]
    L_0040eb5c:
        mov ecx,dword ptr [ebx+30h]
    L_0040eb5f:
        push edx
    L_0040eb60:
        push 2
    L_0040eb62:
        mov eax,ebx
    L_0040eb64:
        fstp dword ptr [esp+250h]
    L_0040eb6b:
        mov dword ptr [esp+18h],ecx
    L_0040eb6f:
        call asm_Ecl_ForwardFloat_00412aa0
    L_0040eb74:
        mov eax,dword ptr [edi+esi*4+18h]
    L_0040eb78:
        fadd dword ptr [esp+10h]
    L_0040eb7c:
        mov ecx,dword ptr [ebx+14D8h]
    L_0040eb82:
        mov edx,dword ptr [ecx+4]
    L_0040eb85:
        push eax
    L_0040eb86:
        fstp dword ptr [esp+250h]
    L_0040eb8d:
        push 3
    L_0040eb8f:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0040eb94:
        mov ecx,dword ptr [ebx+14D8h]
    L_0040eb9a:
        mov edx,dword ptr [ecx+4]
    L_0040eb9d:
        mov dword ptr [esp+25Ch],eax
    L_0040eba4:
        mov eax,dword ptr [edi+esi*4+1Ch]
    L_0040eba8:
        push eax
    L_0040eba9:
        push 4
    L_0040ebab:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0040ebb0:
        mov esi,dword ptr [edi+esi*4+20h]
    L_0040ebb4:
        mov dword ptr [esp+254h],eax
    L_0040ebbb:
        mov eax,dword ptr [ebx+14D8h]
    L_0040ebc1:
        mov edx,dword ptr [eax+4]
    L_0040ebc4:
        push esi
    L_0040ebc5:
        push 5
    L_0040ebc7:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0040ebcc:
        mov dword ptr [esp+258h],eax
    L_0040ebd3:
        mov eax,dword ptr [esp+1Ch]
    L_0040ebd7:
        add eax,14h
    L_0040ebda:
        lea esi,[ebx+0FCh]
    L_0040ebe0:
        mov ecx,8
    L_0040ebe5:
        lea edi,[esp+268h]
    L_0040ebec:
        rep movsd
    L_0040ebee:
        mov ecx,dword ptr [data_00477704]
    L_0040ebf4:
        push eax
    L_0040ebf5:
        push ecx
    L_0040ebf6:
        lea eax,[esp+250h]
    L_0040ebfd:
        mov dword ptr [esp+268h],1
    L_0040ec08:
        call asm_FUN_0040cfb0_0040cfb0
    L_0040ec0d:
        xor eax,eax
    L_0040ec0f:
        pop edi
    L_0040ec10:
        pop esi
    L_0040ec11:
        pop ebx
    L_0040ec12:
        mov ecx,dword ptr [esp+2C0h]
    L_0040ec19:
        xor ecx,ebp
    L_0040ec1b:
        call asm_security_check_cookie_00458ea5
    L_0040ec20:
        mov esp,ebp
    L_0040ec22:
        pop ebp
    L_0040ec23:
        ret
    L_0040ec24:
        mov edx,dword ptr [data_00477704]
    L_0040ec2a:
        mov eax,dword ptr [edx+10h]
    L_0040ec2d:
        test eax,eax
    L_0040ec2f:
        jne asm_target_00411d18
    L_0040ec35:
        mov eax,dword ptr [esp+1Ch]
    L_0040ec39:
        mov eax,dword ptr [eax+10h]
    L_0040ec3c:
        add eax,4
    L_0040ec3f:
        cdq
    L_0040ec40:
        and edx,3
    L_0040ec43:
        add eax,edx
    L_0040ec45:
        mov esi,eax
    L_0040ec47:
        xor eax,eax
    L_0040ec49:
        mov ecx,10h
    L_0040ec4e:
        lea edi,[esp+248h]
    L_0040ec55:
        rep stosd
    L_0040ec57:
        mov edi,dword ptr [esp+1Ch]
    L_0040ec5b:
        sar esi,2
    L_0040ec5e:
        mov ecx,dword ptr [edi+esi*4+10h]
    L_0040ec62:
        push ecx
    L_0040ec63:
        push 1
    L_0040ec65:
        mov eax,ebx
    L_0040ec67:
        call asm_Ecl_ForwardFloat_00412aa0
    L_0040ec6c:
        mov edx,dword ptr [edi+esi*4+14h]
    L_0040ec70:
        push edx
    L_0040ec71:
        fstp dword ptr [esp+24Ch]
    L_0040ec78:
        push 2
    L_0040ec7a:
        mov eax,ebx
    L_0040ec7c:
        call asm_Ecl_ForwardFloat_00412aa0
    L_0040ec81:
        mov eax,dword ptr [edi+esi*4+18h]
    L_0040ec85:
        fstp dword ptr [esp+24Ch]
    L_0040ec8c:
        mov ecx,dword ptr [ebx+14D8h]
    L_0040ec92:
        mov edx,dword ptr [ecx+4]
    L_0040ec95:
        push eax
    L_0040ec96:
        push 3
    L_0040ec98:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0040ec9d:
        mov ecx,dword ptr [ebx+14D8h]
    L_0040eca3:
        mov edx,dword ptr [ecx+4]
    L_0040eca6:
        mov dword ptr [esp+25Ch],eax
    L_0040ecad:
        mov eax,dword ptr [edi+esi*4+1Ch]
    L_0040ecb1:
        push eax
    L_0040ecb2:
        push 4
    L_0040ecb4:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0040ecb9:
        mov esi,dword ptr [edi+esi*4+20h]
    L_0040ecbd:
        mov dword ptr [esp+254h],eax
    L_0040ecc4:
        mov eax,dword ptr [ebx+14D8h]
    L_0040ecca:
        mov edx,dword ptr [eax+4]
    L_0040eccd:
        push esi
    L_0040ecce:
        push 5
    L_0040ecd0:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0040ecd5:
        lea esi,[ebx+0FCh]
    L_0040ecdb:
        mov ecx,8
    L_0040ece0:
        lea edi,[esp+268h]
    L_0040ece7:
        mov dword ptr [esp+258h],eax
    L_0040ecee:
        rep movsd
    L_0040ecf0:
        mov dword ptr [esp+260h],1
    L_0040ecfb:
        mov eax,dword ptr [esp+1Ch]
    L_0040ecff:
        mov ecx,dword ptr [data_00477704]
    L_0040ed05:
        add eax,14h
    L_0040ed08:
        push eax
    L_0040ed09:
        push ecx
    L_0040ed0a:
        lea eax,[esp+250h]
    L_0040ed11:
        call asm_FUN_0040cfb0_0040cfb0
    L_0040ed16:
        xor eax,eax
    L_0040ed18:
        pop edi
    L_0040ed19:
        pop esi
    L_0040ed1a:
        pop ebx
    L_0040ed1b:
        mov ecx,dword ptr [esp+2C0h]
    L_0040ed22:
        xor ecx,ebp
    L_0040ed24:
        call asm_security_check_cookie_00458ea5
    L_0040ed29:
        mov esp,ebp
    L_0040ed2b:
        pop ebp
    L_0040ed2c:
        ret
    L_0040ed2d:
        mov edx,dword ptr [edx+4]
    L_0040ed30:
        push 0
    L_0040ed32:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040ed37:
        mov dword ptr [ebx+0E8h],eax
    L_0040ed3d:
        xor eax,eax
    L_0040ed3f:
        pop edi
    L_0040ed40:
        pop esi
    L_0040ed41:
        pop ebx
    L_0040ed42:
        mov ecx,dword ptr [esp+2C0h]
    L_0040ed49:
        xor ecx,ebp
    L_0040ed4b:
        call asm_security_check_cookie_00458ea5
    L_0040ed50:
        mov esp,ebp
    L_0040ed52:
        pop ebp
    L_0040ed53:
        ret
    L_0040ed54:
        mov edx,dword ptr [edx+4]
    L_0040ed57:
        push 0
    L_0040ed59:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040ed5e:
        mov esi,eax
    L_0040ed60:
        mov eax,dword ptr [ebx+14D8h]
    L_0040ed66:
        mov edx,dword ptr [eax+4]
    L_0040ed69:
        push 1
    L_0040ed6b:
        mov dword ptr [esp+1Ch],esi
    L_0040ed6f:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040ed74:
        lea esi,[ebx+esi*4+0C0h]
    L_0040ed7b:
        mov edi,eax
    L_0040ed7d:
        call asm_AnimationManager_MarkForRemovalAndClearHandle_00449630
    L_0040ed82:
        test edi,edi
    L_0040ed84:
        jl asm_target_00411d18
    L_0040ed8a:
        mov eax,dword ptr [ebx+14D8h]
    L_0040ed90:
        mov edx,dword ptr [eax+4]
    L_0040ed93:
        push 1
    L_0040ed95:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040ed9a:
        mov edx,dword ptr [ebx+0E8h]
    L_0040eda0:
        mov ecx,dword ptr [data_00477704]
    L_0040eda6:
        mov ecx,dword ptr [ecx+edx*4+30h]
    L_0040edaa:
        push 5
    L_0040edac:
        push eax
    L_0040edad:
        push ecx
    L_0040edae:
        lea edi,[esp+50h]
    L_0040edb2:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_0040edb7:
        mov edx,dword ptr [eax]
    L_0040edb9:
        mov eax,dword ptr [esp+18h]
    L_0040edbd:
        test eax,eax
    L_0040edbf:
        mov dword ptr [esi],edx
    L_0040edc1:
        jne short L_0040ede5
    L_0040edc3:
        mov eax,dword ptr [ebx+14D8h]
    L_0040edc9:
        mov edx,dword ptr [eax+4]
    L_0040edcc:
        push 1
    L_0040edce:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040edd3:
        mov dword ptr [ebx+0F0h],eax
    L_0040edd9:
        mov eax,dword ptr [ebx+0E8h]
    L_0040eddf:
        mov dword ptr [ebx+0ECh],eax
    L_0040ede5:
        call asm_AnimationManager_ValidateHandle_00449450
    L_0040edea:
        mov ecx,dword ptr [esp+18h]
    L_0040edee:
        jmp asm_target_0040f103
    L_0040edf3:
        mov edx,dword ptr [edx+4]
    L_0040edf6:
        push 0
    L_0040edf8:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040edfd:
        mov esi,eax
    L_0040edff:
        mov eax,dword ptr [ebx+14D8h]
    L_0040ee05:
        mov edx,dword ptr [eax+4]
    L_0040ee08:
        push 1
    L_0040ee0a:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040ee0f:
        mov ecx,dword ptr [data_00477704]
    L_0040ee15:
        mov edx,dword ptr [ecx+esi*4+30h]
    L_0040ee19:
        push 6
    L_0040ee1b:
        push eax
    L_0040ee1c:
        push edx
    L_0040ee1d:
        lea edi,[esp+1Ch]
    L_0040ee21:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_0040ee26:
        jmp short L_0040ee5b
    L_0040ee28:
        mov edx,dword ptr [edx+4]
    L_0040ee2b:
        push 0
    L_0040ee2d:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040ee32:
        mov esi,eax
    L_0040ee34:
        mov eax,dword ptr [ebx+14D8h]
    L_0040ee3a:
        mov edx,dword ptr [eax+4]
    L_0040ee3d:
        push 1
    L_0040ee3f:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040ee44:
        mov ecx,dword ptr [data_00477704]
    L_0040ee4a:
        mov edx,dword ptr [ecx+esi*4+30h]
    L_0040ee4e:
        push 6
    L_0040ee50:
        push eax
    L_0040ee51:
        push edx
    L_0040ee52:
        lea edi,[esp+1Ch]
    L_0040ee56:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0040ee5b:
        lea esi,[esp+10h]
    L_0040ee5f:
        call asm_AnimationManager_ValidateHandle_00449450
    L_0040ee64:
        mov esi,eax
    L_0040ee66:
        test dword ptr [ebx+1444h],40000h
    L_0040ee70:
        jne short L_0040eea7
    L_0040ee72:
        lea eax,[ebx+2Ch]
    L_0040ee75:
        call asm_Recovery_OffsetPoint_00418810
    L_0040ee7a:
        mov ecx,dword ptr [eax]
    L_0040ee7c:
        add esi,340h
    L_0040ee82:
        mov dword ptr [esi],ecx
    L_0040ee84:
        mov edx,dword ptr [eax+4]
    L_0040ee87:
        mov dword ptr [esi+4],edx
    L_0040ee8a:
        mov eax,dword ptr [eax+8]
    L_0040ee8d:
        mov dword ptr [esi+8],eax
    L_0040ee90:
        xor eax,eax
    L_0040ee92:
        pop edi
    L_0040ee93:
        pop esi
    L_0040ee94:
        pop ebx
    L_0040ee95:
        mov ecx,dword ptr [esp+2C0h]
    L_0040ee9c:
        xor ecx,ebp
    L_0040ee9e:
        call asm_security_check_cookie_00458ea5
    L_0040eea3:
        mov esp,ebp
    L_0040eea5:
        pop ebp
    L_0040eea6:
        ret
    L_0040eea7:
        add ebx,2Ch
    L_0040eeaa:
        mov ecx,dword ptr [ebx]
    L_0040eeac:
        add esi,340h
    L_0040eeb2:
        mov dword ptr [esi],ecx
    L_0040eeb4:
        mov edx,dword ptr [ebx+4]
    L_0040eeb7:
        mov dword ptr [esi+4],edx
    L_0040eeba:
        mov eax,dword ptr [ebx+8]
    L_0040eebd:
        mov dword ptr [esi+8],eax
    L_0040eec0:
        xor eax,eax
    L_0040eec2:
        pop edi
    L_0040eec3:
        pop esi
    L_0040eec4:
        pop ebx
    L_0040eec5:
        mov ecx,dword ptr [esp+2C0h]
    L_0040eecc:
        xor ecx,ebp
    L_0040eece:
        call asm_security_check_cookie_00458ea5
    L_0040eed3:
        mov esp,ebp
    L_0040eed5:
        pop ebp
    L_0040eed6:
        ret
    L_0040eed7:
        mov edx,dword ptr [edx+4]
    L_0040eeda:
        push 0
    L_0040eedc:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040eee1:
        mov ebx,dword ptr [ebx+14D8h]
    L_0040eee7:
        mov edx,dword ptr [ebx+4]
    L_0040eeea:
        push 1
    L_0040eeec:
        mov esi,eax
    L_0040eeee:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040eef3:
        mov ecx,dword ptr [data_00477704]
    L_0040eef9:
        mov edx,dword ptr [ecx+esi*4+30h]
    L_0040eefd:
        push 6
    L_0040eeff:
        push eax
    L_0040ef00:
        push edx
    L_0040ef01:
        lea edi,[esp+1Ch]
    L_0040ef05:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_0040ef0a:
        xor eax,eax
    L_0040ef0c:
        pop edi
    L_0040ef0d:
        pop esi
    L_0040ef0e:
        pop ebx
    L_0040ef0f:
        mov ecx,dword ptr [esp+2C0h]
    L_0040ef16:
        xor ecx,ebp
    L_0040ef18:
        call asm_security_check_cookie_00458ea5
    L_0040ef1d:
        mov esp,ebp
    L_0040ef1f:
        pop ebp
    L_0040ef20:
        ret
    L_0040ef21:
        mov edx,dword ptr [edx+4]
    L_0040ef24:
        push 0
    L_0040ef26:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040ef2b:
        mov esi,eax
    L_0040ef2d:
        mov eax,dword ptr [ebx+14D8h]
    L_0040ef33:
        mov edx,dword ptr [eax+4]
    L_0040ef36:
        push 1
    L_0040ef38:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040ef3d:
        push 6
    L_0040ef3f:
        push eax
    L_0040ef40:
        mov eax,dword ptr [data_00477704]
    L_0040ef45:
        mov ecx,dword ptr [eax+esi*4+30h]
    L_0040ef49:
        push ecx
    L_0040ef4a:
        lea edi,[esp+1Ch]
    L_0040ef4e:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_0040ef53:
        mov esi,edi
    L_0040ef55:
        call asm_AnimationManager_ValidateHandle_00449450
    L_0040ef5a:
        mov esi,eax
    L_0040ef5c:
        test dword ptr [ebx+1444h],40000h
    L_0040ef66:
        jne short L_0040ef88
    L_0040ef68:
        lea eax,[ebx+2Ch]
    L_0040ef6b:
        call asm_Recovery_OffsetPoint_00418810
    L_0040ef70:
        mov ecx,dword ptr [eax]
    L_0040ef72:
        lea edx,[esi+340h]
    L_0040ef78:
        mov dword ptr [edx],ecx
    L_0040ef7a:
        mov ecx,dword ptr [eax+4]
    L_0040ef7d:
        mov dword ptr [edx+4],ecx
    L_0040ef80:
        mov eax,dword ptr [eax+8]
    L_0040ef83:
        mov dword ptr [edx+8],eax
    L_0040ef86:
        jmp short L_0040efa1
    L_0040ef88:
        lea ecx,[ebx+2Ch]
    L_0040ef8b:
        mov eax,dword ptr [ecx]
    L_0040ef8d:
        lea edx,[esi+340h]
    L_0040ef93:
        mov dword ptr [edx],eax
    L_0040ef95:
        mov eax,dword ptr [ecx+4]
    L_0040ef98:
        mov dword ptr [edx+4],eax
    L_0040ef9b:
        mov ecx,dword ptr [ecx+8]
    L_0040ef9e:
        mov dword ptr [edx+8],ecx
    L_0040efa1:
        mov ebx,dword ptr [ebx+14D8h]
    L_0040efa7:
        mov eax,dword ptr [ebx+4]
    L_0040efaa:
        mov ecx,2
    L_0040efaf:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040efb4:
        fstp dword ptr [esi+2Ch]
    L_0040efb7:
        or dword ptr [esi+35Ch],4
    L_0040efbe:
        xor eax,eax
    L_0040efc0:
        pop edi
    L_0040efc1:
        pop esi
    L_0040efc2:
        pop ebx
    L_0040efc3:
        mov ecx,dword ptr [esp+2C0h]
    L_0040efca:
        xor ecx,ebp
    L_0040efcc:
        call asm_security_check_cookie_00458ea5
    L_0040efd1:
        mov esp,ebp
    L_0040efd3:
        pop ebp
    L_0040efd4:
        ret
    L_0040efd5:
        mov edx,dword ptr [edx+4]
    L_0040efd8:
        push 0
    L_0040efda:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040efdf:
        mov esi,eax
    L_0040efe1:
        mov eax,dword ptr [ebx+14D8h]
    L_0040efe7:
        mov edx,dword ptr [eax+4]
    L_0040efea:
        push 1
    L_0040efec:
        mov dword ptr [esp+1Ch],esi
    L_0040eff0:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040eff5:
        mov edi,eax
    L_0040eff7:
        lea esi,[ebx+esi*4+0C0h]
    L_0040effe:
        mov dword ptr [esp+10h],edi
    L_0040f002:
        call asm_AnimationManager_MarkForRemovalAndClearHandle_00449630
    L_0040f007:
        mov edx,dword ptr [ebx+0E8h]
    L_0040f00d:
        mov eax,dword ptr [data_00477704]
    L_0040f012:
        mov eax,dword ptr [eax+edx*4+30h]
    L_0040f016:
        push 5
    L_0040f018:
        push edi
    L_0040f019:
        push eax
    L_0040f01a:
        lea edi,[esp+58h]
    L_0040f01e:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_0040f023:
        mov ecx,dword ptr [eax]
    L_0040f025:
        mov dword ptr [esi],ecx
    L_0040f027:
        call asm_AnimationManager_ValidateHandle_00449450
    L_0040f02c:
        mov ecx,dword ptr [esp+18h]
    L_0040f030:
        test ecx,ecx
    L_0040f032:
        jne short L_0040f04c
    L_0040f034:
        fld dword ptr [eax+50h]
    L_0040f037:
        fmul dword ptr [eax+40h]
    L_0040f03a:
        fstp dword ptr [ebx+13A4h]
    L_0040f040:
        fld dword ptr [eax+4Ch]
    L_0040f043:
        fmul dword ptr [eax+3Ch]
    L_0040f046:
        fstp dword ptr [ebx+13A8h]
    L_0040f04c:
        test byte ptr [ebx+1444h],10h
    L_0040f053:
        je short L_0040f05c
    L_0040f055:
        mov eax,esi
    L_0040f057:
        call asm_AnimationManager_ClearFlag_004495e0
    L_0040f05c:
        mov eax,dword ptr [esp+18h]
    L_0040f060:
        test eax,eax
    L_0040f062:
        jne asm_target_00411d18
    L_0040f068:
        mov eax,dword ptr [ebx+1444h]
    L_0040f06e:
        mov edx,dword ptr [ebx+0E8h]
    L_0040f074:
        or eax,1000h
    L_0040f079:
        mov dword ptr [ebx+1444h],eax
    L_0040f07f:
        mov eax,dword ptr [esp+10h]
    L_0040f083:
        mov dword ptr [ebx+0F4h],eax
    L_0040f089:
        mov dword ptr [ebx+0F0h],eax
    L_0040f08f:
        mov dword ptr [ebx+0F8h],0
    L_0040f099:
        mov dword ptr [ebx+0ECh],edx
    L_0040f09f:
        xor eax,eax
    L_0040f0a1:
        pop edi
    L_0040f0a2:
        pop esi
    L_0040f0a3:
        pop ebx
    L_0040f0a4:
        mov ecx,dword ptr [esp+2C0h]
    L_0040f0ab:
        xor ecx,ebp
    L_0040f0ad:
        call asm_security_check_cookie_00458ea5
    L_0040f0b2:
        mov esp,ebp
    L_0040f0b4:
        pop ebp
    L_0040f0b5:
        ret
    L_0040f0b6:
        mov edx,dword ptr [edx+4]
    L_0040f0b9:
        push 0
    L_0040f0bb:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040f0c0:
        lea esi,[ebx+eax*4+0C0h]
    L_0040f0c7:
        mov dword ptr [esp+10h],eax
    L_0040f0cb:
        call asm_AnimationManager_MarkForRemovalAndClearHandle_00449630
    L_0040f0d0:
        mov edx,dword ptr [ebx+0F4h]
    L_0040f0d6:
        mov eax,dword ptr [ebx+0E8h]
    L_0040f0dc:
        mov ecx,dword ptr [data_00477704]
    L_0040f0e2:
        mov eax,dword ptr [ecx+eax*4+30h]
    L_0040f0e6:
        push 5
    L_0040f0e8:
        add edx,5
    L_0040f0eb:
        push edx
    L_0040f0ec:
        push eax
    L_0040f0ed:
        lea edi,[esp+54h]
    L_0040f0f1:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_0040f0f6:
        mov eax,dword ptr [eax]
    L_0040f0f8:
        mov dword ptr [esi],eax
    L_0040f0fa:
        call asm_AnimationManager_ValidateHandle_00449450
    L_0040f0ff:
        mov ecx,dword ptr [esp+10h]
    L_0040f103:
        test ecx,ecx
    L_0040f105:
        jne short L_0040f11f
    L_0040f107:
        fld dword ptr [eax+50h]
    L_0040f10a:
        fmul dword ptr [eax+40h]
    L_0040f10d:
        fstp dword ptr [ebx+13A4h]
    L_0040f113:
        fld dword ptr [eax+4Ch]
    L_0040f116:
        fmul dword ptr [eax+3Ch]
    L_0040f119:
        fstp dword ptr [ebx+13A8h]
    L_0040f11f:
        test byte ptr [ebx+1444h],10h
    L_0040f126:
        je asm_target_00411d18
    L_0040f12c:
        mov eax,esi
    L_0040f12e:
        call asm_AnimationManager_ClearFlag_004495e0
    L_0040f133:
        xor eax,eax
    L_0040f135:
        pop edi
    L_0040f136:
        pop esi
    L_0040f137:
        pop ebx
    L_0040f138:
        mov ecx,dword ptr [esp+2C0h]
    L_0040f13f:
        xor ecx,ebp
    L_0040f141:
        call asm_security_check_cookie_00458ea5
    L_0040f146:
        mov esp,ebp
    L_0040f148:
        pop ebp
    L_0040f149:
        ret
    L_0040f14a:
        cmp ax,118h
    L_0040f14e:
        lea esi,[ebx+58h]
    L_0040f151:
        je short L_0040f159
    L_0040f153:
        lea esi,[ebx+84h]
    L_0040f159:
        mov eax,dword ptr [edx+4]
    L_0040f15c:
        xor ecx,ecx
    L_0040f15e:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f163:
        fstp dword ptr [esp+18h]
    L_0040f167:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f16d:
        mov eax,dword ptr [eax+4]
    L_0040f170:
        mov ecx,1
    L_0040f175:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f17a:
        fld dword ptr [esp+18h]
    L_0040f17e:
        fcomp qword ptr [data_00470d58]
    L_0040f184:
        fnstsw ax
    L_0040f186:
        test ah,41h
    L_0040f189:
        jne short L_0040f191
    L_0040f18b:
        mov ecx,dword ptr [esp+18h]
    L_0040f18f:
        mov dword ptr [esi],ecx
    L_0040f191:
        fcom qword ptr [data_00470d58]
    L_0040f197:
        fnstsw ax
    L_0040f199:
        test ah,41h
    L_0040f19c:
        jne short L_0040f1a3
    L_0040f19e:
        fstp dword ptr [esi+4]
    L_0040f1a1:
        jmp short L_0040f1a5
    L_0040f1a3:
        fstp st(0)
    L_0040f1a5:
        mov eax,dword ptr [esi+28h]
    L_0040f1a8:
        and eax,0FFFFFFFEh
    L_0040f1ab:
        mov dword ptr [esi+28h],eax
    L_0040f1ae:
        fld dword ptr [ebx+84h]
    L_0040f1b4:
        fadd dword ptr [ebx+58h]
    L_0040f1b7:
        add ebx,2Ch
    L_0040f1ba:
        fstp dword ptr [esp+24h]
    L_0040f1be:
        mov edx,dword ptr [esp+24h]
    L_0040f1c2:
        fld dword ptr [ebx+5Ch]
    L_0040f1c5:
        fadd dword ptr [ebx+30h]
    L_0040f1c8:
        fstp dword ptr [esp+28h]
    L_0040f1cc:
        mov eax,dword ptr [esp+28h]
    L_0040f1d0:
        fld dword ptr [ebx+60h]
    L_0040f1d3:
        fadd dword ptr [ebx+34h]
    L_0040f1d6:
        mov dword ptr [ebx],edx
    L_0040f1d8:
        mov dword ptr [ebx+4],eax
    L_0040f1db:
        xor eax,eax
    L_0040f1dd:
        fstp dword ptr [esp+2Ch]
    L_0040f1e1:
        mov ecx,dword ptr [esp+2Ch]
    L_0040f1e5:
        mov dword ptr [ebx+8],ecx
    L_0040f1e8:
        pop edi
    L_0040f1e9:
        pop esi
    L_0040f1ea:
        pop ebx
    L_0040f1eb:
        mov ecx,dword ptr [esp+2C0h]
    L_0040f1f2:
        xor ecx,ebp
    L_0040f1f4:
        call asm_security_check_cookie_00458ea5
    L_0040f1f9:
        mov esp,ebp
    L_0040f1fb:
        pop ebp
    L_0040f1fc:
        ret
    L_0040f1fd:
        cmp ax,128h
    L_0040f201:
        lea esi,[ebx+58h]
    L_0040f204:
        je short L_0040f20c
    L_0040f206:
        lea esi,[ebx+84h]
    L_0040f20c:
        mov eax,dword ptr [edx+4]
    L_0040f20f:
        xor ecx,ecx
    L_0040f211:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f216:
        fstp dword ptr [esp+10h]
    L_0040f21a:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f220:
        mov eax,dword ptr [eax+4]
    L_0040f223:
        mov ecx,1
    L_0040f228:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f22d:
        fstp dword ptr [esp+30h]
    L_0040f231:
        mov ebx,dword ptr [ebx+14D8h]
    L_0040f237:
        mov eax,dword ptr [ebx+4]
    L_0040f23a:
        mov ecx,2
    L_0040f23f:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f244:
        fld dword ptr [esp+10h]
    L_0040f248:
        fadd dword ptr [esi]
    L_0040f24a:
        xor eax,eax
    L_0040f24c:
        fstp dword ptr [esi]
    L_0040f24e:
        fld dword ptr [esp+30h]
    L_0040f252:
        fadd dword ptr [esi+4]
    L_0040f255:
        fstp dword ptr [esi+4]
    L_0040f258:
        fadd dword ptr [esi+8]
    L_0040f25b:
        fstp dword ptr [esi+8]
    L_0040f25e:
        pop edi
    L_0040f25f:
        pop esi
    L_0040f260:
        pop ebx
    L_0040f261:
        mov ecx,dword ptr [esp+2C0h]
    L_0040f268:
        xor ecx,ebp
    L_0040f26a:
        call asm_security_check_cookie_00458ea5
    L_0040f26f:
        mov esp,ebp
    L_0040f271:
        pop ebp
    L_0040f272:
        ret
    L_0040f273:
        cmp ax,119h
    L_0040f277:
        lea edi,[ebx+58h]
    L_0040f27a:
        je asm_target_0040f33c
    L_0040f280:
        lea edi,[ebx+84h]
    L_0040f286:
        lea esi,[ebx+188h]
    L_0040f28c:
        mov eax,dword ptr [edx+4]
    L_0040f28f:
        mov ecx,2
    L_0040f294:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f299:
        fstp dword ptr [esp+1Ch]
    L_0040f29d:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f2a3:
        mov eax,dword ptr [eax+4]
    L_0040f2a6:
        mov ecx,3
    L_0040f2ab:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f2b0:
        fstp dword ptr [esp+18h]
    L_0040f2b4:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f2ba:
        mov edx,dword ptr [eax+4]
    L_0040f2bd:
        push 0
    L_0040f2bf:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040f2c4:
        mov dword ptr [esi+44h],eax
    L_0040f2c7:
        mov eax,dword ptr [data_00491c14]
    L_0040f2cc:
        lea edx,[esi+18h]
    L_0040f2cf:
        mov dword ptr [edx],eax
    L_0040f2d1:
        mov ecx,dword ptr [data_00491c18]
    L_0040f2d7:
        mov dword ptr [edx+4],ecx
    L_0040f2da:
        mov eax,dword ptr [data_00491c1c]
    L_0040f2df:
        mov dword ptr [edx+8],eax
    L_0040f2e2:
        mov edx,dword ptr [data_00491c14]
    L_0040f2e8:
        lea ecx,[esi+24h]
    L_0040f2eb:
        mov dword ptr [ecx],edx
    L_0040f2ed:
        mov eax,dword ptr [data_00491c18]
    L_0040f2f2:
        mov dword ptr [ecx+4],eax
    L_0040f2f5:
        mov edx,dword ptr [data_00491c1c]
    L_0040f2fb:
        mov dword ptr [ecx+8],edx
    L_0040f2fe:
        mov ebx,dword ptr [ebx+14D8h]
    L_0040f304:
        mov edx,dword ptr [ebx+4]
    L_0040f307:
        push 1
    L_0040f309:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040f30e:
        fld dword ptr [esp+18h]
    L_0040f312:
        fcomp qword ptr [data_00470d58]
    L_0040f318:
        mov dword ptr [esi+48h],eax
    L_0040f31b:
        mov eax,edi
    L_0040f31d:
        mov edx,dword ptr [eax]
    L_0040f31f:
        mov ecx,esi
    L_0040f321:
        mov dword ptr [ecx],edx
    L_0040f323:
        mov edx,dword ptr [eax+4]
    L_0040f326:
        mov dword ptr [ecx+4],edx
    L_0040f329:
        mov eax,dword ptr [eax+8]
    L_0040f32c:
        mov dword ptr [ecx+8],eax
    L_0040f32f:
        fnstsw ax
    L_0040f331:
        test ah,41h
    L_0040f334:
        jne short L_0040f347
    L_0040f336:
        fld dword ptr [esp+18h]
    L_0040f33a:
        jmp short L_0040f34a
    L_0040f33c:
        lea esi,[ebx+13Ch]
    L_0040f342:
        jmp asm_target_0040f28c
    L_0040f347:
        fld dword ptr [edi+4]
    L_0040f34a:
        fld dword ptr [esp+1Ch]
    L_0040f34e:
        fcomp qword ptr [data_00470d58]
    L_0040f354:
        fnstsw ax
    L_0040f356:
        test ah,41h
    L_0040f359:
        jne short L_0040f361
    L_0040f35b:
        fld dword ptr [esp+1Ch]
    L_0040f35f:
        jmp short L_0040f363
    L_0040f361:
        fld dword ptr [edi]
    L_0040f363:
        fstp dword ptr [esp+24h]
    L_0040f367:
        mov edx,dword ptr [esp+24h]
    L_0040f36b:
        lea ecx,[esi+0Ch]
    L_0040f36e:
        mov dword ptr [ecx],edx
    L_0040f370:
        fstp dword ptr [esp+28h]
    L_0040f374:
        mov eax,dword ptr [esp+28h]
    L_0040f378:
        mov dword ptr [ecx+4],eax
    L_0040f37b:
        mov dword ptr [esp+2Ch],0
    L_0040f383:
        mov edx,dword ptr [esp+2Ch]
    L_0040f387:
        mov eax,esi
    L_0040f389:
        mov dword ptr [ecx+8],edx
    L_0040f38c:
        call asm_EmbeddedTimer_Reset_004050d0
    L_0040f391:
        and dword ptr [edi+28h],0FFFFFFFEh
    L_0040f395:
        xor eax,eax
    L_0040f397:
        pop edi
    L_0040f398:
        pop esi
    L_0040f399:
        pop ebx
    L_0040f39a:
        mov ecx,dword ptr [esp+2C0h]
    L_0040f3a1:
        xor ecx,ebp
    L_0040f3a3:
        call asm_security_check_cookie_00458ea5
    L_0040f3a8:
        mov esp,ebp
    L_0040f3aa:
        pop ebp
    L_0040f3ab:
        ret
    L_0040f3ac:
        cmp ax,11Ch
    L_0040f3b0:
        lea esi,[ebx+58h]
    L_0040f3b3:
        je short L_0040f3bb
    L_0040f3b5:
        lea esi,[ebx+84h]
    L_0040f3bb:
        mov eax,dword ptr [edx+4]
    L_0040f3be:
        xor ecx,ecx
    L_0040f3c0:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f3c5:
        fstp dword ptr [esp+1Ch]
    L_0040f3c9:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f3cf:
        mov eax,dword ptr [eax+4]
    L_0040f3d2:
        mov ecx,1
    L_0040f3d7:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f3dc:
        fstp dword ptr [esp+18h]
    L_0040f3e0:
        fld dword ptr [esp+1Ch]
    L_0040f3e4:
        fcomp qword ptr [data_00470d58]
    L_0040f3ea:
        fnstsw ax
    L_0040f3ec:
        test ah,41h
    L_0040f3ef:
        jne short L_0040f42d
    L_0040f3f1:
        mov eax,dword ptr [ebx+1444h]
    L_0040f3f7:
        test ah,8
    L_0040f3fa:
        je short L_0040f422
    L_0040f3fc:
        fld dword ptr [esp+1Ch]
    L_0040f400:
        push ecx
    L_0040f401:
        fsub dword ptr [data_00470b94]
    L_0040f407:
        fstp dword ptr [esp]
    L_0040f40a:
        call asm_Angle_Normalize_0044bc70
    L_0040f40f:
        fsubr dword ptr [data_00470b94]
    L_0040f415:
        push ecx
    L_0040f416:
        fstp dword ptr [esp]
    L_0040f419:
        call asm_Angle_Normalize_0044bc70
    L_0040f41e:
        fstp dword ptr [esp+1Ch]
    L_0040f422:
        mov eax,dword ptr [esp+1Ch]
    L_0040f426:
        push eax
    L_0040f427:
        push esi
    L_0040f428:
        call asm_Score_SetNormalizedAngle_00413170
    L_0040f42d:
        fld dword ptr [esp+18h]
    L_0040f431:
        fcomp qword ptr [data_00470d58]
    L_0040f437:
        fnstsw ax
    L_0040f439:
        test ah,41h
    L_0040f43c:
        jne short L_0040f445
    L_0040f43e:
        mov ecx,dword ptr [esp+18h]
    L_0040f442:
        mov dword ptr [esi+18h],ecx
    L_0040f445:
        and dword ptr [esi+28h],0FFFFFFFEh
    L_0040f449:
        xor eax,eax
    L_0040f44b:
        pop edi
    L_0040f44c:
        pop esi
    L_0040f44d:
        pop ebx
    L_0040f44e:
        mov ecx,dword ptr [esp+2C0h]
    L_0040f455:
        xor ecx,ebp
    L_0040f457:
        call asm_security_check_cookie_00458ea5
    L_0040f45c:
        mov esp,ebp
    L_0040f45e:
        pop ebp
    L_0040f45f:
        ret
    L_0040f460:
        cmp ax,11Dh
    L_0040f464:
        lea edi,[ebx+58h]
    L_0040f467:
        je asm_target_0040f4f9
    L_0040f46d:
        lea edi,[ebx+84h]
    L_0040f473:
        lea esi,[ebx+210h]
    L_0040f479:
        mov eax,dword ptr [edx+4]
    L_0040f47c:
        mov ecx,2
    L_0040f481:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f486:
        fstp dword ptr [esp+1Ch]
    L_0040f48a:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f490:
        mov eax,dword ptr [eax+4]
    L_0040f493:
        mov ecx,3
    L_0040f498:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f49d:
        fstp dword ptr [esp+18h]
    L_0040f4a1:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f4a7:
        mov edx,dword ptr [eax+4]
    L_0040f4aa:
        push 1
    L_0040f4ac:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040f4b1:
        fld dword ptr [esp+1Ch]
    L_0040f4b5:
        fcomp qword ptr [data_00470d58]
    L_0040f4bb:
        mov dword ptr [esi+38h],eax
    L_0040f4be:
        cmp eax,7
    L_0040f4c1:
        fnstsw ax
    L_0040f4c3:
        je short L_0040f52f
    L_0040f4c5:
        test ah,41h
    L_0040f4c8:
        jne short L_0040f504
    L_0040f4ca:
        mov eax,dword ptr [ebx+1444h]
    L_0040f4d0:
        fld dword ptr [esp+1Ch]
    L_0040f4d4:
        test ah,8
    L_0040f4d7:
        je short L_0040f507
    L_0040f4d9:
        fsub dword ptr [data_00470b94]
    L_0040f4df:
        push ecx
    L_0040f4e0:
        fstp dword ptr [esp]
    L_0040f4e3:
        call asm_Angle_Normalize_0044bc70
    L_0040f4e8:
        fsubr dword ptr [data_00470b94]
    L_0040f4ee:
        push ecx
    L_0040f4ef:
        fstp dword ptr [esp]
    L_0040f4f2:
        call asm_Angle_Normalize_0044bc70
    L_0040f4f7:
        jmp short L_0040f507
    L_0040f4f9:
        lea esi,[ebx+1D4h]
    L_0040f4ff:
        jmp asm_target_0040f479
    L_0040f504:
        fld dword ptr [edi+1Ch]
    L_0040f507:
        fstp dword ptr [esp+10h]
    L_0040f50b:
        fld dword ptr [esp+18h]
    L_0040f50f:
        fcomp qword ptr [data_00470d58]
    L_0040f515:
        fnstsw ax
    L_0040f517:
        test ah,41h
    L_0040f51a:
        jne short L_0040f526
    L_0040f51c:
        fld dword ptr [esp+18h]
    L_0040f520:
        fstp dword ptr [esp+14h]
    L_0040f524:
        jmp short L_0040f569
    L_0040f526:
        fld dword ptr [edi+18h]
    L_0040f529:
        fstp dword ptr [esp+14h]
    L_0040f52d:
        jmp short L_0040f569
    L_0040f52f:
        test ah,41h
    L_0040f532:
        jne short L_0040f53e
    L_0040f534:
        mov edx,dword ptr [esp+1Ch]
    L_0040f538:
        mov dword ptr [esp+10h],edx
    L_0040f53c:
        jmp short L_0040f546
    L_0040f53e:
        mov dword ptr [esp+10h],0
    L_0040f546:
        fld dword ptr [esp+18h]
    L_0040f54a:
        fcomp qword ptr [data_00470d58]
    L_0040f550:
        fnstsw ax
    L_0040f552:
        test ah,41h
    L_0040f555:
        jne short L_0040f561
    L_0040f557:
        mov eax,dword ptr [esp+18h]
    L_0040f55b:
        mov dword ptr [esp+14h],eax
    L_0040f55f:
        jmp short L_0040f569
    L_0040f561:
        mov dword ptr [esp+14h],0
    L_0040f569:
        mov ecx,dword ptr [edi+1Ch]
    L_0040f56c:
        mov edx,dword ptr [edi+18h]
    L_0040f56f:
        mov dword ptr [esp+30h],ecx
    L_0040f573:
        fld dword ptr [esp+30h]
    L_0040f577:
        fsub dword ptr [esp+10h]
    L_0040f57b:
        mov dword ptr [esp+34h],edx
    L_0040f57f:
        fabs
    L_0040f581:
        fcomp dword ptr [data_00470b18]
    L_0040f587:
        fnstsw ax
    L_0040f589:
        test ah,1
    L_0040f58c:
        jne short L_0040f5bb
    L_0040f58e:
        fld dword ptr [esp+30h]
    L_0040f592:
        fcomp dword ptr [esp+10h]
    L_0040f596:
        fnstsw ax
    L_0040f598:
        test ah,5
    L_0040f59b:
        jp short L_0040f5ad
    L_0040f59d:
        fld dword ptr [esp+30h]
    L_0040f5a1:
        fadd dword ptr [data_00470b14]
    L_0040f5a7:
        fstp dword ptr [esp+30h]
    L_0040f5ab:
        jmp short L_0040f5bb
    L_0040f5ad:
        fld dword ptr [esp+10h]
    L_0040f5b1:
        fadd dword ptr [data_00470b14]
    L_0040f5b7:
        fstp dword ptr [esp+10h]
    L_0040f5bb:
        mov ebx,dword ptr [ebx+14D8h]
    L_0040f5c1:
        mov edx,dword ptr [ebx+4]
    L_0040f5c4:
        push 0
    L_0040f5c6:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040f5cb:
        mov dword ptr [esi+34h],eax
    L_0040f5ce:
        mov eax,dword ptr [data_00491c20]
    L_0040f5d3:
        mov dword ptr [esi+10h],eax
    L_0040f5d6:
        mov ecx,dword ptr [data_00491c24]
    L_0040f5dc:
        mov dword ptr [esi+14h],ecx
    L_0040f5df:
        mov edx,dword ptr [data_00491c20]
    L_0040f5e5:
        mov ecx,dword ptr [esp+30h]
    L_0040f5e9:
        mov dword ptr [esi+18h],edx
    L_0040f5ec:
        mov edx,dword ptr [esp+34h]
    L_0040f5f0:
        jmp asm_target_0040fc07
    L_0040f5f5:
        cmp ax,120h
    L_0040f5f9:
        lea esi,[ebx+58h]
    L_0040f5fc:
        je short L_0040f604
    L_0040f5fe:
        lea esi,[ebx+84h]
    L_0040f604:
        mov eax,dword ptr [edx+4]
    L_0040f607:
        xor ecx,ecx
    L_0040f609:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f60e:
        fstp dword ptr [esp+18h]
    L_0040f612:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f618:
        mov eax,dword ptr [eax+4]
    L_0040f61b:
        mov ecx,1
    L_0040f620:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f625:
        fstp dword ptr [esp+1Ch]
    L_0040f629:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f62f:
        mov eax,dword ptr [eax+4]
    L_0040f632:
        mov ecx,2
    L_0040f637:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f63c:
        fstp dword ptr [esp+30h]
    L_0040f640:
        mov ebx,dword ptr [ebx+14D8h]
    L_0040f646:
        mov eax,dword ptr [ebx+4]
    L_0040f649:
        mov ecx,3
    L_0040f64e:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f653:
        fstp dword ptr [esp+10h]
    L_0040f657:
        test byte ptr [esi+28h],1
    L_0040f65b:
        jne short L_0040f672
    L_0040f65d:
        mov eax,esi
    L_0040f65f:
        mov ecx,dword ptr [eax]
    L_0040f661:
        lea edx,[esi+0Ch]
    L_0040f664:
        mov dword ptr [edx],ecx
    L_0040f666:
        mov ecx,dword ptr [eax+4]
    L_0040f669:
        mov eax,dword ptr [eax+8]
    L_0040f66c:
        mov dword ptr [edx+4],ecx
    L_0040f66f:
        mov dword ptr [edx+8],eax
    L_0040f672:
        fld dword ptr [esp+18h]
    L_0040f676:
        fcomp qword ptr [data_00470d58]
    L_0040f67c:
        fnstsw ax
    L_0040f67e:
        test ah,41h
    L_0040f681:
        jne short L_0040f68e
    L_0040f683:
        mov ecx,dword ptr [esp+18h]
    L_0040f687:
        push ecx
    L_0040f688:
        push esi
    L_0040f689:
        call asm_Score_SetNormalizedAngle_00413170
    L_0040f68e:
        fld dword ptr [esp+1Ch]
    L_0040f692:
        fcomp qword ptr [data_00470d58]
    L_0040f698:
        fnstsw ax
    L_0040f69a:
        test ah,41h
    L_0040f69d:
        jne short L_0040f6a6
    L_0040f69f:
        mov edx,dword ptr [esp+1Ch]
    L_0040f6a3:
        mov dword ptr [esi+18h],edx
    L_0040f6a6:
        fld dword ptr [esp+30h]
    L_0040f6aa:
        fcomp qword ptr [data_00470d58]
    L_0040f6b0:
        fnstsw ax
    L_0040f6b2:
        test ah,41h
    L_0040f6b5:
        jne short L_0040f6be
    L_0040f6b7:
        mov eax,dword ptr [esp+30h]
    L_0040f6bb:
        mov dword ptr [esi+20h],eax
    L_0040f6be:
        fld dword ptr [esp+10h]
    L_0040f6c2:
        fcomp qword ptr [data_00470d58]
    L_0040f6c8:
        fnstsw ax
    L_0040f6ca:
        test ah,41h
    L_0040f6cd:
        jne short L_0040f6d6
    L_0040f6cf:
        mov ecx,dword ptr [esp+10h]
    L_0040f6d3:
        mov dword ptr [esi+24h],ecx
    L_0040f6d6:
        or dword ptr [esi+28h],1
    L_0040f6da:
        xor eax,eax
    L_0040f6dc:
        pop edi
    L_0040f6dd:
        pop esi
    L_0040f6de:
        pop ebx
    L_0040f6df:
        mov ecx,dword ptr [esp+2C0h]
    L_0040f6e6:
        xor ecx,ebp
    L_0040f6e8:
        call asm_security_check_cookie_00458ea5
    L_0040f6ed:
        mov esp,ebp
    L_0040f6ef:
        pop ebp
    L_0040f6f0:
        ret
    L_0040f6f1:
        cmp ax,121h
    L_0040f6f5:
        lea ecx,[ebx+58h]
    L_0040f6f8:
        je short L_0040f700
    L_0040f6fa:
        lea ecx,[ebx+84h]
    L_0040f700:
        cmp ax,121h
    L_0040f704:
        mov dword ptr [esp+18h],ecx
    L_0040f708:
        lea edi,[ebx+1D4h]
    L_0040f70e:
        je short L_0040f789
    L_0040f710:
        lea edi,[ebx+210h]
    L_0040f716:
        lea esi,[ebx+288h]
    L_0040f71c:
        mov eax,dword ptr [edx+4]
    L_0040f71f:
        mov ecx,2
    L_0040f724:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f729:
        fstp dword ptr [esp+30h]
    L_0040f72d:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f733:
        mov eax,dword ptr [eax+4]
    L_0040f736:
        mov ecx,3
    L_0040f73b:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f740:
        fstp dword ptr [esp+10h]
    L_0040f744:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f74a:
        mov eax,dword ptr [eax+4]
    L_0040f74d:
        mov ecx,4
    L_0040f752:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f757:
        fstp dword ptr [esp+1Ch]
    L_0040f75b:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f761:
        mov eax,dword ptr [eax+4]
    L_0040f764:
        mov ecx,5
    L_0040f769:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f76e:
        fld dword ptr [esp+10h]
    L_0040f772:
        fcomp qword ptr [data_00470d58]
    L_0040f778:
        mov ecx,dword ptr [esp+18h]
    L_0040f77c:
        fnstsw ax
    L_0040f77e:
        test ah,41h
    L_0040f781:
        jne short L_0040f791
    L_0040f783:
        fld dword ptr [esp+10h]
    L_0040f787:
        jmp short L_0040f794
    L_0040f789:
        lea esi,[ebx+24Ch]
    L_0040f78f:
        jmp short L_0040f71c
    L_0040f791:
        fld dword ptr [ecx+18h]
    L_0040f794:
        fld dword ptr [esp+30h]
    L_0040f798:
        fcomp qword ptr [data_00470d58]
    L_0040f79e:
        fnstsw ax
    L_0040f7a0:
        test ah,41h
    L_0040f7a3:
        jne short L_0040f7ab
    L_0040f7a5:
        fld dword ptr [esp+30h]
    L_0040f7a9:
        jmp short L_0040f7ae
    L_0040f7ab:
        fld dword ptr [ecx+1Ch]
    L_0040f7ae:
        mov eax,dword ptr [ecx+18h]
    L_0040f7b1:
        fstp dword ptr [esp+3Ch]
    L_0040f7b5:
        mov edx,dword ptr [ecx+1Ch]
    L_0040f7b8:
        fstp dword ptr [esp+40h]
    L_0040f7bc:
        mov dword ptr [esp+34h],eax
    L_0040f7c0:
        mov dword ptr [esp+30h],edx
    L_0040f7c4:
        fcom qword ptr [data_00470d58]
    L_0040f7ca:
        fnstsw ax
    L_0040f7cc:
        test ah,41h
    L_0040f7cf:
        je short L_0040f7d6
    L_0040f7d1:
        fstp st(0)
    L_0040f7d3:
        fld dword ptr [ecx+24h]
    L_0040f7d6:
        fld dword ptr [esp+1Ch]
    L_0040f7da:
        fcomp qword ptr [data_00470d58]
    L_0040f7e0:
        fnstsw ax
    L_0040f7e2:
        test ah,41h
    L_0040f7e5:
        jne short L_0040f7ed
    L_0040f7e7:
        fld dword ptr [esp+1Ch]
    L_0040f7eb:
        jmp short L_0040f7f0
    L_0040f7ed:
        fld dword ptr [ecx+20h]
    L_0040f7f0:
        mov eax,dword ptr [ecx+24h]
    L_0040f7f3:
        fstp dword ptr [esp+24h]
    L_0040f7f7:
        mov edx,dword ptr [ecx+20h]
    L_0040f7fa:
        mov dword ptr [esp+20h],eax
    L_0040f7fe:
        fstp dword ptr [esp+28h]
    L_0040f802:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f808:
        mov dword ptr [esp+1Ch],edx
    L_0040f80c:
        mov edx,dword ptr [eax+4]
    L_0040f80f:
        push 0
    L_0040f811:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040f816:
        mov ebx,dword ptr [ebx+14D8h]
    L_0040f81c:
        mov edx,dword ptr [ebx+4]
    L_0040f81f:
        push 1
    L_0040f821:
        mov dword ptr [esp+14h],eax
    L_0040f825:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040f82a:
        mov ecx,dword ptr [esp+10h]
    L_0040f82e:
        mov dword ptr [edi+34h],ecx
    L_0040f831:
        mov edx,dword ptr [data_00491c20]
    L_0040f837:
        mov ebx,eax
    L_0040f839:
        mov dword ptr [edi+10h],edx
    L_0040f83c:
        mov eax,dword ptr [data_00491c24]
    L_0040f841:
        mov dword ptr [edi+14h],eax
    L_0040f844:
        mov ecx,dword ptr [data_00491c20]
    L_0040f84a:
        mov eax,dword ptr [esp+30h]
    L_0040f84e:
        mov dword ptr [edi+18h],ecx
    L_0040f851:
        mov edx,dword ptr [data_00491c24]
    L_0040f857:
        mov ecx,dword ptr [esp+34h]
    L_0040f85b:
        mov dword ptr [edi],eax
    L_0040f85d:
        mov eax,dword ptr [esp+40h]
    L_0040f861:
        mov dword ptr [edi+1Ch],edx
    L_0040f864:
        mov edx,dword ptr [esp+3Ch]
    L_0040f868:
        mov dword ptr [edi+0Ch],eax
    L_0040f86b:
        mov eax,edi
    L_0040f86d:
        mov dword ptr [edi+38h],ebx
    L_0040f870:
        mov dword ptr [edi+4],ecx
    L_0040f873:
        mov dword ptr [edi+8],edx
    L_0040f876:
        call asm_RecoveryTimer_Reset_00412db0
    L_0040f87b:
        mov ecx,dword ptr [esp+10h]
    L_0040f87f:
        mov dword ptr [esi+34h],ecx
    L_0040f882:
        mov edx,dword ptr [data_00491c20]
    L_0040f888:
        mov dword ptr [esi+10h],edx
    L_0040f88b:
        mov eax,dword ptr [data_00491c24]
    L_0040f890:
        mov dword ptr [esi+14h],eax
    L_0040f893:
        mov ecx,dword ptr [data_00491c20]
    L_0040f899:
        mov eax,dword ptr [esp+1Ch]
    L_0040f89d:
        mov dword ptr [esi+18h],ecx
    L_0040f8a0:
        mov edx,dword ptr [data_00491c24]
    L_0040f8a6:
        mov ecx,dword ptr [esp+20h]
    L_0040f8aa:
        mov dword ptr [esi],eax
    L_0040f8ac:
        mov eax,dword ptr [esp+28h]
    L_0040f8b0:
        mov dword ptr [esi+1Ch],edx
    L_0040f8b3:
        mov edx,dword ptr [esp+24h]
    L_0040f8b7:
        mov dword ptr [esi+0Ch],eax
    L_0040f8ba:
        mov eax,esi
    L_0040f8bc:
        mov dword ptr [esi+38h],ebx
    L_0040f8bf:
        mov dword ptr [esi+4],ecx
    L_0040f8c2:
        mov dword ptr [esi+8],edx
    L_0040f8c5:
        call asm_RecoveryTimer_Reset_00412db0
    L_0040f8ca:
        mov eax,dword ptr [esp+18h]
    L_0040f8ce:
        mov edx,eax
    L_0040f8d0:
        mov esi,dword ptr [edx]
    L_0040f8d2:
        lea ecx,[eax+0Ch]
    L_0040f8d5:
        mov dword ptr [ecx],esi
    L_0040f8d7:
        mov esi,dword ptr [edx+4]
    L_0040f8da:
        mov edx,dword ptr [edx+8]
    L_0040f8dd:
        mov dword ptr [ecx+4],esi
    L_0040f8e0:
        mov dword ptr [ecx+8],edx
    L_0040f8e3:
        or dword ptr [eax+28h],1
    L_0040f8e7:
        xor eax,eax
    L_0040f8e9:
        pop edi
    L_0040f8ea:
        pop esi
    L_0040f8eb:
        pop ebx
    L_0040f8ec:
        mov ecx,dword ptr [esp+2C0h]
    L_0040f8f3:
        xor ecx,ebp
    L_0040f8f5:
        call asm_security_check_cookie_00458ea5
    L_0040f8fa:
        mov esp,ebp
    L_0040f8fc:
        pop ebp
    L_0040f8fd:
        ret
    L_0040f8fe:
        cmp ax,12Ah
    L_0040f902:
        lea esi,[ebx+58h]
    L_0040f905:
        je short L_0040f90d
    L_0040f907:
        lea esi,[ebx+84h]
    L_0040f90d:
        mov eax,dword ptr [edx+4]
    L_0040f910:
        xor ecx,ecx
    L_0040f912:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f917:
        fstp dword ptr [esp+10h]
    L_0040f91b:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f921:
        mov eax,dword ptr [eax+4]
    L_0040f924:
        mov ecx,1
    L_0040f929:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f92e:
        fld dword ptr [esp+10h]
    L_0040f932:
        fcomp qword ptr [data_00470d58]
    L_0040f938:
        fnstsw ax
    L_0040f93a:
        test ah,41h
    L_0040f93d:
        jne short L_0040f946
    L_0040f93f:
        mov eax,dword ptr [esp+10h]
    L_0040f943:
        mov dword ptr [esi+0Ch],eax
    L_0040f946:
        fcom qword ptr [data_00470d58]
    L_0040f94c:
        fnstsw ax
    L_0040f94e:
        test ah,41h
    L_0040f951:
        jne short L_0040f958
    L_0040f953:
        fstp dword ptr [esi+10h]
    L_0040f956:
        jmp short L_0040f95a
    L_0040f958:
        fstp st(0)
    L_0040f95a:
        mov ecx,dword ptr [data_00477704]
    L_0040f960:
        mov edx,dword ptr [ecx+10h]
    L_0040f963:
        add edx,1068h
    L_0040f969:
        mov eax,dword ptr [edx]
    L_0040f96b:
        add ebx,58h
    L_0040f96e:
        mov dword ptr [ebx],eax
    L_0040f970:
        mov ecx,dword ptr [edx+4]
    L_0040f973:
        mov dword ptr [ebx+4],ecx
    L_0040f976:
        mov edx,dword ptr [edx+8]
    L_0040f979:
        mov dword ptr [ebx+8],edx
    L_0040f97c:
        xor eax,eax
    L_0040f97e:
        pop edi
    L_0040f97f:
        pop esi
    L_0040f980:
        pop ebx
    L_0040f981:
        mov ecx,dword ptr [esp+2C0h]
    L_0040f988:
        xor ecx,ebp
    L_0040f98a:
        call asm_security_check_cookie_00458ea5
    L_0040f98f:
        mov esp,ebp
    L_0040f991:
        pop ebp
    L_0040f992:
        ret
    L_0040f993:
        mov eax,dword ptr [data_00477704]
    L_0040f998:
        mov ecx,dword ptr [eax+10h]
    L_0040f99b:
        add ecx,1068h
    L_0040f9a1:
        mov edx,dword ptr [ecx]
    L_0040f9a3:
        add ebx,84h
    L_0040f9a9:
        mov dword ptr [ebx],edx
    L_0040f9ab:
        mov eax,dword ptr [ecx+4]
    L_0040f9ae:
        mov dword ptr [ebx+4],eax
    L_0040f9b1:
        mov ecx,dword ptr [ecx+8]
    L_0040f9b4:
        mov dword ptr [ebx+8],ecx
    L_0040f9b7:
        xor eax,eax
    L_0040f9b9:
        pop edi
    L_0040f9ba:
        pop esi
    L_0040f9bb:
        pop ebx
    L_0040f9bc:
        mov ecx,dword ptr [esp+2C0h]
    L_0040f9c3:
        xor ecx,ebp
    L_0040f9c5:
        call asm_security_check_cookie_00458ea5
    L_0040f9ca:
        mov esp,ebp
    L_0040f9cc:
        pop ebp
    L_0040f9cd:
        ret
    L_0040f9ce:
        or dword ptr [ebx+1444h],200h
    L_0040f9d8:
        mov eax,dword ptr [edx+4]
    L_0040f9db:
        xor ecx,ecx
    L_0040f9dd:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f9e2:
        fstp dword ptr [ebx+13ACh]
    L_0040f9e8:
        mov eax,dword ptr [ebx+14D8h]
    L_0040f9ee:
        mov eax,dword ptr [eax+4]
    L_0040f9f1:
        mov ecx,1
    L_0040f9f6:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040f9fb:
        fstp dword ptr [ebx+13B0h]
    L_0040fa01:
        mov eax,dword ptr [ebx+14D8h]
    L_0040fa07:
        mov eax,dword ptr [eax+4]
    L_0040fa0a:
        mov ecx,2
    L_0040fa0f:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040fa14:
        fstp dword ptr [ebx+13B4h]
    L_0040fa1a:
        mov eax,dword ptr [ebx+14D8h]
    L_0040fa20:
        mov eax,dword ptr [eax+4]
    L_0040fa23:
        mov ecx,3
    L_0040fa28:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040fa2d:
        fstp dword ptr [ebx+13B8h]
    L_0040fa33:
        xor eax,eax
    L_0040fa35:
        pop edi
    L_0040fa36:
        pop esi
    L_0040fa37:
        pop ebx
    L_0040fa38:
        mov ecx,dword ptr [esp+2C0h]
    L_0040fa3f:
        xor ecx,ebp
    L_0040fa41:
        call asm_security_check_cookie_00458ea5
    L_0040fa46:
        mov esp,ebp
    L_0040fa48:
        pop ebp
    L_0040fa49:
        ret
    L_0040fa4a:
        and dword ptr [ebx+1444h],0FFFFFDFFh
    L_0040fa54:
        xor eax,eax
    L_0040fa56:
        pop edi
    L_0040fa57:
        pop esi
    L_0040fa58:
        pop ebx
    L_0040fa59:
        mov ecx,dword ptr [esp+2C0h]
    L_0040fa60:
        xor ecx,ebp
    L_0040fa62:
        call asm_security_check_cookie_00458ea5
    L_0040fa67:
        mov esp,ebp
    L_0040fa69:
        pop ebp
    L_0040fa6a:
        ret
    L_0040fa6b:
        mov eax,dword ptr [edx+4]
    L_0040fa6e:
        xor ecx,ecx
    L_0040fa70:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040fa75:
        fld st(0)
    L_0040fa77:
        fmul st,st(1)
    L_0040fa79:
        fstp dword ptr [ebx+1454h]
    L_0040fa7f:
        jmp asm_target_00411d16
    L_0040fa84:
        cmp ax,124h
    L_0040fa88:
        lea edi,[ebx+58h]
    L_0040fa8b:
        je short L_0040facb
    L_0040fa8d:
        lea edi,[ebx+84h]
    L_0040fa93:
        lea esi,[ebx+210h]
    L_0040fa99:
        fld dword ptr [ebx+13B4h]
    L_0040fa9f:
        mov ecx,4918B0h
    L_0040faa4:
        fmul dword ptr [data_00470d40]
    L_0040faaa:
        fld dword ptr [ebx+13ACh]
    L_0040fab0:
        fsub st,st(1)
    L_0040fab2:
        fcomp dword ptr [ebx+2Ch]
    L_0040fab5:
        fnstsw ax
    L_0040fab7:
        test ah,41h
    L_0040faba:
        jne short L_0040fad3
    L_0040fabc:
        fstp st(0)
    L_0040fabe:
        call asm_Rng_NextFloatSigned_0044bb90
    L_0040fac3:
        fmul dword ptr [data_00470d50]
    L_0040fac9:
        jmp short L_0040fb39
    L_0040facb:
        lea esi,[ebx+1D4h]
    L_0040fad1:
        jmp short L_0040fa99
    L_0040fad3:
        fadd dword ptr [ebx+13ACh]
    L_0040fad9:
        fcomp dword ptr [ebx+2Ch]
    L_0040fadc:
        fnstsw ax
    L_0040fade:
        test ah,5
    L_0040fae1:
        jp short L_0040faf6
    L_0040fae3:
        call asm_Rng_NextFloatSigned_0044bb90
    L_0040fae8:
        fmul dword ptr [data_00470b18]
    L_0040faee:
        fmul dword ptr [data_00470cc4]
    L_0040faf4:
        jmp short L_0040fb2a
    L_0040faf6:
        fld dword ptr [ebx+2Ch]
    L_0040faf9:
        mov edx,dword ptr [data_00477834]
    L_0040faff:
        fcomp dword ptr [edx+3C0h]
    L_0040fb05:
        fnstsw ax
    L_0040fb07:
        test ah,5
    L_0040fb0a:
        jp short L_0040fb19
    L_0040fb0c:
        call asm_Rng_NextFloatSigned_0044bb90
    L_0040fb11:
        fmul dword ptr [data_00470b94]
    L_0040fb17:
        jmp short L_0040fb39
    L_0040fb19:
        call asm_Rng_NextFloatSigned_0044bb90
    L_0040fb1e:
        fmul dword ptr [data_00470b18]
    L_0040fb24:
        fmul dword ptr [data_00470b0c]
    L_0040fb2a:
        fadd dword ptr [data_00470b18]
    L_0040fb30:
        push ecx
    L_0040fb31:
        fstp dword ptr [esp]
    L_0040fb34:
        call asm_Angle_Normalize_0044bc70
    L_0040fb39:
        fstp dword ptr [esp+1Ch]
    L_0040fb3d:
        fld dword ptr [ebx+13B8h]
    L_0040fb43:
        fmul dword ptr [data_00470d40]
    L_0040fb49:
        fld dword ptr [ebx+13B0h]
    L_0040fb4f:
        fsub st,st(1)
    L_0040fb51:
        fcomp dword ptr [ebx+30h]
    L_0040fb54:
        fnstsw ax
    L_0040fb56:
        test ah,41h
    L_0040fb59:
        jne short L_0040fb65
    L_0040fb5b:
        fstp st(0)
    L_0040fb5d:
        fld dword ptr [esp+1Ch]
    L_0040fb61:
        fabs
    L_0040fb63:
        jmp short L_0040fb7d
    L_0040fb65:
        fadd dword ptr [ebx+13B0h]
    L_0040fb6b:
        fcomp dword ptr [ebx+30h]
    L_0040fb6e:
        fnstsw ax
    L_0040fb70:
        test ah,5
    L_0040fb73:
        jp short L_0040fb81
    L_0040fb75:
        fld dword ptr [esp+1Ch]
    L_0040fb79:
        fabs
    L_0040fb7b:
        fchs
    L_0040fb7d:
        fstp dword ptr [esp+1Ch]
    L_0040fb81:
        mov eax,dword ptr [ebx+14D8h]
    L_0040fb87:
        mov edx,dword ptr [eax+4]
    L_0040fb8a:
        push 1
    L_0040fb8c:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040fb91:
        cmp eax,7
    L_0040fb94:
        mov dword ptr [esi+38h],eax
    L_0040fb97:
        mov dword ptr [esp+14h],0
    L_0040fb9f:
        je short L_0040fbab
    L_0040fba1:
        mov eax,dword ptr [esp+1Ch]
    L_0040fba5:
        mov dword ptr [esp+10h],eax
    L_0040fba9:
        jmp short L_0040fbb3
    L_0040fbab:
        mov ecx,dword ptr [esp+1Ch]
    L_0040fbaf:
        mov dword ptr [esp+10h],ecx
    L_0040fbb3:
        mov eax,dword ptr [ebx+14D8h]
    L_0040fbb9:
        mov edx,dword ptr [esp+1Ch]
    L_0040fbbd:
        mov eax,dword ptr [eax+4]
    L_0040fbc0:
        mov ecx,2
    L_0040fbc5:
        mov dword ptr [esp+24h],edx
    L_0040fbc9:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040fbce:
        fstp dword ptr [esp+28h]
    L_0040fbd2:
        mov ebx,dword ptr [ebx+14D8h]
    L_0040fbd8:
        mov edx,dword ptr [ebx+4]
    L_0040fbdb:
        push 0
    L_0040fbdd:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040fbe2:
        mov dword ptr [esi+34h],eax
    L_0040fbe5:
        mov eax,dword ptr [data_00491c20]
    L_0040fbea:
        mov dword ptr [esi+10h],eax
    L_0040fbed:
        mov ecx,dword ptr [data_00491c24]
    L_0040fbf3:
        mov dword ptr [esi+14h],ecx
    L_0040fbf6:
        mov edx,dword ptr [data_00491c20]
    L_0040fbfc:
        mov ecx,dword ptr [esp+24h]
    L_0040fc00:
        mov dword ptr [esi+18h],edx
    L_0040fc03:
        mov edx,dword ptr [esp+28h]
    L_0040fc07:
        mov eax,dword ptr [data_00491c24]
    L_0040fc0c:
        mov dword ptr [esi+1Ch],eax
    L_0040fc0f:
        mov eax,dword ptr [esp+10h]
    L_0040fc13:
        mov dword ptr [esi],ecx
    L_0040fc15:
        mov ecx,dword ptr [esp+14h]
    L_0040fc19:
        mov dword ptr [esi+4],edx
    L_0040fc1c:
        mov dword ptr [esi+8],eax
    L_0040fc1f:
        mov eax,esi
    L_0040fc21:
        mov dword ptr [esi+0Ch],ecx
    L_0040fc24:
        call asm_RecoveryTimer_Reset_00412db0
    L_0040fc29:
        and dword ptr [edi+28h],0FFFFFFFEh
    L_0040fc2d:
        xor eax,eax
    L_0040fc2f:
        pop edi
    L_0040fc30:
        pop esi
    L_0040fc31:
        pop ebx
    L_0040fc32:
        mov ecx,dword ptr [esp+2C0h]
    L_0040fc39:
        xor ecx,ebp
    L_0040fc3b:
        call asm_security_check_cookie_00458ea5
    L_0040fc40:
        mov esp,ebp
    L_0040fc42:
        pop ebp
    L_0040fc43:
        ret
    L_0040fc44:
        mov edx,dword ptr [edx+4]
    L_0040fc47:
        push 2
    L_0040fc49:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040fc4e:
        mov esi,eax
    L_0040fc50:
        mov eax,dword ptr [ebx+14D8h]
    L_0040fc56:
        mov eax,dword ptr [eax+4]
    L_0040fc59:
        mov ecx,1
    L_0040fc5e:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040fc63:
        fstp dword ptr [esp+30h]
    L_0040fc67:
        mov edx,dword ptr [ebx+13C4h]
    L_0040fc6d:
        mov ebx,dword ptr [ebx+14D8h]
    L_0040fc73:
        mov dword ptr [esp+10h],edx
    L_0040fc77:
        mov edx,dword ptr [ebx+4]
    L_0040fc7a:
        push 0
    L_0040fc7c:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040fc81:
        fild dword ptr [esp+10h]
    L_0040fc85:
        mov ecx,dword ptr [data_0047770c]
    L_0040fc8b:
        mov dword ptr [ecx+eax*8+9E98h],esi
    L_0040fc92:
        fdivr dword ptr [esp+30h]
    L_0040fc96:
        fstp dword ptr [ecx+eax*8+9E94h]
    L_0040fc9d:
        xor eax,eax
    L_0040fc9f:
        pop edi
    L_0040fca0:
        pop esi
    L_0040fca1:
        pop ebx
    L_0040fca2:
        mov ecx,dword ptr [esp+2C0h]
    L_0040fca9:
        xor ecx,ebp
    L_0040fcab:
        call asm_security_check_cookie_00458ea5
    L_0040fcb0:
        mov esp,ebp
    L_0040fcb2:
        pop ebp
    L_0040fcb3:
        ret
    L_0040fcb4:
        mov eax,dword ptr [edx+4]
    L_0040fcb7:
        xor ecx,ecx
    L_0040fcb9:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040fcbe:
        fstp dword ptr [ebx+0B0h]
    L_0040fcc4:
        mov eax,dword ptr [ebx+14D8h]
    L_0040fcca:
        mov eax,dword ptr [eax+4]
    L_0040fccd:
        mov ecx,1
    L_0040fcd2:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040fcd7:
        fstp dword ptr [ebx+0B4h]
    L_0040fcdd:
        xor eax,eax
    L_0040fcdf:
        pop edi
    L_0040fce0:
        pop esi
    L_0040fce1:
        pop ebx
    L_0040fce2:
        mov ecx,dword ptr [esp+2C0h]
    L_0040fce9:
        xor ecx,ebp
    L_0040fceb:
        call asm_security_check_cookie_00458ea5
    L_0040fcf0:
        mov esp,ebp
    L_0040fcf2:
        pop ebp
    L_0040fcf3:
        ret
    L_0040fcf4:
        mov eax,dword ptr [edx+4]
    L_0040fcf7:
        xor ecx,ecx
    L_0040fcf9:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040fcfe:
        fstp dword ptr [ebx+0B8h]
    L_0040fd04:
        mov eax,dword ptr [ebx+14D8h]
    L_0040fd0a:
        mov eax,dword ptr [eax+4]
    L_0040fd0d:
        mov ecx,1
    L_0040fd12:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040fd17:
        fstp dword ptr [ebx+0BCh]
    L_0040fd1d:
        xor eax,eax
    L_0040fd1f:
        pop edi
    L_0040fd20:
        pop esi
    L_0040fd21:
        pop ebx
    L_0040fd22:
        mov ecx,dword ptr [esp+2C0h]
    L_0040fd29:
        xor ecx,ebp
    L_0040fd2b:
        call asm_security_check_cookie_00458ea5
    L_0040fd30:
        mov esp,ebp
    L_0040fd32:
        pop ebp
    L_0040fd33:
        ret
    L_0040fd34:
        mov edx,dword ptr [edx+4]
    L_0040fd37:
        push 0
    L_0040fd39:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040fd3e:
        mov ecx,dword ptr [ebx+1444h]
    L_0040fd44:
        or ecx,eax
    L_0040fd46:
        mov al,cl
    L_0040fd48:
        test al,10h
    L_0040fd4a:
        mov dword ptr [ebx+1444h],ecx
    L_0040fd50:
        je asm_target_00411d18
    L_0040fd56:
        lea esi,[ebx+0C0h]
    L_0040fd5c:
        mov edi,0Ah
    L_0040fd61:
        mov eax,esi
    L_0040fd63:
        call asm_AnimationManager_ClearFlag_004495e0
    L_0040fd68:
        add esi,4
    L_0040fd6b:
        dec edi
    L_0040fd6c:
        jne short L_0040fd61
    L_0040fd6e:
        xor eax,eax
    L_0040fd70:
        pop edi
    L_0040fd71:
        pop esi
    L_0040fd72:
        pop ebx
    L_0040fd73:
        mov ecx,dword ptr [esp+2C0h]
    L_0040fd7a:
        xor ecx,ebp
    L_0040fd7c:
        call asm_security_check_cookie_00458ea5
    L_0040fd81:
        mov esp,ebp
    L_0040fd83:
        pop ebp
    L_0040fd84:
        ret
    L_0040fd85:
        mov edx,dword ptr [edx+4]
    L_0040fd88:
        push 0
    L_0040fd8a:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040fd8f:
        mov ecx,dword ptr [ebx+1444h]
    L_0040fd95:
        not eax
    L_0040fd97:
        and ecx,eax
    L_0040fd99:
        mov al,cl
    L_0040fd9b:
        test al,10h
    L_0040fd9d:
        mov dword ptr [ebx+1444h],ecx
    L_0040fda3:
        jne asm_target_00411d18
    L_0040fda9:
        lea esi,[ebx+0C0h]
    L_0040fdaf:
        mov edi,0Ah
    L_0040fdb4:
        mov eax,esi
    L_0040fdb6:
        call asm_AnimationManager_SetFlagBit1_00449590
    L_0040fdbb:
        add esi,4
    L_0040fdbe:
        dec edi
    L_0040fdbf:
        jne short L_0040fdb4
    L_0040fdc1:
        xor eax,eax
    L_0040fdc3:
        pop edi
    L_0040fdc4:
        pop esi
    L_0040fdc5:
        pop ebx
    L_0040fdc6:
        mov ecx,dword ptr [esp+2C0h]
    L_0040fdcd:
        xor ecx,ebp
    L_0040fdcf:
        call asm_security_check_cookie_00458ea5
    L_0040fdd4:
        mov esp,ebp
    L_0040fdd6:
        pop ebp
    L_0040fdd7:
        ret
    L_0040fdd8:
        mov ecx,0Ch
    L_0040fddd:
        xor eax,eax
    L_0040fddf:
        lea edi,[ebx+13D0h]
    L_0040fde5:
        rep stosd
    L_0040fde7:
        pop edi
    L_0040fde8:
        pop esi
    L_0040fde9:
        pop ebx
    L_0040fdea:
        mov ecx,dword ptr [esp+2C0h]
    L_0040fdf1:
        xor ecx,ebp
    L_0040fdf3:
        call asm_security_check_cookie_00458ea5
    L_0040fdf8:
        mov esp,ebp
    L_0040fdfa:
        pop ebp
    L_0040fdfb:
        ret
    L_0040fdfc:
        mov edx,dword ptr [edx+4]
    L_0040fdff:
        push 0
    L_0040fe01:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040fe06:
        mov esi,eax
    L_0040fe08:
        mov eax,dword ptr [ebx+1444h]
    L_0040fe0e:
        test ah,ah
    L_0040fe10:
        jns short L_0040fe28
    L_0040fe12:
        cmp esi,1
    L_0040fe15:
        jne short L_0040fe1e
    L_0040fe17:
        mov esi,0Ah
    L_0040fe1c:
        jmp short L_0040fe28
    L_0040fe1e:
        cmp esi,4
    L_0040fe21:
        jne short L_0040fe28
    L_0040fe23:
        mov esi,0Bh
    L_0040fe28:
        mov eax,dword ptr [ebx+14D8h]
    L_0040fe2e:
        mov edx,dword ptr [eax+4]
    L_0040fe31:
        push 1
    L_0040fe33:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040fe38:
        mov dword ptr [ebx+esi*4+13CCh],eax
    L_0040fe3f:
        xor eax,eax
    L_0040fe41:
        pop edi
    L_0040fe42:
        pop esi
    L_0040fe43:
        pop ebx
    L_0040fe44:
        mov ecx,dword ptr [esp+2C0h]
    L_0040fe4b:
        xor ecx,ebp
    L_0040fe4d:
        call asm_security_check_cookie_00458ea5
    L_0040fe52:
        mov esp,ebp
    L_0040fe54:
        pop ebp
    L_0040fe55:
        ret
    L_0040fe56:
        mov eax,dword ptr [edx+4]
    L_0040fe59:
        mov ecx,1
    L_0040fe5e:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040fe63:
        fstp dword ptr [esp+10h]
    L_0040fe67:
        mov eax,dword ptr [ebx+14D8h]
    L_0040fe6d:
        mov eax,dword ptr [eax+4]
    L_0040fe70:
        xor ecx,ecx
    L_0040fe72:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0040fe77:
        fstp dword ptr [ebx+1400h]
    L_0040fe7d:
        mov eax,dword ptr [esp+10h]
    L_0040fe81:
        mov dword ptr [ebx+1404h],eax
    L_0040fe87:
        xor eax,eax
    L_0040fe89:
        pop edi
    L_0040fe8a:
        pop esi
    L_0040fe8b:
        pop ebx
    L_0040fe8c:
        mov ecx,dword ptr [esp+2C0h]
    L_0040fe93:
        xor ecx,ebp
    L_0040fe95:
        call asm_security_check_cookie_00458ea5
    L_0040fe9a:
        mov esp,ebp
    L_0040fe9c:
        pop ebp
    L_0040fe9d:
        ret
    L_0040fe9e:
        lea eax,[ebx+2Ch]
    L_0040fea1:
        lea edi,[ebx+13CCh]
    L_0040fea7:
        call asm_Recovery_ResetEmitter_0040c9a0
    L_0040feac:
        xor eax,eax
    L_0040feae:
        pop edi
    L_0040feaf:
        pop esi
    L_0040feb0:
        pop ebx
    L_0040feb1:
        mov ecx,dword ptr [esp+2C0h]
    L_0040feb8:
        xor ecx,ebp
    L_0040feba:
        call asm_security_check_cookie_00458ea5
    L_0040febf:
        mov esp,ebp
    L_0040fec1:
        pop ebp
    L_0040fec2:
        ret
    L_0040fec3:
        mov edx,dword ptr [edx+4]
    L_0040fec6:
        push 0
    L_0040fec8:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040fecd:
        mov ecx,dword ptr [ebx+1444h]
    L_0040fed3:
        test ch,ch
    L_0040fed5:
        jns short L_0040ff08
    L_0040fed7:
        cmp eax,1
    L_0040feda:
        jne short L_0040fefe
    L_0040fedc:
        mov eax,0Ah
    L_0040fee1:
        mov dword ptr [ebx+13CCh],eax
    L_0040fee7:
        xor eax,eax
    L_0040fee9:
        pop edi
    L_0040feea:
        pop esi
    L_0040feeb:
        pop ebx
    L_0040feec:
        mov ecx,dword ptr [esp+2C0h]
    L_0040fef3:
        xor ecx,ebp
    L_0040fef5:
        call asm_security_check_cookie_00458ea5
    L_0040fefa:
        mov esp,ebp
    L_0040fefc:
        pop ebp
    L_0040fefd:
        ret
    L_0040fefe:
        cmp eax,4
    L_0040ff01:
        jne short L_0040ff08
    L_0040ff03:
        mov eax,0Bh
    L_0040ff08:
        mov dword ptr [ebx+13CCh],eax
    L_0040ff0e:
        xor eax,eax
    L_0040ff10:
        pop edi
    L_0040ff11:
        pop esi
    L_0040ff12:
        pop ebx
    L_0040ff13:
        mov ecx,dword ptr [esp+2C0h]
    L_0040ff1a:
        xor ecx,ebp
    L_0040ff1c:
        call asm_security_check_cookie_00458ea5
    L_0040ff21:
        mov esp,ebp
    L_0040ff23:
        pop ebp
    L_0040ff24:
        ret
    L_0040ff25:
        mov edx,dword ptr [edx+4]
    L_0040ff28:
        xor esi,esi
    L_0040ff2a:
        push esi
    L_0040ff2b:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040ff30:
        mov dword ptr [ebx+13C0h],eax
    L_0040ff36:
        mov dword ptr [ebx+13C4h],eax
    L_0040ff3c:
        mov eax,dword ptr [data_0047770c]
    L_0040ff41:
        mov dword ptr [eax+9E94h],esi
    L_0040ff47:
        mov dword ptr [eax+9E98h],esi
    L_0040ff4d:
        mov dword ptr [eax+9E9Ch],esi
    L_0040ff53:
        mov dword ptr [eax+9EA0h],esi
    L_0040ff59:
        mov dword ptr [eax+9EA4h],esi
    L_0040ff5f:
        mov dword ptr [eax+9EA8h],esi
    L_0040ff65:
        mov dword ptr [eax+9EACh],esi
    L_0040ff6b:
        mov dword ptr [eax+9EB0h],esi
    L_0040ff71:
        mov ecx,dword ptr [ebx+13C0h]
    L_0040ff77:
        mov dword ptr [ebx+13C8h],ecx
    L_0040ff7d:
        xor eax,eax
    L_0040ff7f:
        pop edi
    L_0040ff80:
        pop esi
    L_0040ff81:
        pop ebx
    L_0040ff82:
        mov ecx,dword ptr [esp+2C0h]
    L_0040ff89:
        xor ecx,ebp
    L_0040ff8b:
        call asm_security_check_cookie_00458ea5
    L_0040ff90:
        mov esp,ebp
    L_0040ff92:
        pop ebp
    L_0040ff93:
        ret
    L_0040ff94:
        mov edx,dword ptr [edx+4]
    L_0040ff97:
        push 0
    L_0040ff99:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040ff9e:
        test eax,eax
    L_0040ffa0:
        jge short L_0040ffe0
    L_0040ffa2:
        mov eax,dword ptr [ebx+1444h]
    L_0040ffa8:
        test ah,ah
    L_0040ffaa:
        jns short L_0040ffbf
    L_0040ffac:
        mov edx,dword ptr [ebx+1450h]
    L_0040ffb2:
        mov eax,dword ptr [data_00477704]
    L_0040ffb7:
        mov dword ptr [eax+edx*4+10h],0
    L_0040ffbf:
        and dword ptr [ebx+1444h],0FFFF7FFFh
    L_0040ffc9:
        xor eax,eax
    L_0040ffcb:
        pop edi
    L_0040ffcc:
        pop esi
    L_0040ffcd:
        pop ebx
    L_0040ffce:
        mov ecx,dword ptr [esp+2C0h]
    L_0040ffd5:
        xor ecx,ebp
    L_0040ffd7:
        call asm_security_check_cookie_00458ea5
    L_0040ffdc:
        mov esp,ebp
    L_0040ffde:
        pop ebp
    L_0040ffdf:
        ret
    L_0040ffe0:
        mov ecx,dword ptr [ebx+1444h]
    L_0040ffe6:
        mov edx,dword ptr [data_00477704]
    L_0040ffec:
        or ecx,8000h
    L_0040fff2:
        mov dword ptr [ebx+1444h],ecx
    L_0040fff8:
        mov ecx,dword ptr [ebx+14D8h]
    L_0040fffe:
        mov dword ptr [edx+eax*4+10h],ecx
    L_00410002:
        mov dword ptr [ebx+1450h],eax
    L_00410008:
        xor eax,eax
    L_0041000a:
        pop edi
    L_0041000b:
        pop esi
    L_0041000c:
        pop ebx
    L_0041000d:
        mov ecx,dword ptr [esp+2C0h]
    L_00410014:
        xor ecx,ebp
    L_00410016:
        call asm_security_check_cookie_00458ea5
    L_0041001b:
        mov esp,ebp
    L_0041001d:
        pop ebp
    L_0041001e:
        ret
    L_0041001f:
        mov edx,dword ptr [edx+4]
    L_00410022:
        push 0
    L_00410024:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410029:
        push eax
    L_0041002a:
        lea eax,[ebx+141Ch]
    L_00410030:
        call asm_Player_SetSchedulerValue_00405410
    L_00410035:
        xor eax,eax
    L_00410037:
        pop edi
    L_00410038:
        pop esi
    L_00410039:
        pop ebx
    L_0041003a:
        mov ecx,dword ptr [esp+2C0h]
    L_00410041:
        xor ecx,ebp
    L_00410043:
        call asm_security_check_cookie_00458ea5
    L_00410048:
        mov esp,ebp
    L_0041004a:
        pop ebp
    L_0041004b:
        ret
    L_0041004c:
        mov edx,dword ptr [edx+4]
    L_0041004f:
        push 0
    L_00410051:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410056:
        push eax
    L_00410057:
        lea eax,[ebx+1430h]
    L_0041005d:
        call asm_Player_SetSchedulerValue_00405410
    L_00410062:
        xor eax,eax
    L_00410064:
        pop edi
    L_00410065:
        pop esi
    L_00410066:
        pop ebx
    L_00410067:
        mov ecx,dword ptr [esp+2C0h]
    L_0041006e:
        xor ecx,ebp
    L_00410070:
        call asm_security_check_cookie_00458ea5
    L_00410075:
        mov esp,ebp
    L_00410077:
        pop ebp
    L_00410078:
        ret
    L_00410079:
        mov eax,dword ptr [data_00477704]
    L_0041007e:
        push eax
    L_0041007f:
        call asm_Enemy_DeathSweepRetail_0040e6a0
    L_00410084:
        xor eax,eax
    L_00410086:
        pop edi
    L_00410087:
        pop esi
    L_00410088:
        pop ebx
    L_00410089:
        mov ecx,dword ptr [esp+2C0h]
    L_00410090:
        xor ecx,ebp
    L_00410092:
        call asm_security_check_cookie_00458ea5
    L_00410097:
        mov esp,ebp
    L_00410099:
        pop ebp
    L_0041009a:
        ret
    L_0041009b:
        mov eax,dword ptr [data_00474c74]
    L_004100a0:
        cmp eax,4
    L_004100a3:
        ja asm_target_00411d18
    L_004100a9:
        jmp dword ptr [eax*4+411F98h]
    L_004100b0:
        push 1
    L_004100b2:
        mov edx,dword ptr [edx+4]
    L_004100b5:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004100ba:
        mov esi,eax
    L_004100bc:
        xor ecx,ecx
    L_004100be:
        mov eax,ebx
    L_004100c0:
        call asm_ECL_ResolveIntDestination_00412a10
    L_004100c5:
        mov dword ptr [eax],esi
    L_004100c7:
        xor eax,eax
    L_004100c9:
        pop edi
    L_004100ca:
        pop esi
    L_004100cb:
        pop ebx
    L_004100cc:
        mov ecx,dword ptr [esp+2C0h]
    L_004100d3:
        xor ecx,ebp
    L_004100d5:
        call asm_security_check_cookie_00458ea5
    L_004100da:
        mov esp,ebp
    L_004100dc:
        pop ebp
    L_004100dd:
        ret
    L_004100de:
        push 2
    L_004100e0:
        jmp short L_004100b2
    L_004100e2:
        push 3
    L_004100e4:
        jmp short L_004100b2
    L_004100e6:
        push 4
    L_004100e8:
        jmp short L_004100b2
    L_004100ea:
        mov eax,dword ptr [data_00474c74]
    L_004100ef:
        cmp eax,4
    L_004100f2:
        ja asm_target_00411d18
    L_004100f8:
        jmp dword ptr [eax*4+411FACh]
    L_004100ff:
        mov eax,dword ptr [edx+4]
    L_00410102:
        jmp asm_target_0041194c
    L_00410107:
        mov eax,dword ptr [edx+4]
    L_0041010a:
        mov ecx,3
    L_0041010f:
        jmp asm_target_00411951
    L_00410114:
        mov ecx,4
    L_00410119:
        jmp asm_target_00411909
    L_0041011e:
        mov eax,dword ptr [edx+4]
    L_00410121:
        mov ecx,4
    L_00410126:
        jmp asm_target_00411951
    L_0041012b:
        mov edx,dword ptr [edx+4]
    L_0041012e:
        push 0
    L_00410130:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410135:
        mov esi,eax
    L_00410137:
        mov edx,esi
    L_00410139:
        imul edx,210h
    L_0041013f:
        add edx,ebx
    L_00410141:
        xor eax,eax
    L_00410143:
        lea edi,[edx+2C4h]
    L_00410149:
        mov ecx,84h
    L_0041014e:
        rep stosd
    L_00410150:
        mov ecx,1
    L_00410155:
        mov word ptr [edx+4B8h],cx
    L_0041015c:
        mov word ptr [edx+4BAh],cx
    L_00410163:
        mov dword ptr [edx+2D4h],eax
    L_00410169:
        mov dword ptr [edx+2DCh],40000000h
    L_00410173:
        mov dword ptr [edx+4C4h],7
    L_0041017d:
        mov dword ptr [edx+4C8h],18h
    L_00410187:
        mov dword ptr [edx+4C0h],203h
    L_00410191:
        lea ecx,[esi+esi*2+4D1h]
    L_00410198:
        lea edx,[esi+esi*2]
    L_0041019b:
        mov dword ptr [ebx+ecx*4],eax
    L_0041019e:
        mov dword ptr [ebx+edx*4+1348h],eax
    L_004101a5:
        pop edi
    L_004101a6:
        pop esi
    L_004101a7:
        pop ebx
    L_004101a8:
        mov ecx,dword ptr [esp+2C0h]
    L_004101af:
        xor ecx,ebp
    L_004101b1:
        call asm_security_check_cookie_00458ea5
    L_004101b6:
        mov esp,ebp
    L_004101b8:
        pop ebp
    L_004101b9:
        ret
    L_004101ba:
        mov edx,dword ptr [edx+4]
    L_004101bd:
        push 1
    L_004101bf:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004101c4:
        mov esi,eax
    L_004101c6:
        mov eax,dword ptr [ebx+14D8h]
    L_004101cc:
        mov edx,dword ptr [eax+4]
    L_004101cf:
        push 0
    L_004101d1:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004101d6:
        imul esi,210h
    L_004101dc:
        imul eax,210h
    L_004101e2:
        lea edi,[eax+ebx+2C4h]
    L_004101e9:
        lea esi,[esi+ebx+2C4h]
    L_004101f0:
        mov ecx,84h
    L_004101f5:
        rep movsd
    L_004101f7:
        xor eax,eax
    L_004101f9:
        pop edi
    L_004101fa:
        pop esi
    L_004101fb:
        pop ebx
    L_004101fc:
        mov ecx,dword ptr [esp+2C0h]
    L_00410203:
        xor ecx,ebp
    L_00410205:
        call asm_security_check_cookie_00458ea5
    L_0041020a:
        mov esp,ebp
    L_0041020c:
        pop ebp
    L_0041020d:
        ret
    L_0041020e:
        mov edx,dword ptr [edx+4]
    L_00410211:
        push 0
    L_00410213:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410218:
        lea ecx,[eax+eax*2+4D1h]
    L_0041021f:
        imul eax,210h
    L_00410225:
        fld dword ptr [ebx+ecx*4]
    L_00410228:
        fadd dword ptr [ebx+2Ch]
    L_0041022b:
        fstp dword ptr [esp+24h]
    L_0041022f:
        fld dword ptr [ebx+ecx*4+4]
    L_00410233:
        fadd dword ptr [ebx+30h]
    L_00410236:
        mov esi,dword ptr [esp+24h]
    L_0041023a:
        lea ecx,[ebx+ecx*4]
    L_0041023d:
        fstp dword ptr [esp+28h]
    L_00410241:
        lea edx,[eax+ebx]
    L_00410244:
        fld dword ptr [ecx+8]
    L_00410247:
        lea ecx,[edx+2C8h]
    L_0041024d:
        fadd dword ptr [ebx+34h]
    L_00410250:
        mov eax,ecx
    L_00410252:
        mov dword ptr [eax],esi
    L_00410254:
        mov esi,dword ptr [esp+28h]
    L_00410258:
        fstp dword ptr [esp+2Ch]
    L_0041025c:
        mov dword ptr [eax+4],esi
    L_0041025f:
        mov esi,dword ptr [esp+2Ch]
    L_00410263:
        fld dword ptr [data_00470b04]
    L_00410269:
        mov dword ptr [eax+8],esi
    L_0041026c:
        fld dword ptr [ebx+1454h]
    L_00410272:
        fucompp
    L_00410274:
        fnstsw ax
    L_00410276:
        test ah,44h
    L_00410279:
        jnp short L_004102b2
    L_0041027b:
        mov eax,dword ptr [data_00477834]
    L_00410280:
        fld dword ptr [ecx+4]
    L_00410283:
        fsub dword ptr [eax+3C4h]
    L_00410289:
        fld dword ptr [ecx]
    L_0041028b:
        fsub dword ptr [eax+3C0h]
    L_00410291:
        fld st(0)
    L_00410293:
        fmul st,st(1)
    L_00410295:
        fld st(2)
    L_00410297:
        fmul st,st(3)
    L_00410299:
        faddp st(1),st
    L_0041029b:
        fld dword ptr [ebx+1454h]
    L_004102a1:
        fcompp
    L_004102a3:
        fnstsw ax
    L_004102a5:
        fstp st(0)
    L_004102a7:
        test ah,41h
    L_004102aa:
        fstp st(0)
    L_004102ac:
        jp asm_target_00411d18
    L_004102b2:
        mov ecx,dword ptr [data_004776f0]
    L_004102b8:
        lea eax,[edx+2C4h]
    L_004102be:
        push ecx
    L_004102bf:
        call asm_EnemyGrid_ScanCellsRetail_004073e0
    L_004102c4:
        xor eax,eax
    L_004102c6:
        pop edi
    L_004102c7:
        pop esi
    L_004102c8:
        pop ebx
    L_004102c9:
        mov ecx,dword ptr [esp+2C0h]
    L_004102d0:
        xor ecx,ebp
    L_004102d2:
        call asm_security_check_cookie_00458ea5
    L_004102d7:
        mov esp,ebp
    L_004102d9:
        pop ebp
    L_004102da:
        ret
    L_004102db:
        mov edx,dword ptr [edx+4]
    L_004102de:
        push 0
    L_004102e0:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004102e5:
        imul eax,210h
    L_004102eb:
        mov ecx,dword ptr [ebx+14D8h]
    L_004102f1:
        mov edx,dword ptr [ecx+4]
    L_004102f4:
        push 1
    L_004102f6:
        lea esi,[eax+ebx]
    L_004102f9:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004102fe:
        mov word ptr [esi+2C4h],ax
    L_00410305:
        mov ebx,dword ptr [ebx+14D8h]
    L_0041030b:
        mov edx,dword ptr [ebx+4]
    L_0041030e:
        push 2
    L_00410310:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410315:
        mov word ptr [esi+2C6h],ax
    L_0041031c:
        xor eax,eax
    L_0041031e:
        pop edi
    L_0041031f:
        pop esi
    L_00410320:
        pop ebx
    L_00410321:
        mov ecx,dword ptr [esp+2C0h]
    L_00410328:
        xor ecx,ebp
    L_0041032a:
        call asm_security_check_cookie_00458ea5
    L_0041032f:
        mov esp,ebp
    L_00410331:
        pop ebp
    L_00410332:
        ret
    L_00410333:
        mov edx,dword ptr [edx+4]
    L_00410336:
        push 0
    L_00410338:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0041033d:
        mov esi,eax
    L_0041033f:
        mov eax,dword ptr [ebx+14D8h]
    L_00410345:
        mov eax,dword ptr [eax+4]
    L_00410348:
        mov ecx,1
    L_0041034d:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00410352:
        lea edx,[esi+esi*2+4D1h]
    L_00410359:
        fstp dword ptr [ebx+edx*4]
    L_0041035c:
        mov eax,dword ptr [ebx+14D8h]
    L_00410362:
        mov eax,dword ptr [eax+4]
    L_00410365:
        mov ecx,2
    L_0041036a:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0041036f:
        lea eax,[esi+esi*2]
    L_00410372:
        fstp dword ptr [ebx+eax*4+1348h]
    L_00410379:
        xor eax,eax
    L_0041037b:
        pop edi
    L_0041037c:
        pop esi
    L_0041037d:
        pop ebx
    L_0041037e:
        mov ecx,dword ptr [esp+2C0h]
    L_00410385:
        xor ecx,ebp
    L_00410387:
        call asm_security_check_cookie_00458ea5
    L_0041038c:
        mov esp,ebp
    L_0041038e:
        pop ebp
    L_0041038f:
        ret
    L_00410390:
        mov edx,dword ptr [edx+4]
    L_00410393:
        push 0
    L_00410395:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0041039a:
        imul eax,210h
    L_004103a0:
        mov edx,dword ptr [ebx+14D8h]
    L_004103a6:
        lea esi,[eax+ebx]
    L_004103a9:
        mov eax,dword ptr [edx+4]
    L_004103ac:
        mov ecx,1
    L_004103b1:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004103b6:
        mov ecx,2
    L_004103bb:
        fstp dword ptr [esi+2D4h]
    L_004103c1:
        mov ebx,dword ptr [ebx+14D8h]
    L_004103c7:
        mov eax,dword ptr [ebx+4]
    L_004103ca:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004103cf:
        fstp dword ptr [esi+2D8h]
    L_004103d5:
        xor eax,eax
    L_004103d7:
        pop edi
    L_004103d8:
        pop esi
    L_004103d9:
        pop ebx
    L_004103da:
        mov ecx,dword ptr [esp+2C0h]
    L_004103e1:
        xor ecx,ebp
    L_004103e3:
        call asm_security_check_cookie_00458ea5
    L_004103e8:
        mov esp,ebp
    L_004103ea:
        pop ebp
    L_004103eb:
        ret
    L_004103ec:
        mov edx,dword ptr [edx+4]
    L_004103ef:
        push 0
    L_004103f1:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004103f6:
        imul eax,210h
    L_004103fc:
        mov edx,dword ptr [ebx+14D8h]
    L_00410402:
        lea esi,[eax+ebx]
    L_00410405:
        mov eax,dword ptr [edx+4]
    L_00410408:
        mov ecx,1
    L_0041040d:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00410412:
        fstp dword ptr [esi+2DCh]
    L_00410418:
        mov ebx,dword ptr [ebx+14D8h]
    L_0041041e:
        mov eax,dword ptr [ebx+4]
    L_00410421:
        mov ecx,2
    L_00410426:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0041042b:
        fstp dword ptr [esi+2E0h]
    L_00410431:
        xor eax,eax
    L_00410433:
        pop edi
    L_00410434:
        pop esi
    L_00410435:
        pop ebx
    L_00410436:
        mov ecx,dword ptr [esp+2C0h]
    L_0041043d:
        xor ecx,ebp
    L_0041043f:
        call asm_security_check_cookie_00458ea5
    L_00410444:
        mov esp,ebp
    L_00410446:
        pop ebp
    L_00410447:
        ret
    L_00410448:
        mov edx,dword ptr [edx+4]
    L_0041044b:
        push 0
    L_0041044d:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410452:
        imul eax,210h
    L_00410458:
        mov ecx,dword ptr [ebx+14D8h]
    L_0041045e:
        mov edx,dword ptr [ecx+4]
    L_00410461:
        push 1
    L_00410463:
        lea esi,[eax+ebx]
    L_00410466:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0041046b:
        mov word ptr [esi+4B8h],ax
    L_00410472:
        mov ebx,dword ptr [ebx+14D8h]
    L_00410478:
        mov edx,dword ptr [ebx+4]
    L_0041047b:
        push 2
    L_0041047d:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410482:
        mov word ptr [esi+4BAh],ax
    L_00410489:
        xor eax,eax
    L_0041048b:
        pop edi
    L_0041048c:
        pop esi
    L_0041048d:
        pop ebx
    L_0041048e:
        mov ecx,dword ptr [esp+2C0h]
    L_00410495:
        xor ecx,ebp
    L_00410497:
        call asm_security_check_cookie_00458ea5
    L_0041049c:
        mov esp,ebp
    L_0041049e:
        pop ebp
    L_0041049f:
        ret
    L_004104a0:
        mov edx,dword ptr [edx+4]
    L_004104a3:
        push 0
    L_004104a5:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004104aa:
        mov esi,eax
    L_004104ac:
        mov eax,dword ptr [data_00474c74]
    L_004104b1:
        test eax,eax
    L_004104b3:
        jne short L_004104bc
    L_004104b5:
        mov ecx,1
    L_004104ba:
        jmp short L_004104d7
    L_004104bc:
        cmp eax,1
    L_004104bf:
        jne short L_004104c8
    L_004104c1:
        mov ecx,2
    L_004104c6:
        jmp short L_004104d7
    L_004104c8:
        cmp eax,2
    L_004104cb:
        mov ecx,3
    L_004104d0:
        je short L_004104d7
    L_004104d2:
        mov ecx,4
    L_004104d7:
        mov eax,dword ptr [ebx+14D8h]
    L_004104dd:
        mov eax,dword ptr [eax+4]
    L_004104e0:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004104e5:
        imul esi,210h
    L_004104eb:
        fstp dword ptr [esi+ebx+2DCh]
    L_004104f2:
        mov eax,dword ptr [data_00474c74]
    L_004104f7:
        add esi,ebx
    L_004104f9:
        test eax,eax
    L_004104fb:
        jne short L_00410504
    L_004104fd:
        mov ecx,5
    L_00410502:
        jmp short L_0041051f
    L_00410504:
        cmp eax,1
    L_00410507:
        jne short L_00410510
    L_00410509:
        mov ecx,6
    L_0041050e:
        jmp short L_0041051f
    L_00410510:
        cmp eax,2
    L_00410513:
        mov ecx,7
    L_00410518:
        je short L_0041051f
    L_0041051a:
        mov ecx,8
    L_0041051f:
        mov ebx,dword ptr [ebx+14D8h]
    L_00410525:
        mov eax,dword ptr [ebx+4]
    L_00410528:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0041052d:
        fstp dword ptr [esi+2E0h]
    L_00410533:
        xor eax,eax
    L_00410535:
        pop edi
    L_00410536:
        pop esi
    L_00410537:
        pop ebx
    L_00410538:
        mov ecx,dword ptr [esp+2C0h]
    L_0041053f:
        xor ecx,ebp
    L_00410541:
        call asm_security_check_cookie_00458ea5
    L_00410546:
        mov esp,ebp
    L_00410548:
        pop ebp
    L_00410549:
        ret
    L_0041054a:
        mov edx,dword ptr [edx+4]
    L_0041054d:
        push 0
    L_0041054f:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410554:
        mov esi,eax
    L_00410556:
        mov eax,dword ptr [data_00474c74]
    L_0041055b:
        test eax,eax
    L_0041055d:
        jne short L_00410563
    L_0041055f:
        push 1
    L_00410561:
        jmp short L_00410577
    L_00410563:
        cmp eax,1
    L_00410566:
        jne short L_0041056c
    L_00410568:
        push 2
    L_0041056a:
        jmp short L_00410577
    L_0041056c:
        cmp eax,2
    L_0041056f:
        jne short L_00410575
    L_00410571:
        push 3
    L_00410573:
        jmp short L_00410577
    L_00410575:
        push 4
    L_00410577:
        mov eax,dword ptr [ebx+14D8h]
    L_0041057d:
        mov edx,dword ptr [eax+4]
    L_00410580:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410585:
        imul esi,210h
    L_0041058b:
        add esi,ebx
    L_0041058d:
        mov word ptr [esi+4B8h],ax
    L_00410594:
        mov eax,dword ptr [data_00474c74]
    L_00410599:
        test eax,eax
    L_0041059b:
        jne short L_004105a1
    L_0041059d:
        push 5
    L_0041059f:
        jmp short L_004105b5
    L_004105a1:
        cmp eax,1
    L_004105a4:
        jne short L_004105aa
    L_004105a6:
        push 6
    L_004105a8:
        jmp short L_004105b5
    L_004105aa:
        cmp eax,2
    L_004105ad:
        jne short L_004105b3
    L_004105af:
        push 7
    L_004105b1:
        jmp short L_004105b5
    L_004105b3:
        push 8
    L_004105b5:
        mov ebx,dword ptr [ebx+14D8h]
    L_004105bb:
        mov edx,dword ptr [ebx+4]
    L_004105be:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004105c3:
        mov word ptr [esi+4BAh],ax
    L_004105ca:
        xor eax,eax
    L_004105cc:
        pop edi
    L_004105cd:
        pop esi
    L_004105ce:
        pop ebx
    L_004105cf:
        mov ecx,dword ptr [esp+2C0h]
    L_004105d6:
        xor ecx,ebp
    L_004105d8:
        call asm_security_check_cookie_00458ea5
    L_004105dd:
        mov esp,ebp
    L_004105df:
        pop ebp
    L_004105e0:
        ret
    L_004105e1:
        mov edx,dword ptr [edx+4]
    L_004105e4:
        push 0
    L_004105e6:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004105eb:
        mov ecx,dword ptr [data_00474c98]
    L_004105f1:
        cmp ecx,200h
    L_004105f7:
        jge asm_target_004106da
    L_004105fd:
        imul eax,210h
    L_00410603:
        cmp ecx,0FFFFFE00h
    L_00410609:
        jmp asm_target_00410738
    L_0041060e:
        mov edx,dword ptr [edx+4]
    L_00410611:
        push 0
    L_00410613:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410618:
        mov ecx,dword ptr [data_00474c98]
    L_0041061e:
        cmp ecx,258h
    L_00410624:
        jl short L_00410678
    L_00410626:
        mov edx,dword ptr [ebx+14D8h]
    L_0041062c:
        imul eax,210h
    L_00410632:
        lea esi,[eax+ebx]
    L_00410635:
        mov eax,dword ptr [edx+4]
    L_00410638:
        mov ecx,9
    L_0041063d:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00410642:
        mov ecx,0Ah
    L_00410647:
        fstp dword ptr [esi+2DCh]
    L_0041064d:
        mov ebx,dword ptr [ebx+14D8h]
    L_00410653:
        mov eax,dword ptr [ebx+4]
    L_00410656:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0041065b:
        fstp dword ptr [esi+2E0h]
    L_00410661:
        xor eax,eax
    L_00410663:
        pop edi
    L_00410664:
        pop esi
    L_00410665:
        pop ebx
    L_00410666:
        mov ecx,dword ptr [esp+2C0h]
    L_0041066d:
        xor ecx,ebp
    L_0041066f:
        call asm_security_check_cookie_00458ea5
    L_00410674:
        mov esp,ebp
    L_00410676:
        pop ebp
    L_00410677:
        ret
    L_00410678:
        cmp ecx,0C8h
    L_0041067e:
        jl short L_004106d2
    L_00410680:
        mov edx,dword ptr [ebx+14D8h]
    L_00410686:
        imul eax,210h
    L_0041068c:
        lea esi,[eax+ebx]
    L_0041068f:
        mov eax,dword ptr [edx+4]
    L_00410692:
        mov ecx,7
    L_00410697:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0041069c:
        mov ecx,8
    L_004106a1:
        fstp dword ptr [esi+2DCh]
    L_004106a7:
        mov ebx,dword ptr [ebx+14D8h]
    L_004106ad:
        mov eax,dword ptr [ebx+4]
    L_004106b0:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004106b5:
        fstp dword ptr [esi+2E0h]
    L_004106bb:
        xor eax,eax
    L_004106bd:
        pop edi
    L_004106be:
        pop esi
    L_004106bf:
        pop ebx
    L_004106c0:
        mov ecx,dword ptr [esp+2C0h]
    L_004106c7:
        xor ecx,ebp
    L_004106c9:
        call asm_security_check_cookie_00458ea5
    L_004106ce:
        mov esp,ebp
    L_004106d0:
        pop ebp
    L_004106d1:
        ret
    L_004106d2:
        cmp ecx,0FFFFFF38h
    L_004106d8:
        jl short L_0041072c
    L_004106da:
        mov edx,dword ptr [ebx+14D8h]
    L_004106e0:
        imul eax,210h
    L_004106e6:
        lea esi,[eax+ebx]
    L_004106e9:
        mov eax,dword ptr [edx+4]
    L_004106ec:
        mov ecx,5
    L_004106f1:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004106f6:
        mov ecx,6
    L_004106fb:
        fstp dword ptr [esi+2DCh]
    L_00410701:
        mov ebx,dword ptr [ebx+14D8h]
    L_00410707:
        mov eax,dword ptr [ebx+4]
    L_0041070a:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0041070f:
        fstp dword ptr [esi+2E0h]
    L_00410715:
        xor eax,eax
    L_00410717:
        pop edi
    L_00410718:
        pop esi
    L_00410719:
        pop ebx
    L_0041071a:
        mov ecx,dword ptr [esp+2C0h]
    L_00410721:
        xor ecx,ebp
    L_00410723:
        call asm_security_check_cookie_00458ea5
    L_00410728:
        mov esp,ebp
    L_0041072a:
        pop ebp
    L_0041072b:
        ret
    L_0041072c:
        imul eax,210h
    L_00410732:
        cmp ecx,0FFFFFDA8h
    L_00410738:
        mov edx,dword ptr [ebx+14D8h]
    L_0041073e:
        lea esi,[eax+ebx]
    L_00410741:
        mov eax,dword ptr [edx+4]
    L_00410744:
        jl asm_target_00410408
    L_0041074a:
        mov ecx,3
    L_0041074f:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00410754:
        fstp dword ptr [esi+2DCh]
    L_0041075a:
        mov ebx,dword ptr [ebx+14D8h]
    L_00410760:
        mov eax,dword ptr [ebx+4]
    L_00410763:
        mov ecx,4
    L_00410768:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0041076d:
        fstp dword ptr [esi+2E0h]
    L_00410773:
        xor eax,eax
    L_00410775:
        pop edi
    L_00410776:
        pop esi
    L_00410777:
        pop ebx
    L_00410778:
        mov ecx,dword ptr [esp+2C0h]
    L_0041077f:
        xor ecx,ebp
    L_00410781:
        call asm_security_check_cookie_00458ea5
    L_00410786:
        mov esp,ebp
    L_00410788:
        pop ebp
    L_00410789:
        ret
    L_0041078a:
        mov edx,dword ptr [edx+4]
    L_0041078d:
        push 0
    L_0041078f:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410794:
        mov esi,eax
    L_00410796:
        mov eax,dword ptr [ebx+14D8h]
    L_0041079c:
        mov eax,dword ptr [eax+4]
    L_0041079f:
        mov ecx,1
    L_004107a4:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004107a9:
        fstp dword ptr [esp+10h]
    L_004107ad:
        mov eax,dword ptr [ebx+14D8h]
    L_004107b3:
        mov eax,dword ptr [eax+4]
    L_004107b6:
        mov ecx,2
    L_004107bb:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004107c0:
        fstp dword ptr [esp+30h]
    L_004107c4:
        mov eax,dword ptr [ebx+14D8h]
    L_004107ca:
        mov eax,dword ptr [eax+4]
    L_004107cd:
        mov ecx,3
    L_004107d2:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004107d7:
        fstp dword ptr [esp+18h]
    L_004107db:
        mov eax,dword ptr [ebx+14D8h]
    L_004107e1:
        mov eax,dword ptr [eax+4]
    L_004107e4:
        mov ecx,4
    L_004107e9:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004107ee:
        fild dword ptr [data_00474c98]
    L_004107f4:
        imul esi,210h
    L_004107fa:
        fadd dword ptr [data_00470d4c]
    L_00410800:
        fld dword ptr [esp+18h]
    L_00410804:
        fsub dword ptr [esp+10h]
    L_00410808:
        fmulp st(1),st
    L_0041080a:
        lea eax,[esi+ebx]
    L_0041080d:
        fmul dword ptr [data_00470d48]
    L_00410813:
        fadd dword ptr [esp+10h]
    L_00410817:
        fstp dword ptr [eax+2DCh]
    L_0041081d:
        fild dword ptr [data_00474c98]
    L_00410823:
        fadd dword ptr [data_00470d4c]
    L_00410829:
        fxch
    L_0041082b:
        fsub dword ptr [esp+30h]
    L_0041082f:
        fmulp st(1),st
    L_00410831:
        fmul dword ptr [data_00470d48]
    L_00410837:
        fadd dword ptr [esp+30h]
    L_0041083b:
        fstp dword ptr [eax+2E0h]
    L_00410841:
        xor eax,eax
    L_00410843:
        pop edi
    L_00410844:
        pop esi
    L_00410845:
        pop ebx
    L_00410846:
        mov ecx,dword ptr [esp+2C0h]
    L_0041084d:
        xor ecx,ebp
    L_0041084f:
        call asm_security_check_cookie_00458ea5
    L_00410854:
        mov esp,ebp
    L_00410856:
        pop ebp
    L_00410857:
        ret
    L_00410858:
        mov edx,dword ptr [edx+4]
    L_0041085b:
        push 0
    L_0041085d:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410862:
        mov ecx,dword ptr [data_00474c98]
    L_00410868:
        cmp ecx,200h
    L_0041086e:
        jge asm_target_00410949
    L_00410874:
        imul eax,210h
    L_0041087a:
        cmp ecx,0FFFFFE00h
    L_00410880:
        jmp asm_target_004109a3
    L_00410885:
        mov edx,dword ptr [edx+4]
    L_00410888:
        push 0
    L_0041088a:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0041088f:
        mov ecx,dword ptr [data_00474c98]
    L_00410895:
        cmp ecx,258h
    L_0041089b:
        jl short L_004108eb
    L_0041089d:
        mov ecx,dword ptr [ebx+14D8h]
    L_004108a3:
        imul eax,210h
    L_004108a9:
        mov edx,dword ptr [ecx+4]
    L_004108ac:
        push 9
    L_004108ae:
        lea esi,[eax+ebx]
    L_004108b1:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004108b6:
        mov word ptr [esi+4B8h],ax
    L_004108bd:
        mov ebx,dword ptr [ebx+14D8h]
    L_004108c3:
        mov edx,dword ptr [ebx+4]
    L_004108c6:
        push 0Ah
    L_004108c8:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004108cd:
        mov word ptr [esi+4BAh],ax
    L_004108d4:
        xor eax,eax
    L_004108d6:
        pop edi
    L_004108d7:
        pop esi
    L_004108d8:
        pop ebx
    L_004108d9:
        mov ecx,dword ptr [esp+2C0h]
    L_004108e0:
        xor ecx,ebp
    L_004108e2:
        call asm_security_check_cookie_00458ea5
    L_004108e7:
        mov esp,ebp
    L_004108e9:
        pop ebp
    L_004108ea:
        ret
    L_004108eb:
        cmp ecx,0C8h
    L_004108f1:
        jl short L_00410941
    L_004108f3:
        mov ecx,dword ptr [ebx+14D8h]
    L_004108f9:
        imul eax,210h
    L_004108ff:
        mov edx,dword ptr [ecx+4]
    L_00410902:
        push 7
    L_00410904:
        lea esi,[eax+ebx]
    L_00410907:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0041090c:
        mov word ptr [esi+4B8h],ax
    L_00410913:
        mov ebx,dword ptr [ebx+14D8h]
    L_00410919:
        mov edx,dword ptr [ebx+4]
    L_0041091c:
        push 8
    L_0041091e:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410923:
        mov word ptr [esi+4BAh],ax
    L_0041092a:
        xor eax,eax
    L_0041092c:
        pop edi
    L_0041092d:
        pop esi
    L_0041092e:
        pop ebx
    L_0041092f:
        mov ecx,dword ptr [esp+2C0h]
    L_00410936:
        xor ecx,ebp
    L_00410938:
        call asm_security_check_cookie_00458ea5
    L_0041093d:
        mov esp,ebp
    L_0041093f:
        pop ebp
    L_00410940:
        ret
    L_00410941:
        cmp ecx,0FFFFFF38h
    L_00410947:
        jl short L_00410997
    L_00410949:
        mov ecx,dword ptr [ebx+14D8h]
    L_0041094f:
        imul eax,210h
    L_00410955:
        mov edx,dword ptr [ecx+4]
    L_00410958:
        push 5
    L_0041095a:
        lea esi,[eax+ebx]
    L_0041095d:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410962:
        mov word ptr [esi+4B8h],ax
    L_00410969:
        mov ebx,dword ptr [ebx+14D8h]
    L_0041096f:
        mov edx,dword ptr [ebx+4]
    L_00410972:
        push 6
    L_00410974:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410979:
        mov word ptr [esi+4BAh],ax
    L_00410980:
        xor eax,eax
    L_00410982:
        pop edi
    L_00410983:
        pop esi
    L_00410984:
        pop ebx
    L_00410985:
        mov ecx,dword ptr [esp+2C0h]
    L_0041098c:
        xor ecx,ebp
    L_0041098e:
        call asm_security_check_cookie_00458ea5
    L_00410993:
        mov esp,ebp
    L_00410995:
        pop ebp
    L_00410996:
        ret
    L_00410997:
        imul eax,210h
    L_0041099d:
        cmp ecx,0FFFFFDA8h
    L_004109a3:
        mov ecx,dword ptr [ebx+14D8h]
    L_004109a9:
        mov edx,dword ptr [ecx+4]
    L_004109ac:
        lea esi,[eax+ebx]
    L_004109af:
        jl short L_004109ed
    L_004109b1:
        push 3
    L_004109b3:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004109b8:
        mov word ptr [esi+4B8h],ax
    L_004109bf:
        mov ebx,dword ptr [ebx+14D8h]
    L_004109c5:
        mov edx,dword ptr [ebx+4]
    L_004109c8:
        push 4
    L_004109ca:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004109cf:
        mov word ptr [esi+4BAh],ax
    L_004109d6:
        xor eax,eax
    L_004109d8:
        pop edi
    L_004109d9:
        pop esi
    L_004109da:
        pop ebx
    L_004109db:
        mov ecx,dword ptr [esp+2C0h]
    L_004109e2:
        xor ecx,ebp
    L_004109e4:
        call asm_security_check_cookie_00458ea5
    L_004109e9:
        mov esp,ebp
    L_004109eb:
        pop ebp
    L_004109ec:
        ret
    L_004109ed:
        push 1
    L_004109ef:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004109f4:
        mov word ptr [esi+4B8h],ax
    L_004109fb:
        mov ebx,dword ptr [ebx+14D8h]
    L_00410a01:
        mov edx,dword ptr [ebx+4]
    L_00410a04:
        push 2
    L_00410a06:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410a0b:
        mov word ptr [esi+4BAh],ax
    L_00410a12:
        xor eax,eax
    L_00410a14:
        pop edi
    L_00410a15:
        pop esi
    L_00410a16:
        pop ebx
    L_00410a17:
        mov ecx,dword ptr [esp+2C0h]
    L_00410a1e:
        xor ecx,ebp
    L_00410a20:
        call asm_security_check_cookie_00458ea5
    L_00410a25:
        mov esp,ebp
    L_00410a27:
        pop ebp
    L_00410a28:
        ret
    L_00410a29:
        mov edx,dword ptr [edx+4]
    L_00410a2c:
        push 0
    L_00410a2e:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410a33:
        mov esi,eax
    L_00410a35:
        mov eax,dword ptr [ebx+14D8h]
    L_00410a3b:
        mov edx,dword ptr [eax+4]
    L_00410a3e:
        push 1
    L_00410a40:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410a45:
        mov edi,eax
    L_00410a47:
        mov eax,dword ptr [ebx+14D8h]
    L_00410a4d:
        mov edx,dword ptr [eax+4]
    L_00410a50:
        push 2
    L_00410a52:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410a57:
        mov dword ptr [esp+30h],eax
    L_00410a5b:
        mov eax,dword ptr [ebx+14D8h]
    L_00410a61:
        mov edx,dword ptr [eax+4]
    L_00410a64:
        push 3
    L_00410a66:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410a6b:
        mov dword ptr [esp+10h],eax
    L_00410a6f:
        mov eax,dword ptr [ebx+14D8h]
    L_00410a75:
        mov edx,dword ptr [eax+4]
    L_00410a78:
        push 4
    L_00410a7a:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410a7f:
        imul esi,210h
    L_00410a85:
        mov edx,dword ptr [data_00474c98]
    L_00410a8b:
        mov ecx,eax
    L_00410a8d:
        mov eax,dword ptr [esp+10h]
    L_00410a91:
        sub eax,edi
    L_00410a93:
        add edx,400h
    L_00410a99:
        imul eax,edx
    L_00410a9c:
        cdq
    L_00410a9d:
        and edx,7FFh
    L_00410aa3:
        add eax,edx
    L_00410aa5:
        sar eax,0Bh
    L_00410aa8:
        add eax,edi
    L_00410aaa:
        mov word ptr [esi+ebx+4B8h],ax
    L_00410ab2:
        mov edx,dword ptr [data_00474c98]
    L_00410ab8:
        add esi,ebx
    L_00410aba:
        mov eax,ecx
    L_00410abc:
        mov ecx,dword ptr [esp+30h]
    L_00410ac0:
        sub eax,ecx
    L_00410ac2:
        add edx,400h
    L_00410ac8:
        imul eax,edx
    L_00410acb:
        cdq
    L_00410acc:
        and edx,7FFh
    L_00410ad2:
        add eax,edx
    L_00410ad4:
        sar eax,0Bh
    L_00410ad7:
        add eax,ecx
    L_00410ad9:
        mov word ptr [esi+4BAh],ax
    L_00410ae0:
        xor eax,eax
    L_00410ae2:
        pop edi
    L_00410ae3:
        pop esi
    L_00410ae4:
        pop ebx
    L_00410ae5:
        mov ecx,dword ptr [esp+2C0h]
    L_00410aec:
        xor ecx,ebp
    L_00410aee:
        call asm_security_check_cookie_00458ea5
    L_00410af3:
        mov esp,ebp
    L_00410af5:
        pop ebp
    L_00410af6:
        ret
    L_00410af7:
        mov edx,dword ptr [edx+4]
    L_00410afa:
        push 0
    L_00410afc:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410b01:
        mov esi,eax
    L_00410b03:
        mov eax,dword ptr [ebx+14D8h]
    L_00410b09:
        mov edx,dword ptr [eax+4]
    L_00410b0c:
        push 1
    L_00410b0e:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410b13:
        imul esi,210h
    L_00410b19:
        mov word ptr [esi+ebx+4BCh],ax
    L_00410b21:
        xor eax,eax
    L_00410b23:
        pop edi
    L_00410b24:
        pop esi
    L_00410b25:
        pop ebx
    L_00410b26:
        mov ecx,dword ptr [esp+2C0h]
    L_00410b2d:
        xor ecx,ebp
    L_00410b2f:
        call asm_security_check_cookie_00458ea5
    L_00410b34:
        mov esp,ebp
    L_00410b36:
        pop ebp
    L_00410b37:
        ret
    L_00410b38:
        mov edx,dword ptr [edx+4]
    L_00410b3b:
        push 0
    L_00410b3d:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410b42:
        imul eax,210h
    L_00410b48:
        mov ecx,dword ptr [ebx+14D8h]
    L_00410b4e:
        mov edx,dword ptr [ecx+4]
    L_00410b51:
        push 1
    L_00410b53:
        lea esi,[eax+ebx]
    L_00410b56:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410b5b:
        mov dword ptr [esi+4C4h],eax
    L_00410b61:
        mov ebx,dword ptr [ebx+14D8h]
    L_00410b67:
        mov edx,dword ptr [ebx+4]
    L_00410b6a:
        push 2
    L_00410b6c:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410b71:
        mov dword ptr [esi+4C8h],eax
    L_00410b77:
        xor eax,eax
    L_00410b79:
        pop edi
    L_00410b7a:
        pop esi
    L_00410b7b:
        pop ebx
    L_00410b7c:
        mov ecx,dword ptr [esp+2C0h]
    L_00410b83:
        xor ecx,ebp
    L_00410b85:
        call asm_security_check_cookie_00458ea5
    L_00410b8a:
        mov esp,ebp
    L_00410b8c:
        pop ebp
    L_00410b8d:
        ret
    L_00410b8e:
        mov edx,dword ptr [edx+4]
    L_00410b91:
        push 0
    L_00410b93:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410b98:
        mov esi,eax
    L_00410b9a:
        mov eax,dword ptr [ebx+14D8h]
    L_00410ba0:
        mov edx,dword ptr [eax+4]
    L_00410ba3:
        push 1
    L_00410ba5:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410baa:
        imul esi,16h
    L_00410bad:
        mov ecx,dword ptr [ebx+14D8h]
    L_00410bb3:
        mov edx,dword ptr [ecx+4]
    L_00410bb6:
        lea edi,[esi+eax]
    L_00410bb9:
        lea eax,[edi+edi*2]
    L_00410bbc:
        push 2
    L_00410bbe:
        lea esi,[ebx+eax*8]
    L_00410bc1:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410bc6:
        mov dword ptr [esi+2F8h],eax
    L_00410bcc:
        mov eax,dword ptr [ebx+14D8h]
    L_00410bd2:
        mov edx,dword ptr [eax+4]
    L_00410bd5:
        push 3
    L_00410bd7:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410bdc:
        mov dword ptr [esi+2F4h],eax
    L_00410be2:
        mov eax,dword ptr [ebx+14D8h]
    L_00410be8:
        mov edx,dword ptr [eax+4]
    L_00410beb:
        push 4
    L_00410bed:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410bf2:
        mov dword ptr [esi+2ECh],eax
    L_00410bf8:
        mov eax,dword ptr [ebx+14D8h]
    L_00410bfe:
        mov edx,dword ptr [eax+4]
    L_00410c01:
        push 5
    L_00410c03:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410c08:
        mov dword ptr [esi+2F0h],eax
    L_00410c0e:
        mov eax,dword ptr [ebx+14D8h]
    L_00410c14:
        mov eax,dword ptr [eax+4]
    L_00410c17:
        mov ecx,6
    L_00410c1c:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00410c21:
        fstp dword ptr [esi+2E4h]
    L_00410c27:
        mov eax,dword ptr [ebx+14D8h]
    L_00410c2d:
        mov eax,dword ptr [eax+4]
    L_00410c30:
        mov ecx,7
    L_00410c35:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00410c3a:
        lea ecx,[edi+edi*2+5Dh]
    L_00410c3e:
        fstp dword ptr [ebx+ecx*8]
    L_00410c41:
        xor eax,eax
    L_00410c43:
        pop edi
    L_00410c44:
        pop esi
    L_00410c45:
        pop ebx
    L_00410c46:
        mov ecx,dword ptr [esp+2C0h]
    L_00410c4d:
        xor ecx,ebp
    L_00410c4f:
        call asm_security_check_cookie_00458ea5
    L_00410c54:
        mov esp,ebp
    L_00410c56:
        pop ebp
    L_00410c57:
        ret
    L_00410c58:
        push 0
    L_00410c5a:
        lea eax,[ebx+11Ch]
    L_00410c60:
        call asm_Player_SetSchedulerValue_00405410
    L_00410c65:
        xor eax,eax
    L_00410c67:
        pop edi
    L_00410c68:
        pop esi
    L_00410c69:
        pop ebx
    L_00410c6a:
        mov ecx,dword ptr [esp+2C0h]
    L_00410c71:
        xor ecx,ebp
    L_00410c73:
        call asm_security_check_cookie_00458ea5
    L_00410c78:
        mov esp,ebp
    L_00410c7a:
        pop ebp
    L_00410c7b:
        ret
    L_00410c7c:
        mov edx,dword ptr [edx+4]
    L_00410c7f:
        push 2
    L_00410c81:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410c86:
        mov esi,eax
    L_00410c88:
        mov eax,dword ptr [ebx+14D8h]
    L_00410c8e:
        mov edx,dword ptr [eax+4]
    L_00410c91:
        push 1
    L_00410c93:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410c98:
        mov dword ptr [esp+10h],eax
    L_00410c9c:
        mov eax,dword ptr [ebx+14D8h]
    L_00410ca2:
        mov edx,dword ptr [eax+4]
    L_00410ca5:
        push 0
    L_00410ca7:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410cac:
        mov edi,dword ptr [esp+1Ch]
    L_00410cb0:
        mov ecx,dword ptr [esp+10h]
    L_00410cb4:
        push esi
    L_00410cb5:
        mov esi,dword ptr [ebx+14D8h]
    L_00410cbb:
        add edi,20h
    L_00410cbe:
        mov edx,eax
    L_00410cc0:
        call asm_Ecl_SetResourceSlot_00412720
    L_00410cc5:
        xor eax,eax
    L_00410cc7:
        pop edi
    L_00410cc8:
        pop esi
    L_00410cc9:
        pop ebx
    L_00410cca:
        mov ecx,dword ptr [esp+2C0h]
    L_00410cd1:
        xor ecx,ebp
    L_00410cd3:
        call asm_security_check_cookie_00458ea5
    L_00410cd8:
        mov esp,ebp
    L_00410cda:
        pop ebp
    L_00410cdb:
        ret
    L_00410cdc:
        mov edx,dword ptr [edx+4]
    L_00410cdf:
        push 0
    L_00410ce1:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410ce6:
        mov edx,dword ptr [ebx+14D8h]
    L_00410cec:
        add eax,24Ah
    L_00410cf1:
        add esi,18h
    L_00410cf4:
        shl eax,4
    L_00410cf7:
        mov dword ptr [eax+edx],esi
    L_00410cfa:
        xor eax,eax
    L_00410cfc:
        pop edi
    L_00410cfd:
        pop esi
    L_00410cfe:
        pop ebx
    L_00410cff:
        mov ecx,dword ptr [esp+2C0h]
    L_00410d06:
        xor ecx,ebp
    L_00410d08:
        call asm_security_check_cookie_00458ea5
    L_00410d0d:
        mov esp,ebp
    L_00410d0f:
        pop ebp
    L_00410d10:
        ret
    L_00410d11:
        mov ebx,dword ptr [data_004776f0]
    L_00410d17:
        push 1
    L_00410d19:
        call asm_FUN_00408210_00408210
    L_00410d1e:
        mov eax,dword ptr [data_0047781c]
    L_00410d23:
        mov ebx,1
    L_00410d28:
        call asm_FUN_0041c850_0041c850
    L_00410d2d:
        xor eax,eax
    L_00410d2f:
        pop edi
    L_00410d30:
        pop esi
    L_00410d31:
        pop ebx
    L_00410d32:
        mov ecx,dword ptr [esp+2C0h]
    L_00410d39:
        xor ecx,ebp
    L_00410d3b:
        call asm_security_check_cookie_00458ea5
    L_00410d40:
        mov esp,ebp
    L_00410d42:
        pop ebp
    L_00410d43:
        ret
    L_00410d44:
        mov edx,dword ptr [edx+4]
    L_00410d47:
        push 0
    L_00410d49:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410d4e:
        mov ecx,dword ptr [ebx+2Ch]
    L_00410d51:
        push ecx
    L_00410d52:
        mov ebx,eax
    L_00410d54:
        mov esi,492590h
    L_00410d59:
        call asm_FUN_0043dd10_0043dd10
    L_00410d5e:
        xor eax,eax
    L_00410d60:
        pop edi
    L_00410d61:
        pop esi
    L_00410d62:
        pop ebx
    L_00410d63:
        mov ecx,dword ptr [esp+2C0h]
    L_00410d6a:
        xor ecx,ebp
    L_00410d6c:
        call asm_security_check_cookie_00458ea5
    L_00410d71:
        mov esp,ebp
    L_00410d73:
        pop ebp
    L_00410d74:
        ret
    L_00410d75:
        mov edx,dword ptr [edx+4]
    L_00410d78:
        push 2
    L_00410d7a:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410d7f:
        mov esi,eax
    L_00410d81:
        mov eax,dword ptr [ebx+14D8h]
    L_00410d87:
        mov edx,dword ptr [eax+4]
    L_00410d8a:
        push 1
    L_00410d8c:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410d91:
        mov ebx,dword ptr [ebx+14D8h]
    L_00410d97:
        mov edx,dword ptr [ebx+4]
    L_00410d9a:
        push 0
    L_00410d9c:
        push esi
    L_00410d9d:
        push eax
    L_00410d9e:
        push 0
    L_00410da0:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410da5:
        push eax
    L_00410da6:
        push 1
    L_00410da8:
        mov ebx,31h
    L_00410dad:
        call asm_AsciiManager_CreateRetail_0043c8b0
    L_00410db2:
        xor eax,eax
    L_00410db4:
        pop edi
    L_00410db5:
        pop esi
    L_00410db6:
        pop ebx
    L_00410db7:
        mov ecx,dword ptr [esp+2C0h]
    L_00410dbe:
        xor ecx,ebp
    L_00410dc0:
        call asm_security_check_cookie_00458ea5
    L_00410dc5:
        mov esp,ebp
    L_00410dc7:
        pop ebp
    L_00410dc8:
        ret
    L_00410dc9:
        mov edx,dword ptr [edx+4]
    L_00410dcc:
        push 0
    L_00410dce:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410dd3:
        mov edi,dword ptr [data_0047770c]
    L_00410dd9:
        mov esi,eax
    L_00410ddb:
        call asm_FUN_00415db0_00415db0
    L_00410de0:
        mov ebx,dword ptr [data_004776f0]
    L_00410de6:
        push 0
    L_00410de8:
        call asm_FUN_00408210_00408210
    L_00410ded:
        mov eax,dword ptr [data_0047781c]
    L_00410df2:
        xor ebx,ebx
    L_00410df4:
        call asm_FUN_0041c850_0041c850
    L_00410df9:
        mov edx,dword ptr [data_00477704]
    L_00410dff:
        push edx
    L_00410e00:
        call asm_Enemy_DeathSweepRetail_0040e6a0
    L_00410e05:
        xor eax,eax
    L_00410e07:
        pop edi
    L_00410e08:
        pop esi
    L_00410e09:
        pop ebx
    L_00410e0a:
        mov ecx,dword ptr [esp+2C0h]
    L_00410e11:
        xor ecx,ebp
    L_00410e13:
        call asm_security_check_cookie_00458ea5
    L_00410e18:
        mov esp,ebp
    L_00410e1a:
        pop ebp
    L_00410e1b:
        ret
    L_00410e1c:
        mov eax,dword ptr [data_0047770c]
    L_00410e21:
        mov eax,dword ptr [eax+9EB8h]
    L_00410e27:
        test eax,eax
    L_00410e29:
        je asm_target_00411d18
    L_00410e2f:
        mov ecx,dword ptr [eax+78h]
    L_00410e32:
        test ecx,ecx
    L_00410e34:
        jne asm_target_00411d18
    L_00410e3a:
        or eax,0FFFFFFFFh
    L_00410e3d:
        pop edi
    L_00410e3e:
        pop esi
    L_00410e3f:
        pop ebx
    L_00410e40:
        mov ecx,dword ptr [esp+2C0h]
    L_00410e47:
        xor ecx,ebp
    L_00410e49:
        call asm_security_check_cookie_00458ea5
    L_00410e4e:
        mov esp,ebp
    L_00410e50:
        pop ebp
    L_00410e51:
        ret
    L_00410e52:
        mov ecx,dword ptr [data_00477704]
    L_00410e58:
        mov eax,dword ptr [ecx+10h]
    L_00410e5b:
        test eax,eax
    L_00410e5d:
        je asm_target_00411d18
    L_00410e63:
        or eax,0FFFFFFFFh
    L_00410e66:
        pop edi
    L_00410e67:
        pop esi
    L_00410e68:
        pop ebx
    L_00410e69:
        mov ecx,dword ptr [esp+2C0h]
    L_00410e70:
        xor ecx,ebp
    L_00410e72:
        call asm_security_check_cookie_00458ea5
    L_00410e77:
        mov esp,ebp
    L_00410e79:
        pop ebp
    L_00410e7a:
        ret
    L_00410e7b:
        lea ecx,[esi+20h]
    L_00410e7e:
        mov esi,dword ptr [esi+1Ch]
    L_00410e81:
        xor edi,edi
    L_00410e83:
        test esi,esi
    L_00410e85:
        mov al,77h
    L_00410e87:
        mov byte ptr [esp+3Bh],7
    L_00410e8c:
        mov dword ptr [esp+30h],esi
    L_00410e90:
        jle short L_00410ec8
    L_00410e92:
        lea esi,[esp+248h]
    L_00410e99:
        sub ecx,esi
    L_00410e9b:
        mov dword ptr [esp+10h],ecx
    L_00410e9f:
        nop
    L_00410ea0:
        mov ecx,dword ptr [esp+10h]
    L_00410ea4:
        lea esi,[esp+edi+248h]
    L_00410eab:
        mov cl,byte ptr [ecx+esi]
    L_00410eae:
        xor cl,al
    L_00410eb0:
        mov byte ptr [esi],cl
    L_00410eb2:
        mov cl,byte ptr [esp+3Bh]
    L_00410eb6:
        add al,cl
    L_00410eb8:
        add cl,10h
    L_00410ebb:
        mov byte ptr [esp+3Bh],cl
    L_00410ebf:
        mov ecx,dword ptr [esp+30h]
    L_00410ec3:
        inc edi
    L_00410ec4:
        cmp edi,ecx
    L_00410ec6:
        jl short L_00410ea0
    L_00410ec8:
        mov edx,dword ptr [edx+4]
    L_00410ecb:
        push 0
    L_00410ecd:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410ed2:
        mov edx,dword ptr [esp+1Ch]
    L_00410ed6:
        mov esi,eax
    L_00410ed8:
        movsx eax,word ptr [edx+4]
    L_00410edc:
        sub eax,165h
    L_00410ee1:
        je short L_00410f00
    L_00410ee3:
        dec eax
    L_00410ee4:
        je short L_00410ef4
    L_00410ee6:
        dec eax
    L_00410ee7:
        jne short L_00410f06
    L_00410ee9:
        mov eax,dword ptr [data_00474c74]
    L_00410eee:
        lea esi,[esi+eax-2]
    L_00410ef2:
        jmp short L_00410f06
    L_00410ef4:
        mov ecx,dword ptr [data_00474c74]
    L_00410efa:
        lea esi,[esi+ecx-1]
    L_00410efe:
        jmp short L_00410f06
    L_00410f00:
        add esi,dword ptr [data_00474c74]
    L_00410f06:
        mov eax,dword ptr [ebx+14D8h]
    L_00410f0c:
        mov edx,dword ptr [eax+4]
    L_00410f0f:
        push 2
    L_00410f11:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410f16:
        mov ebx,dword ptr [ebx+14D8h]
    L_00410f1c:
        mov edx,dword ptr [ebx+4]
    L_00410f1f:
        push 1
    L_00410f21:
        mov dword ptr [esp+14h],eax
    L_00410f25:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410f2a:
        push eax
    L_00410f2b:
        mov eax,dword ptr [data_004776f4]
    L_00410f30:
        lea edx,[esp+24Ch]
    L_00410f37:
        push edx
    L_00410f38:
        push esi
    L_00410f39:
        push eax
    L_00410f3a:
        call asm_FUN_00409280_00409280
    L_00410f3f:
        xor eax,eax
    L_00410f41:
        pop edi
    L_00410f42:
        pop esi
    L_00410f43:
        pop ebx
    L_00410f44:
        mov ecx,dword ptr [esp+2C0h]
    L_00410f4b:
        xor ecx,ebp
    L_00410f4d:
        call asm_security_check_cookie_00458ea5
    L_00410f52:
        mov esp,ebp
    L_00410f54:
        pop ebp
    L_00410f55:
        ret
    L_00410f56:
        mov eax,dword ptr [data_004776f4]
    L_00410f5b:
        call asm_FUN_00409c00_00409c00
    L_00410f60:
        xor eax,eax
    L_00410f62:
        pop edi
    L_00410f63:
        pop esi
    L_00410f64:
        pop ebx
    L_00410f65:
        mov ecx,dword ptr [esp+2C0h]
    L_00410f6c:
        xor ecx,ebp
    L_00410f6e:
        call asm_security_check_cookie_00458ea5
    L_00410f73:
        mov esp,ebp
    L_00410f75:
        pop ebp
    L_00410f76:
        ret
    L_00410f77:
        mov eax,dword ptr [data_004776f4]
    L_00410f7c:
        or dword ptr [eax+378Ch],8
    L_00410f83:
        xor eax,eax
    L_00410f85:
        pop edi
    L_00410f86:
        pop esi
    L_00410f87:
        pop ebx
    L_00410f88:
        mov ecx,dword ptr [esp+2C0h]
    L_00410f8f:
        xor ecx,ebp
    L_00410f91:
        call asm_security_check_cookie_00458ea5
    L_00410f96:
        mov esp,ebp
    L_00410f98:
        pop ebp
    L_00410f99:
        ret
    L_00410f9a:
        mov esi,dword ptr [data_004776f4]
    L_00410fa0:
        call asm_BulletEntity_MarkAnimationForRemoval_0040cea0
    L_00410fa5:
        xor eax,eax
    L_00410fa7:
        pop edi
    L_00410fa8:
        pop esi
    L_00410fa9:
        pop ebx
    L_00410faa:
        mov ecx,dword ptr [esp+2C0h]
    L_00410fb1:
        xor ecx,ebp
    L_00410fb3:
        call asm_security_check_cookie_00458ea5
    L_00410fb8:
        mov esp,ebp
    L_00410fba:
        pop ebp
    L_00410fbb:
        ret
    L_00410fbc:
        mov edx,dword ptr [edx+4]
    L_00410fbf:
        push 0
    L_00410fc1:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00410fc6:
        mov esi,dword ptr [ebx+1444h]
    L_00410fcc:
        shl eax,13h
    L_00410fcf:
        xor eax,esi
    L_00410fd1:
        and eax,80000h
    L_00410fd6:
        mov ecx,esi
    L_00410fd8:
        xor ecx,eax
    L_00410fda:
        mov dword ptr [ebx+1444h],ecx
    L_00410fe0:
        xor eax,eax
    L_00410fe2:
        pop edi
    L_00410fe3:
        pop esi
    L_00410fe4:
        pop ebx
    L_00410fe5:
        mov ecx,dword ptr [esp+2C0h]
    L_00410fec:
        xor ecx,ebp
    L_00410fee:
        call asm_security_check_cookie_00458ea5
    L_00410ff3:
        mov esp,ebp
    L_00410ff5:
        pop ebp
    L_00410ff6:
        ret
    L_00410ff7:
        xor eax,eax
    L_00410ff9:
        cmp word ptr [esp+10h],1AFh
    L_00411000:
        mov ecx,77h
    L_00411005:
        lea edi,[esp+50h]
    L_00411009:
        rep stosd
    L_0041100b:
        jne short L_0041101e
    L_0041100d:
        lea esi,[ebx+2E4h]
    L_00411013:
        mov ecx,6Ch
    L_00411018:
        lea edi,[esp+7Ch]
    L_0041101c:
        rep movsd
    L_0041101e:
        fld dword ptr [ebx+1344h]
    L_00411024:
        push 0
    L_00411026:
        fadd dword ptr [ebx+2Ch]
    L_00411029:
        fstp dword ptr [esp+28h]
    L_0041102d:
        mov ecx,dword ptr [esp+28h]
    L_00411031:
        fld dword ptr [ebx+1348h]
    L_00411037:
        mov dword ptr [esp+54h],ecx
    L_0041103b:
        fadd dword ptr [ebx+30h]
    L_0041103e:
        fstp dword ptr [esp+2Ch]
    L_00411042:
        mov eax,dword ptr [esp+2Ch]
    L_00411046:
        fld dword ptr [ebx+134Ch]
    L_0041104c:
        mov dword ptr [esp+58h],eax
    L_00411050:
        fadd dword ptr [ebx+34h]
    L_00411053:
        fstp dword ptr [esp+30h]
    L_00411057:
        mov ecx,dword ptr [esp+30h]
    L_0041105b:
        mov dword ptr [esp+5Ch],ecx
    L_0041105f:
        mov edx,dword ptr [edx+4]
    L_00411062:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00411067:
        mov word ptr [esp+74h],ax
    L_0041106c:
        mov eax,dword ptr [ebx+14D8h]
    L_00411072:
        mov edx,dword ptr [eax+4]
    L_00411075:
        push 1
    L_00411077:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0041107c:
        mov word ptr [esp+76h],ax
    L_00411081:
        mov eax,dword ptr [ebx+14D8h]
    L_00411087:
        mov eax,dword ptr [eax+4]
    L_0041108a:
        mov ecx,2
    L_0041108f:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411094:
        fstp dword ptr [esp+5Ch]
    L_00411098:
        mov eax,dword ptr [ebx+14D8h]
    L_0041109e:
        mov eax,dword ptr [eax+4]
    L_004110a1:
        mov ecx,3
    L_004110a6:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004110ab:
        fstp dword ptr [esp+70h]
    L_004110af:
        mov eax,dword ptr [ebx+14D8h]
    L_004110b5:
        mov eax,dword ptr [eax+4]
    L_004110b8:
        mov ecx,4
    L_004110bd:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004110c2:
        fstp dword ptr [esp+64h]
    L_004110c6:
        mov eax,dword ptr [ebx+14D8h]
    L_004110cc:
        mov eax,dword ptr [eax+4]
    L_004110cf:
        mov ecx,5
    L_004110d4:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004110d9:
        fstp dword ptr [esp+60h]
    L_004110dd:
        mov eax,dword ptr [ebx+14D8h]
    L_004110e3:
        mov eax,dword ptr [eax+4]
    L_004110e6:
        mov ecx,6
    L_004110eb:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004110f0:
        fstp dword ptr [esp+68h]
    L_004110f4:
        mov ebx,dword ptr [ebx+14D8h]
    L_004110fa:
        mov eax,dword ptr [ebx+4]
    L_004110fd:
        mov ecx,7
    L_00411102:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411107:
        fstp dword ptr [esp+6Ch]
    L_0041110b:
        mov ecx,dword ptr [esp+78h]
    L_0041110f:
        mov esi,dword ptr [data_0047781c]
    L_00411115:
        or ecx,1
    L_00411118:
        push 0
    L_0041111a:
        lea edi,[esp+54h]
    L_0041111e:
        mov dword ptr [esp+7Ch],ecx
    L_00411122:
        call asm_FUN_0041c510_0041c510
    L_00411127:
        xor eax,eax
    L_00411129:
        pop edi
    L_0041112a:
        pop esi
    L_0041112b:
        pop ebx
    L_0041112c:
        mov ecx,dword ptr [esp+2C0h]
    L_00411133:
        xor ecx,ebp
    L_00411135:
        call asm_security_check_cookie_00458ea5
    L_0041113a:
        mov esp,ebp
    L_0041113c:
        pop ebp
    L_0041113d:
        ret
    L_0041113e:
        xor eax,eax
    L_00411140:
        mov ecx,7Eh
    L_00411145:
        lea edi,[esp+50h]
    L_00411149:
        rep stosd
    L_0041114b:
        xor ecx,ecx
    L_0041114d:
        mov eax,ebx
    L_0041114f:
        mov dword ptr [esp+7Ch],41000000h
    L_00411157:
        call asm_ECL_ResolveIntDestination_00412a10
    L_0041115c:
        cmp word ptr [esi+4],1B0h
    L_00411162:
        mov dword ptr [esp+10h],eax
    L_00411166:
        jne short L_0041117c
    L_00411168:
        lea esi,[ebx+2E4h]
    L_0041116e:
        mov ecx,6Ch
    L_00411173:
        lea edi,[esp+98h]
    L_0041117a:
        rep movsd
    L_0041117c:
        fld dword ptr [ebx+1344h]
    L_00411182:
        push 1
    L_00411184:
        fadd dword ptr [ebx+2Ch]
    L_00411187:
        fstp dword ptr [esp+28h]
    L_0041118b:
        mov edx,dword ptr [esp+28h]
    L_0041118f:
        fld dword ptr [ebx+1348h]
    L_00411195:
        mov dword ptr [esp+54h],edx
    L_00411199:
        fadd dword ptr [ebx+30h]
    L_0041119c:
        fstp dword ptr [esp+2Ch]
    L_004111a0:
        mov eax,dword ptr [esp+2Ch]
    L_004111a4:
        fld dword ptr [ebx+134Ch]
    L_004111aa:
        mov dword ptr [esp+58h],eax
    L_004111ae:
        fadd dword ptr [ebx+34h]
    L_004111b1:
        mov eax,dword ptr [ebx+14D8h]
    L_004111b7:
        fstp dword ptr [esp+30h]
    L_004111bb:
        mov ecx,dword ptr [esp+30h]
    L_004111bf:
        mov dword ptr [esp+5Ch],ecx
    L_004111c3:
        mov edx,dword ptr [eax+4]
    L_004111c6:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004111cb:
        mov word ptr [esp+90h],ax
    L_004111d3:
        mov eax,dword ptr [ebx+14D8h]
    L_004111d9:
        mov edx,dword ptr [eax+4]
    L_004111dc:
        push 2
    L_004111de:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004111e3:
        mov word ptr [esp+92h],ax
    L_004111eb:
        mov eax,dword ptr [ebx+14D8h]
    L_004111f1:
        mov eax,dword ptr [eax+4]
    L_004111f4:
        mov ecx,3
    L_004111f9:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004111fe:
        fstp dword ptr [esp+68h]
    L_00411202:
        mov eax,dword ptr [ebx+14D8h]
    L_00411208:
        mov eax,dword ptr [eax+4]
    L_0041120b:
        mov ecx,4
    L_00411210:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411215:
        fstp dword ptr [esp+74h]
    L_00411219:
        mov eax,dword ptr [ebx+14D8h]
    L_0041121f:
        mov eax,dword ptr [eax+4]
    L_00411222:
        mov ecx,5
    L_00411227:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0041122c:
        fstp dword ptr [esp+70h]
    L_00411230:
        mov eax,dword ptr [ebx+14D8h]
    L_00411236:
        mov edx,dword ptr [eax+4]
    L_00411239:
        push 6
    L_0041123b:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00411240:
        mov dword ptr [esp+80h],eax
    L_00411247:
        mov eax,dword ptr [ebx+14D8h]
    L_0041124d:
        mov edx,dword ptr [eax+4]
    L_00411250:
        push 7
    L_00411252:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00411257:
        mov dword ptr [esp+84h],eax
    L_0041125e:
        mov eax,dword ptr [ebx+14D8h]
    L_00411264:
        mov edx,dword ptr [eax+4]
    L_00411267:
        push 8
    L_00411269:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0041126e:
        mov dword ptr [esp+88h],eax
    L_00411275:
        mov eax,dword ptr [ebx+14D8h]
    L_0041127b:
        mov edx,dword ptr [eax+4]
    L_0041127e:
        push 9
    L_00411280:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00411285:
        mov dword ptr [esp+8Ch],eax
    L_0041128c:
        mov eax,dword ptr [ebx+14D8h]
    L_00411292:
        mov eax,dword ptr [eax+4]
    L_00411295:
        mov ecx,0Ah
    L_0041129a:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0041129f:
        fstp dword ptr [esp+78h]
    L_004112a3:
        mov ebx,dword ptr [ebx+14D8h]
    L_004112a9:
        mov edx,dword ptr [ebx+4]
    L_004112ac:
        push 0Bh
    L_004112ae:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_004112b3:
        mov esi,dword ptr [data_0047781c]
    L_004112b9:
        or eax,2
    L_004112bc:
        push 1
    L_004112be:
        lea edi,[esp+54h]
    L_004112c2:
        mov dword ptr [esp+98h],eax
    L_004112c9:
        call asm_FUN_0041c510_0041c510
    L_004112ce:
        mov ecx,dword ptr [esp+10h]
    L_004112d2:
        test ecx,ecx
    L_004112d4:
        je asm_target_00411d18
    L_004112da:
        mov edx,ecx
    L_004112dc:
        mov dword ptr [edx],eax
    L_004112de:
        xor eax,eax
    L_004112e0:
        pop edi
    L_004112e1:
        pop esi
    L_004112e2:
        pop ebx
    L_004112e3:
        mov ecx,dword ptr [esp+2C0h]
    L_004112ea:
        xor ecx,ebp
    L_004112ec:
        call asm_security_check_cookie_00458ea5
    L_004112f1:
        mov esp,ebp
    L_004112f3:
        pop ebp
    L_004112f4:
        ret
    L_004112f5:
        xor eax,eax
    L_004112f7:
        cmp word ptr [esp+10h],1B1h
    L_004112fe:
        mov ecx,77h
    L_00411303:
        lea edi,[esp+50h]
    L_00411307:
        rep stosd
    L_00411309:
        jne short L_0041131c
    L_0041130b:
        lea esi,[ebx+2E4h]
    L_00411311:
        mov ecx,6Ch
    L_00411316:
        lea edi,[esp+7Ch]
    L_0041131a:
        rep movsd
    L_0041131c:
        fld dword ptr [ebx+1344h]
    L_00411322:
        fadd dword ptr [ebx+2Ch]
    L_00411325:
        fstp dword ptr [esp+24h]
    L_00411329:
        mov eax,dword ptr [esp+24h]
    L_0041132d:
        fld dword ptr [ebx+1348h]
    L_00411333:
        mov dword ptr [esp+50h],eax
    L_00411337:
        fadd dword ptr [ebx+30h]
    L_0041133a:
        mov eax,ebx
    L_0041133c:
        fstp dword ptr [esp+28h]
    L_00411340:
        mov ecx,dword ptr [esp+28h]
    L_00411344:
        fld dword ptr [ebx+134Ch]
    L_0041134a:
        mov dword ptr [esp+54h],ecx
    L_0041134e:
        fadd dword ptr [ebx+34h]
    L_00411351:
        xor ecx,ecx
    L_00411353:
        fstp dword ptr [esp+2Ch]
    L_00411357:
        mov edx,dword ptr [esp+2Ch]
    L_0041135b:
        mov dword ptr [esp+58h],edx
    L_0041135f:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411364:
        mov word ptr [esp+74h],ax
    L_00411369:
        mov ecx,1
    L_0041136e:
        mov eax,ebx
    L_00411370:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411375:
        mov word ptr [esp+76h],ax
    L_0041137a:
        mov eax,dword ptr [ebx+14D8h]
    L_00411380:
        mov eax,dword ptr [eax+4]
    L_00411383:
        mov ecx,2
    L_00411388:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0041138d:
        fstp dword ptr [esp+5Ch]
    L_00411391:
        mov eax,dword ptr [ebx+14D8h]
    L_00411397:
        mov eax,dword ptr [eax+4]
    L_0041139a:
        mov ecx,3
    L_0041139f:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004113a4:
        fstp dword ptr [esp+70h]
    L_004113a8:
        mov eax,dword ptr [ebx+14D8h]
    L_004113ae:
        mov eax,dword ptr [eax+4]
    L_004113b1:
        mov ecx,4
    L_004113b6:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004113bb:
        fstp dword ptr [esp+64h]
    L_004113bf:
        mov eax,dword ptr [ebx+14D8h]
    L_004113c5:
        mov eax,dword ptr [eax+4]
    L_004113c8:
        mov ecx,5
    L_004113cd:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004113d2:
        fstp dword ptr [esp+60h]
    L_004113d6:
        mov eax,dword ptr [ebx+14D8h]
    L_004113dc:
        mov eax,dword ptr [eax+4]
    L_004113df:
        mov ecx,6
    L_004113e4:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004113e9:
        fstp dword ptr [esp+68h]
    L_004113ed:
        mov ebx,dword ptr [ebx+14D8h]
    L_004113f3:
        mov eax,dword ptr [ebx+4]
    L_004113f6:
        mov ecx,7
    L_004113fb:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411400:
        fstp dword ptr [esp+6Ch]
    L_00411404:
        mov ecx,dword ptr [esp+78h]
    L_00411408:
        mov esi,dword ptr [data_0047781c]
    L_0041140e:
        and ecx,0FFFFFFFEh
    L_00411411:
        push 0
    L_00411413:
        lea edi,[esp+54h]
    L_00411417:
        mov dword ptr [esp+7Ch],ecx
    L_0041141b:
        call asm_FUN_0041c510_0041c510
    L_00411420:
        xor eax,eax
    L_00411422:
        pop edi
    L_00411423:
        pop esi
    L_00411424:
        pop ebx
    L_00411425:
        mov ecx,dword ptr [esp+2C0h]
    L_0041142c:
        xor ecx,ebp
    L_0041142e:
        call asm_security_check_cookie_00458ea5
    L_00411433:
        mov esp,ebp
    L_00411435:
        pop ebp
    L_00411436:
        ret
    L_00411437:
        lea edx,[esp+50h]
    L_0041143b:
        call asm_BulletSpawnParameters_Initialize_0040cf40
    L_00411440:
        xor ecx,ecx
    L_00411442:
        mov eax,ebx
    L_00411444:
        call asm_ECL_ResolveIntDestination_00412a10
    L_00411449:
        cmp word ptr [esi+4],1B2h
    L_0041144f:
        mov dword ptr [esp+10h],eax
    L_00411453:
        jne short L_00411469
    L_00411455:
        lea esi,[ebx+2E4h]
    L_0041145b:
        mov ecx,6Ch
    L_00411460:
        lea edi,[esp+98h]
    L_00411467:
        rep movsd
    L_00411469:
        fld dword ptr [ebx+1344h]
    L_0041146f:
        fadd dword ptr [ebx+2Ch]
    L_00411472:
        fstp dword ptr [esp+24h]
    L_00411476:
        mov eax,dword ptr [esp+24h]
    L_0041147a:
        fld dword ptr [ebx+1348h]
    L_00411480:
        mov dword ptr [esp+50h],eax
    L_00411484:
        fadd dword ptr [ebx+30h]
    L_00411487:
        mov eax,ebx
    L_00411489:
        fstp dword ptr [esp+28h]
    L_0041148d:
        mov ecx,dword ptr [esp+28h]
    L_00411491:
        fld dword ptr [ebx+134Ch]
    L_00411497:
        mov dword ptr [esp+54h],ecx
    L_0041149b:
        fadd dword ptr [ebx+34h]
    L_0041149e:
        mov ecx,1
    L_004114a3:
        fstp dword ptr [esp+2Ch]
    L_004114a7:
        mov edx,dword ptr [esp+2Ch]
    L_004114ab:
        mov dword ptr [esp+58h],edx
    L_004114af:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_004114b4:
        mov word ptr [esp+90h],ax
    L_004114bc:
        mov ecx,2
    L_004114c1:
        mov eax,ebx
    L_004114c3:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_004114c8:
        mov word ptr [esp+92h],ax
    L_004114d0:
        mov eax,dword ptr [ebx+14D8h]
    L_004114d6:
        mov eax,dword ptr [eax+4]
    L_004114d9:
        mov ecx,3
    L_004114de:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004114e3:
        fstp dword ptr [esp+68h]
    L_004114e7:
        mov eax,dword ptr [ebx+14D8h]
    L_004114ed:
        mov eax,dword ptr [eax+4]
    L_004114f0:
        mov ecx,4
    L_004114f5:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004114fa:
        fstp dword ptr [esp+74h]
    L_004114fe:
        mov eax,dword ptr [ebx+14D8h]
    L_00411504:
        mov eax,dword ptr [eax+4]
    L_00411507:
        mov ecx,5
    L_0041150c:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411511:
        fstp dword ptr [esp+70h]
    L_00411515:
        mov ecx,6
    L_0041151a:
        mov eax,ebx
    L_0041151c:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411521:
        mov dword ptr [esp+80h],eax
    L_00411528:
        mov ecx,7
    L_0041152d:
        mov eax,ebx
    L_0041152f:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411534:
        mov dword ptr [esp+84h],eax
    L_0041153b:
        mov ecx,8
    L_00411540:
        mov eax,ebx
    L_00411542:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411547:
        mov dword ptr [esp+88h],eax
    L_0041154e:
        mov ecx,9
    L_00411553:
        mov eax,ebx
    L_00411555:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_0041155a:
        mov dword ptr [esp+8Ch],eax
    L_00411561:
        mov eax,dword ptr [ebx+14D8h]
    L_00411567:
        mov eax,dword ptr [eax+4]
    L_0041156a:
        mov ecx,0Ah
    L_0041156f:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411574:
        fstp dword ptr [esp+78h]
    L_00411578:
        mov ecx,0Bh
    L_0041157d:
        mov eax,ebx
    L_0041157f:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411584:
        mov esi,dword ptr [data_0047781c]
    L_0041158a:
        and eax,0FFFFFFFDh
    L_0041158d:
        push 1
    L_0041158f:
        lea edi,[esp+54h]
    L_00411593:
        mov dword ptr [esp+98h],eax
    L_0041159a:
        call asm_FUN_0041c510_0041c510
    L_0041159f:
        mov ecx,dword ptr [esp+10h]
    L_004115a3:
        test ecx,ecx
    L_004115a5:
        je asm_target_00411d18
    L_004115ab:
        mov dword ptr [ecx],eax
    L_004115ad:
        xor eax,eax
    L_004115af:
        pop edi
    L_004115b0:
        pop esi
    L_004115b1:
        pop ebx
    L_004115b2:
        mov ecx,dword ptr [esp+2C0h]
    L_004115b9:
        xor ecx,ebp
    L_004115bb:
        call asm_security_check_cookie_00458ea5
    L_004115c0:
        mov esp,ebp
    L_004115c2:
        pop ebp
    L_004115c3:
        ret
    L_004115c4:
        xor ecx,ecx
    L_004115c6:
        mov eax,ebx
    L_004115c8:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_004115cd:
        mov ecx,eax
    L_004115cf:
        mov eax,dword ptr [data_0047781c]
    L_004115d4:
        call asm_BulletEntity_FindById_0040cf90
    L_004115d9:
        mov esi,eax
    L_004115db:
        test esi,esi
    L_004115dd:
        je asm_target_00411d18
    L_004115e3:
        mov eax,dword ptr [ebx+14D8h]
    L_004115e9:
        mov eax,dword ptr [eax+4]
    L_004115ec:
        mov ecx,2
    L_004115f1:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004115f6:
        fstp dword ptr [esp+10h]
    L_004115fa:
        mov ebx,dword ptr [ebx+14D8h]
    L_00411600:
        mov eax,dword ptr [ebx+4]
    L_00411603:
        mov ecx,1
    L_00411608:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0041160d:
        fstp dword ptr [esp+24h]
    L_00411611:
        mov edx,dword ptr [esp+10h]
    L_00411615:
        mov eax,dword ptr [esp+24h]
    L_00411619:
        add esi,24h
    L_0041161c:
        mov dword ptr [esi],eax
    L_0041161e:
        mov ecx,edx
    L_00411620:
        mov dword ptr [esp+28h],edx
    L_00411624:
        mov dword ptr [esp+2Ch],0
    L_0041162c:
        mov edx,dword ptr [esp+2Ch]
    L_00411630:
        mov dword ptr [esi+4],ecx
    L_00411633:
        mov dword ptr [esi+8],edx
    L_00411636:
        xor eax,eax
    L_00411638:
        pop edi
    L_00411639:
        pop esi
    L_0041163a:
        pop ebx
    L_0041163b:
        mov ecx,dword ptr [esp+2C0h]
    L_00411642:
        xor ecx,ebp
    L_00411644:
        call asm_security_check_cookie_00458ea5
    L_00411649:
        mov esp,ebp
    L_0041164b:
        pop ebp
    L_0041164c:
        ret
    L_0041164d:
        xor ecx,ecx
    L_0041164f:
        mov eax,ebx
    L_00411651:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411656:
        mov ecx,eax
    L_00411658:
        mov eax,dword ptr [data_0047781c]
    L_0041165d:
        call asm_BulletEntity_FindById_0040cf90
    L_00411662:
        mov esi,eax
    L_00411664:
        test esi,esi
    L_00411666:
        je asm_target_00411d18
    L_0041166c:
        mov eax,dword ptr [ebx+14D8h]
    L_00411672:
        mov eax,dword ptr [eax+4]
    L_00411675:
        mov ecx,2
    L_0041167a:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0041167f:
        fstp dword ptr [esp+10h]
    L_00411683:
        mov ebx,dword ptr [ebx+14D8h]
    L_00411689:
        mov eax,dword ptr [ebx+4]
    L_0041168c:
        mov ecx,1
    L_00411691:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411696:
        fstp dword ptr [esp+24h]
    L_0041169a:
        mov eax,dword ptr [esp+10h]
    L_0041169e:
        mov dword ptr [esp+28h],eax
    L_004116a2:
        lea eax,[esp+24h]
    L_004116a6:
        mov ecx,esi
    L_004116a8:
        mov dword ptr [esp+2Ch],0
    L_004116b0:
        call asm_BulletEntity_SetAnimationVector_0040cf60
    L_004116b5:
        xor eax,eax
    L_004116b7:
        pop edi
    L_004116b8:
        pop esi
    L_004116b9:
        pop ebx
    L_004116ba:
        mov ecx,dword ptr [esp+2C0h]
    L_004116c1:
        xor ecx,ebp
    L_004116c3:
        call asm_security_check_cookie_00458ea5
    L_004116c8:
        mov esp,ebp
    L_004116ca:
        pop ebp
    L_004116cb:
        ret
    L_004116cc:
        xor ecx,ecx
    L_004116ce:
        mov eax,ebx
    L_004116d0:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_004116d5:
        mov ecx,eax
    L_004116d7:
        mov eax,dword ptr [data_0047781c]
    L_004116dc:
        call asm_BulletEntity_FindById_0040cf90
    L_004116e1:
        mov esi,eax
    L_004116e3:
        test esi,esi
    L_004116e5:
        je asm_target_00411d18
    L_004116eb:
        mov ebx,dword ptr [ebx+14D8h]
    L_004116f1:
        mov eax,dword ptr [ebx+4]
    L_004116f4:
        mov ecx,1
    L_004116f9:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004116fe:
        fstp dword ptr [esi+48h]
    L_00411701:
        xor eax,eax
    L_00411703:
        pop edi
    L_00411704:
        pop esi
    L_00411705:
        pop ebx
    L_00411706:
        mov ecx,dword ptr [esp+2C0h]
    L_0041170d:
        xor ecx,ebp
    L_0041170f:
        call asm_security_check_cookie_00458ea5
    L_00411714:
        mov esp,ebp
    L_00411716:
        pop ebp
    L_00411717:
        ret
    L_00411718:
        xor ecx,ecx
    L_0041171a:
        mov eax,ebx
    L_0041171c:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411721:
        mov ecx,eax
    L_00411723:
        mov eax,dword ptr [data_0047781c]
    L_00411728:
        call asm_BulletEntity_FindById_0040cf90
    L_0041172d:
        mov esi,eax
    L_0041172f:
        test esi,esi
    L_00411731:
        je asm_target_00411d18
    L_00411737:
        mov ebx,dword ptr [ebx+14D8h]
    L_0041173d:
        mov eax,dword ptr [ebx+4]
    L_00411740:
        mov ecx,1
    L_00411745:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0041174a:
        fstp dword ptr [esi+44h]
    L_0041174d:
        xor eax,eax
    L_0041174f:
        pop edi
    L_00411750:
        pop esi
    L_00411751:
        pop ebx
    L_00411752:
        mov ecx,dword ptr [esp+2C0h]
    L_00411759:
        xor ecx,ebp
    L_0041175b:
        call asm_security_check_cookie_00458ea5
    L_00411760:
        mov esp,ebp
    L_00411762:
        pop ebp
    L_00411763:
        ret
    L_00411764:
        xor ecx,ecx
    L_00411766:
        mov eax,ebx
    L_00411768:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_0041176d:
        mov ecx,eax
    L_0041176f:
        mov eax,dword ptr [data_0047781c]
    L_00411774:
        call asm_BulletEntity_FindById_0040cf90
    L_00411779:
        mov esi,eax
    L_0041177b:
        test esi,esi
    L_0041177d:
        je asm_target_00411d18
    L_00411783:
        mov ebx,dword ptr [ebx+14D8h]
    L_00411789:
        mov eax,dword ptr [ebx+4]
    L_0041178c:
        mov ecx,1
    L_00411791:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411796:
        fstp dword ptr [esi+3Ch]
    L_00411799:
        xor eax,eax
    L_0041179b:
        pop edi
    L_0041179c:
        pop esi
    L_0041179d:
        pop ebx
    L_0041179e:
        mov ecx,dword ptr [esp+2C0h]
    L_004117a5:
        xor ecx,ebp
    L_004117a7:
        call asm_security_check_cookie_00458ea5
    L_004117ac:
        mov esp,ebp
    L_004117ae:
        pop ebp
    L_004117af:
        ret
    L_004117b0:
        xor ecx,ecx
    L_004117b2:
        mov eax,ebx
    L_004117b4:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_004117b9:
        mov ecx,eax
    L_004117bb:
        mov eax,dword ptr [data_0047781c]
    L_004117c0:
        call asm_BulletEntity_FindById_0040cf90
    L_004117c5:
        mov esi,eax
    L_004117c7:
        test esi,esi
    L_004117c9:
        je asm_target_00411d18
    L_004117cf:
        mov ebx,dword ptr [ebx+14D8h]
    L_004117d5:
        mov eax,dword ptr [ebx+4]
    L_004117d8:
        mov ecx,1
    L_004117dd:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004117e2:
        fstp dword ptr [esi+440h]
    L_004117e8:
        xor eax,eax
    L_004117ea:
        pop edi
    L_004117eb:
        pop esi
    L_004117ec:
        pop ebx
    L_004117ed:
        mov ecx,dword ptr [esp+2C0h]
    L_004117f4:
        xor ecx,ebp
    L_004117f6:
        call asm_security_check_cookie_00458ea5
    L_004117fb:
        mov esp,ebp
    L_004117fd:
        pop ebp
    L_004117fe:
        ret
    L_004117ff:
        mov eax,dword ptr [edx+4]
    L_00411802:
        xor ecx,ecx
    L_00411804:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411809:
        fstp dword ptr [esp+10h]
    L_0041180d:
        mov esi,dword ptr [esp+10h]
    L_00411811:
        mov eax,dword ptr [data_004776f0]
    L_00411816:
        push 0
    L_00411818:
        push 1
    L_0041181a:
        add ebx,2Ch
    L_0041181d:
        push esi
    L_0041181e:
        call asm_FUN_00408100_00408100
    L_00411823:
        mov eax,dword ptr [data_0047781c]
    L_00411828:
        push 1
    L_0041182a:
        push esi
    L_0041182b:
        call asm_ScoreRecords_CopyVectorAndEvaluate_0041c800
    L_00411830:
        xor eax,eax
    L_00411832:
        pop edi
    L_00411833:
        pop esi
    L_00411834:
        pop ebx
    L_00411835:
        mov ecx,dword ptr [esp+2C0h]
    L_0041183c:
        xor ecx,ebp
    L_0041183e:
        call asm_security_check_cookie_00458ea5
    L_00411843:
        mov esp,ebp
    L_00411845:
        pop ebp
    L_00411846:
        ret
    L_00411847:
        mov eax,dword ptr [edx+4]
    L_0041184a:
        xor ecx,ecx
    L_0041184c:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411851:
        fstp dword ptr [esp+10h]
    L_00411855:
        mov esi,dword ptr [esp+10h]
    L_00411859:
        mov eax,dword ptr [data_004776f0]
    L_0041185e:
        push 0
    L_00411860:
        push 0
    L_00411862:
        add ebx,2Ch
    L_00411865:
        push esi
    L_00411866:
        call asm_FUN_00408100_00408100
    L_0041186b:
        mov eax,dword ptr [data_0047781c]
    L_00411870:
        push 0
    L_00411872:
        push esi
    L_00411873:
        call asm_ScoreRecords_CopyVectorAndEvaluate_0041c800
    L_00411878:
        xor eax,eax
    L_0041187a:
        pop edi
    L_0041187b:
        pop esi
    L_0041187c:
        pop ebx
    L_0041187d:
        mov ecx,dword ptr [esp+2C0h]
    L_00411884:
        xor ecx,ebp
    L_00411886:
        call asm_security_check_cookie_00458ea5
    L_0041188b:
        mov esp,ebp
    L_0041188d:
        pop ebp
    L_0041188e:
        ret
    L_0041188f:
        xor ecx,ecx
    L_00411891:
        mov eax,ebx
    L_00411893:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411898:
        mov ecx,eax
    L_0041189a:
        mov eax,474C40h
    L_0041189f:
        call asm_Score_SetMode_00412ed0
    L_004118a4:
        xor eax,eax
    L_004118a6:
        pop edi
    L_004118a7:
        pop esi
    L_004118a8:
        pop ebx
    L_004118a9:
        mov ecx,dword ptr [esp+2C0h]
    L_004118b0:
        xor ecx,ebp
    L_004118b2:
        call asm_security_check_cookie_00458ea5
    L_004118b7:
        mov esp,ebp
    L_004118b9:
        pop ebp
    L_004118ba:
        ret
    L_004118bb:
        mov eax,dword ptr [data_00474c98]
    L_004118c0:
        cmp eax,200h
    L_004118c5:
        jl short L_004118d4
    L_004118c7:
        mov eax,dword ptr [edx+4]
    L_004118ca:
        mov ecx,2
    L_004118cf:
        jmp asm_target_00411951
    L_004118d4:
        xor ecx,ecx
    L_004118d6:
        cmp eax,0FFFFFE00h
    L_004118db:
        mov eax,dword ptr [edx+4]
    L_004118de:
        jg short L_00411951
    L_004118e0:
        jmp short L_0041190c
    L_004118e2:
        mov eax,dword ptr [data_00474c98]
    L_004118e7:
        cmp eax,258h
    L_004118ec:
        jge asm_target_00410114
    L_004118f2:
        cmp eax,0C8h
    L_004118f7:
        jge asm_target_00410107
    L_004118fd:
        cmp eax,0FFFFFF38h
    L_00411902:
        jl short L_00411942
    L_00411904:
        mov ecx,2
    L_00411909:
        mov eax,dword ptr [edx+4]
    L_0041190c:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411911:
        fstp dword ptr [esp+10h]
    L_00411915:
        mov ebx,dword ptr [ebx+14D8h]
    L_0041191b:
        mov eax,dword ptr [ebx+4]
    L_0041191e:
        xor ecx,ecx
    L_00411920:
        call asm_ECL_ResolveFloatDestination_00450070
    L_00411925:
        mov edx,dword ptr [esp+10h]
    L_00411929:
        mov dword ptr [eax],edx
    L_0041192b:
        xor eax,eax
    L_0041192d:
        pop edi
    L_0041192e:
        pop esi
    L_0041192f:
        pop ebx
    L_00411930:
        mov ecx,dword ptr [esp+2C0h]
    L_00411937:
        xor ecx,ebp
    L_00411939:
        call asm_security_check_cookie_00458ea5
    L_0041193e:
        mov esp,ebp
    L_00411940:
        pop ebp
    L_00411941:
        ret
    L_00411942:
        cmp eax,0FFFFFE70h
    L_00411947:
        mov eax,dword ptr [edx+4]
    L_0041194a:
        jl short L_00411987
    L_0041194c:
        mov ecx,1
    L_00411951:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411956:
        mov ebx,dword ptr [ebx+14D8h]
    L_0041195c:
        fstp dword ptr [esp+10h]
    L_00411960:
        mov eax,dword ptr [ebx+4]
    L_00411963:
        xor ecx,ecx
    L_00411965:
        call asm_ECL_ResolveFloatDestination_00450070
    L_0041196a:
        mov ecx,dword ptr [esp+10h]
    L_0041196e:
        mov dword ptr [eax],ecx
    L_00411970:
        xor eax,eax
    L_00411972:
        pop edi
    L_00411973:
        pop esi
    L_00411974:
        pop ebx
    L_00411975:
        mov ecx,dword ptr [esp+2C0h]
    L_0041197c:
        xor ecx,ebp
    L_0041197e:
        call asm_security_check_cookie_00458ea5
    L_00411983:
        mov esp,ebp
    L_00411985:
        pop ebp
    L_00411986:
        ret
    L_00411987:
        xor ecx,ecx
    L_00411989:
        jmp short L_0041190c
    L_0041198b:
        mov eax,dword ptr [edx+4]
    L_0041198e:
        mov ecx,1
    L_00411993:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411998:
        fstp dword ptr [esp+10h]
    L_0041199c:
        mov eax,dword ptr [ebx+14D8h]
    L_004119a2:
        mov eax,dword ptr [eax+4]
    L_004119a5:
        mov ecx,2
    L_004119aa:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_004119af:
        fstp dword ptr [esp+30h]
    L_004119b3:
        mov ebx,dword ptr [ebx+14D8h]
    L_004119b9:
        mov eax,dword ptr [ebx+4]
    L_004119bc:
        xor ecx,ecx
    L_004119be:
        call asm_ECL_ResolveFloatDestination_00450070
    L_004119c3:
        fild dword ptr [data_00474c98]
    L_004119c9:
        fadd dword ptr [data_00470d4c]
    L_004119cf:
        fld dword ptr [esp+30h]
    L_004119d3:
        fsub dword ptr [esp+10h]
    L_004119d7:
        fmulp st(1),st
    L_004119d9:
        fmul dword ptr [data_00470d48]
    L_004119df:
        fadd dword ptr [esp+10h]
    L_004119e3:
        fstp dword ptr [eax]
    L_004119e5:
        xor eax,eax
    L_004119e7:
        pop edi
    L_004119e8:
        pop esi
    L_004119e9:
        pop ebx
    L_004119ea:
        mov ecx,dword ptr [esp+2C0h]
    L_004119f1:
        xor ecx,ebp
    L_004119f3:
        call asm_security_check_cookie_00458ea5
    L_004119f8:
        mov esp,ebp
    L_004119fa:
        pop ebp
    L_004119fb:
        ret
    L_004119fc:
        mov eax,dword ptr [data_00474c98]
    L_00411a01:
        cmp eax,200h
    L_00411a06:
        jge asm_target_00411ab8
    L_00411a0c:
        xor ecx,ecx
    L_00411a0e:
        cmp eax,0FFFFFE00h
    L_00411a13:
        mov eax,ebx
    L_00411a15:
        call asm_ECL_ResolveIntDestination_00412a10
    L_00411a1a:
        mov esi,eax
    L_00411a1c:
        xor ecx,ecx
    L_00411a1e:
        mov eax,ebx
    L_00411a20:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411a25:
        mov dword ptr [esi],eax
    L_00411a27:
        xor eax,eax
    L_00411a29:
        pop edi
    L_00411a2a:
        pop esi
    L_00411a2b:
        pop ebx
    L_00411a2c:
        mov ecx,dword ptr [esp+2C0h]
    L_00411a33:
        xor ecx,ebp
    L_00411a35:
        call asm_security_check_cookie_00458ea5
    L_00411a3a:
        mov esp,ebp
    L_00411a3c:
        pop ebp
    L_00411a3d:
        ret
    L_00411a3e:
        mov eax,dword ptr [data_00474c98]
    L_00411a43:
        cmp eax,258h
    L_00411a48:
        jl short L_00411a7a
    L_00411a4a:
        xor ecx,ecx
    L_00411a4c:
        mov eax,ebx
    L_00411a4e:
        call asm_ECL_ResolveIntDestination_00412a10
    L_00411a53:
        mov esi,eax
    L_00411a55:
        mov ecx,4
    L_00411a5a:
        mov eax,ebx
    L_00411a5c:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411a61:
        mov dword ptr [esi],eax
    L_00411a63:
        xor eax,eax
    L_00411a65:
        pop edi
    L_00411a66:
        pop esi
    L_00411a67:
        pop ebx
    L_00411a68:
        mov ecx,dword ptr [esp+2C0h]
    L_00411a6f:
        xor ecx,ebp
    L_00411a71:
        call asm_security_check_cookie_00458ea5
    L_00411a76:
        mov esp,ebp
    L_00411a78:
        pop ebp
    L_00411a79:
        ret
    L_00411a7a:
        cmp eax,0C8h
    L_00411a7f:
        jl short L_00411ab1
    L_00411a81:
        xor ecx,ecx
    L_00411a83:
        mov eax,ebx
    L_00411a85:
        call asm_ECL_ResolveIntDestination_00412a10
    L_00411a8a:
        mov esi,eax
    L_00411a8c:
        mov ecx,3
    L_00411a91:
        mov eax,ebx
    L_00411a93:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411a98:
        mov dword ptr [esi],eax
    L_00411a9a:
        xor eax,eax
    L_00411a9c:
        pop edi
    L_00411a9d:
        pop esi
    L_00411a9e:
        pop ebx
    L_00411a9f:
        mov ecx,dword ptr [esp+2C0h]
    L_00411aa6:
        xor ecx,ebp
    L_00411aa8:
        call asm_security_check_cookie_00458ea5
    L_00411aad:
        mov esp,ebp
    L_00411aaf:
        pop ebp
    L_00411ab0:
        ret
    L_00411ab1:
        cmp eax,0FFFFFF38h
    L_00411ab6:
        jl short L_00411ae8
    L_00411ab8:
        xor ecx,ecx
    L_00411aba:
        mov eax,ebx
    L_00411abc:
        call asm_ECL_ResolveIntDestination_00412a10
    L_00411ac1:
        mov esi,eax
    L_00411ac3:
        mov ecx,2
    L_00411ac8:
        mov eax,ebx
    L_00411aca:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411acf:
        mov dword ptr [esi],eax
    L_00411ad1:
        xor eax,eax
    L_00411ad3:
        pop edi
    L_00411ad4:
        pop esi
    L_00411ad5:
        pop ebx
    L_00411ad6:
        mov ecx,dword ptr [esp+2C0h]
    L_00411add:
        xor ecx,ebp
    L_00411adf:
        call asm_security_check_cookie_00458ea5
    L_00411ae4:
        mov esp,ebp
    L_00411ae6:
        pop ebp
    L_00411ae7:
        ret
    L_00411ae8:
        xor ecx,ecx
    L_00411aea:
        cmp eax,0FFFFFE70h
    L_00411aef:
        mov eax,ebx
    L_00411af1:
        jl asm_target_00411a15
    L_00411af7:
        call asm_ECL_ResolveIntDestination_00412a10
    L_00411afc:
        mov esi,eax
    L_00411afe:
        mov ecx,1
    L_00411b03:
        mov eax,ebx
    L_00411b05:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411b0a:
        mov dword ptr [esi],eax
    L_00411b0c:
        xor eax,eax
    L_00411b0e:
        pop edi
    L_00411b0f:
        pop esi
    L_00411b10:
        pop ebx
    L_00411b11:
        mov ecx,dword ptr [esp+2C0h]
    L_00411b18:
        xor ecx,ebp
    L_00411b1a:
        call asm_security_check_cookie_00458ea5
    L_00411b1f:
        mov esp,ebp
    L_00411b21:
        pop ebp
    L_00411b22:
        ret
    L_00411b23:
        mov ecx,1
    L_00411b28:
        mov eax,ebx
    L_00411b2a:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411b2f:
        mov esi,eax
    L_00411b31:
        mov ecx,2
    L_00411b36:
        mov eax,ebx
    L_00411b38:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411b3d:
        mov edi,eax
    L_00411b3f:
        xor ecx,ecx
    L_00411b41:
        mov eax,ebx
    L_00411b43:
        call asm_ECL_ResolveIntDestination_00412a10
    L_00411b48:
        mov edx,dword ptr [data_00474c98]
    L_00411b4e:
        mov ecx,eax
    L_00411b50:
        add edx,400h
    L_00411b56:
        mov eax,edi
    L_00411b58:
        sub eax,esi
    L_00411b5a:
        imul eax,edx
    L_00411b5d:
        cdq
    L_00411b5e:
        and edx,7FFh
    L_00411b64:
        add eax,edx
    L_00411b66:
        sar eax,0Bh
    L_00411b69:
        add eax,esi
    L_00411b6b:
        mov dword ptr [ecx],eax
    L_00411b6d:
        xor eax,eax
    L_00411b6f:
        pop edi
    L_00411b70:
        pop esi
    L_00411b71:
        pop ebx
    L_00411b72:
        mov ecx,dword ptr [esp+2C0h]
    L_00411b79:
        xor ecx,ebp
    L_00411b7b:
        call asm_security_check_cookie_00458ea5
    L_00411b80:
        mov esp,ebp
    L_00411b82:
        pop ebp
    L_00411b83:
        ret
    L_00411b84:
        xor ecx,ecx
    L_00411b86:
        mov eax,ebx
    L_00411b88:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411b8d:
        mov ecx,dword ptr [data_0047770c]
    L_00411b93:
        mov dword ptr [ecx+9E90h],eax
    L_00411b99:
        xor eax,eax
    L_00411b9b:
        pop edi
    L_00411b9c:
        pop esi
    L_00411b9d:
        pop ebx
    L_00411b9e:
        mov ecx,dword ptr [esp+2C0h]
    L_00411ba5:
        xor ecx,ebp
    L_00411ba7:
        call asm_security_check_cookie_00458ea5
    L_00411bac:
        mov esp,ebp
    L_00411bae:
        pop ebp
    L_00411baf:
        ret
    L_00411bb0:
        mov eax,dword ptr [data_0047781c]
    L_00411bb5:
        call asm_ScoreRecords_MarkEligible_0041c7d0
    L_00411bba:
        xor eax,eax
    L_00411bbc:
        pop edi
    L_00411bbd:
        pop esi
    L_00411bbe:
        pop ebx
    L_00411bbf:
        mov ecx,dword ptr [esp+2C0h]
    L_00411bc6:
        xor ecx,ebp
    L_00411bc8:
        call asm_security_check_cookie_00458ea5
    L_00411bcd:
        mov esp,ebp
    L_00411bcf:
        pop ebp
    L_00411bd0:
        ret
    L_00411bd1:
        xor ecx,ecx
    L_00411bd3:
        mov eax,ebx
    L_00411bd5:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411bda:
        mov esi,dword ptr [ebx+1444h]
    L_00411be0:
        shl eax,14h
    L_00411be3:
        xor eax,esi
    L_00411be5:
        and eax,100000h
    L_00411bea:
        mov ecx,esi
    L_00411bec:
        xor ecx,eax
    L_00411bee:
        mov dword ptr [ebx+1444h],ecx
    L_00411bf4:
        mov ecx,1
    L_00411bf9:
        mov eax,ebx
    L_00411bfb:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411c00:
        mov edx,dword ptr [ebx+0F4h]
    L_00411c06:
        mov dword ptr [ebx+1448h],eax
    L_00411c0c:
        and dword ptr [ebx+1444h],0FFDFFFFFh
    L_00411c16:
        mov dword ptr [ebx+144Ch],edx
    L_00411c1c:
        xor eax,eax
    L_00411c1e:
        pop edi
    L_00411c1f:
        pop esi
    L_00411c20:
        pop ebx
    L_00411c21:
        mov ecx,dword ptr [esp+2C0h]
    L_00411c28:
        xor ecx,ebp
    L_00411c2a:
        call asm_security_check_cookie_00458ea5
    L_00411c2f:
        mov esp,ebp
    L_00411c31:
        pop ebp
    L_00411c32:
        ret
    L_00411c33:
        mov eax,dword ptr [edx+4]
    L_00411c36:
        xor ecx,ecx
    L_00411c38:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411c3d:
        fstp dword ptr [data_00476f78]
    L_00411c43:
        xor eax,eax
    L_00411c45:
        pop edi
    L_00411c46:
        pop esi
    L_00411c47:
        pop ebx
    L_00411c48:
        mov ecx,dword ptr [esp+2C0h]
    L_00411c4f:
        xor ecx,ebp
    L_00411c51:
        call asm_security_check_cookie_00458ea5
    L_00411c56:
        mov esp,ebp
    L_00411c58:
        pop ebp
    L_00411c59:
        ret
    L_00411c5a:
        mov esi,dword ptr [data_00477834]
    L_00411c60:
        mov eax,dword ptr [edx+4]
    L_00411c63:
        mov ecx,1
    L_00411c68:
        add esi,3C0h
    L_00411c6e:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411c73:
        fstp dword ptr [esp+10h]
    L_00411c77:
        mov eax,dword ptr [ebx+14D8h]
    L_00411c7d:
        mov edi,dword ptr [data_00477834]
    L_00411c83:
        mov eax,dword ptr [eax+4]
    L_00411c86:
        mov ecx,2
    L_00411c8b:
        add edi,3C0h
    L_00411c91:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_00411c96:
        fsubr dword ptr [edi+4]
    L_00411c99:
        fld dword ptr [esi]
    L_00411c9b:
        fsub dword ptr [esp+10h]
    L_00411c9f:
        fpatan
    L_00411ca1:
        jmp asm_target_00411956
    L_00411ca6:
        mov eax,dword ptr [data_00474c74]
    L_00411cab:
        test eax,eax
    L_00411cad:
        jne short L_00411cc2
    L_00411caf:
        xor ecx,ecx
    L_00411cb1:
        mov eax,ebx
    L_00411cb3:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411cb8:
        mov dword ptr [esp+10h],eax
    L_00411cbc:
        fild dword ptr [esp+10h]
    L_00411cc0:
        jmp short L_00411d07
    L_00411cc2:
        cmp eax,1
    L_00411cc5:
        jne short L_00411cda
    L_00411cc7:
        mov ecx,eax
    L_00411cc9:
        mov eax,ebx
    L_00411ccb:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411cd0:
        mov dword ptr [esp+10h],eax
    L_00411cd4:
        fild dword ptr [esp+10h]
    L_00411cd8:
        jmp short L_00411d07
    L_00411cda:
        cmp eax,2
    L_00411cdd:
        mov eax,ebx
    L_00411cdf:
        jne short L_00411cf5
    L_00411ce1:
        mov ecx,2
    L_00411ce6:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411ceb:
        mov dword ptr [esp+10h],eax
    L_00411cef:
        fild dword ptr [esp+10h]
    L_00411cf3:
        jmp short L_00411d07
    L_00411cf5:
        mov ecx,3
    L_00411cfa:
        call asm_ECL_ResolveIntFromEntity_00412a00
    L_00411cff:
        mov dword ptr [esp+10h],eax
    L_00411d03:
        fild dword ptr [esp+10h]
    L_00411d07:
        mov ebx,dword ptr [ebx+14D8h]
    L_00411d0d:
        mov eax,dword ptr [ebx+4]
    L_00411d10:
        fld dword ptr [eax]
    L_00411d12:
        fsub st,st(1)
    L_00411d14:
        fstp dword ptr [eax]
    L_00411d16:
        fstp st(0)
    L_00411d18:
        mov ecx,dword ptr [esp+2CCh]
    L_00411d1f:
        pop edi
    L_00411d20:
        pop esi
    L_00411d21:
        xor ecx,ebp
    L_00411d23:
        xor eax,eax
    L_00411d25:
        pop ebx
    L_00411d26:
        call asm_security_check_cookie_00458ea5
    L_00411d2b:
        mov esp,ebp
    L_00411d2d:
        pop ebp
    L_00411d2e:
        ret
    }
}

// 0x00412A00..0x00412A0F: ?ECL_ResolveIntFromEntity@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResolveIntFromEntity_00412a00() {
    __asm {
    L_00412a00:
        mov eax,dword ptr [eax+14D8h]
    L_00412a06:
        mov edx,dword ptr [eax+4]
    L_00412a09:
        push ecx
    L_00412a0a:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00412a0f:
        ret
    }
}

// 0x00412A10..0x00412A5A: ?ECL_ResolveIntDestination@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResolveIntDestination_00412a10() {
    __asm {
    L_00412a10:
        mov edx,dword ptr [eax+14D8h]
    L_00412a16:
        mov eax,dword ptr [edx+4]
    L_00412a19:
        mov edx,dword ptr [eax+4]
    L_00412a1c:
        push esi
    L_00412a1d:
        movzx esi,word ptr [edx+8]
    L_00412a21:
        push edi
    L_00412a22:
        mov edi,1
    L_00412a27:
        shl edi,cl
    L_00412a29:
        test esi,edi
    L_00412a2b:
        je short L_00412a56
    L_00412a2d:
        mov edx,dword ptr [edx+ecx*4+10h]
    L_00412a31:
        test edx,edx
    L_00412a33:
        jl short L_00412a45
    L_00412a35:
        lea ecx,[eax+8]
    L_00412a38:
        mov eax,dword ptr [ecx+1004h]
    L_00412a3e:
        add eax,edx
    L_00412a40:
        pop edi
    L_00412a41:
        add eax,ecx
    L_00412a43:
        pop esi
    L_00412a44:
        ret
    L_00412a45:
        mov eax,dword ptr [eax+1014h]
    L_00412a4b:
        mov esi,dword ptr [eax]
    L_00412a4d:
        push edx
    L_00412a4e:
        mov ecx,eax
    L_00412a50:
        call dword ptr [esi+8]
    L_00412a53:
        pop edi
    L_00412a54:
        pop esi
    L_00412a55:
        ret
    L_00412a56:
        pop edi
    L_00412a57:
        xor eax,eax
    L_00412a59:
        pop esi
    L_00412a5a:
        ret
    }
}
