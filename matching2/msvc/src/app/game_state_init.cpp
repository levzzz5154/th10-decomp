#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00445900..0x00445ADC: GameStateInit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameStateInit_00445900() {
    __asm {
    L_00445900:
        push 0FFFFFFFFh
    L_00445902:
        push 4657A5h
    L_00445907:
        mov eax,dword ptr fs:[0]
    L_0044590d:
        push eax
    L_0044590e:
        mov dword ptr fs:[0],esp
    L_00445915:
        push ecx
    L_00445916:
        push ebx
    L_00445917:
        push ebp
    L_00445918:
        mov ebp,dword ptr [esp+1Ch]
    L_0044591c:
        push esi
    L_0044591d:
        push edi
    L_0044591e:
        push 401FF0h
    L_00445923:
        push 402050h
    L_00445928:
        push 1000h
    L_0044592d:
        lea eax,[ebp+68h]
    L_00445930:
        push 3ACh
    L_00445935:
        push eax
    L_00445936:
        call asm_eh_vector_constructor_iterator_0045252d
    L_0044593b:
        lea edx,[ebp+3AD130h]
    L_00445941:
        mov esi,0FFFFFFFEh
    L_00445946:
        xor ebx,ebx
    L_00445948:
        mov dword ptr [esp+1Ch],ebx
    L_0044594c:
        and dword ptr [edx+6Ch],esi
    L_0044594f:
        and dword ptr [edx+0B0h],esi
    L_00445955:
        and dword ptr [edx+0FCh],esi
    L_0044595b:
        and dword ptr [edx+128h],esi
    L_00445961:
        and dword ptr [edx+174h],esi
    L_00445967:
        and dword ptr [edx+1B0h],esi
    L_0044596d:
        and dword ptr [edx+1FCh],esi
    L_00445973:
        and dword ptr [edx+228h],esi
    L_00445979:
        and dword ptr [edx+378h],esi
    L_0044597f:
        mov ecx,0EBh
    L_00445984:
        xor eax,eax
    L_00445986:
        mov edi,edx
    L_00445988:
        rep stosd
    L_0044598a:
        mov word ptr [edx+384h],0FFFFh
    L_00445993:
        push 401FF0h
    L_00445998:
        push 402050h
    L_0044599d:
        push 14h
    L_0044599f:
        push 3ACh
    L_004459a4:
        lea eax,[ebp+72DAE4h]
    L_004459aa:
        push eax
    L_004459ab:
        mov byte ptr [esp+30h],1
    L_004459b0:
        call asm_eh_vector_constructor_iterator_0045252d
    L_004459b5:
        mov byte ptr [esp+1Ch],2
    L_004459ba:
        xor eax,eax
    L_004459bc:
        mov ecx,1CC918h
    L_004459c1:
        mov edi,ebp
    L_004459c3:
        rep stosd
    L_004459c5:
        mov dword ptr [data_004978b4],3F800000h
    L_004459cf:
        mov dword ptr [data_0049789c],3F800000h
    L_004459d9:
        mov dword ptr [data_00497884],3F800000h
    L_004459e3:
        mov dword ptr [data_0049786c],3F800000h
    L_004459ed:
        mov dword ptr [data_00497870],eax
    L_004459f2:
        mov dword ptr [data_00497874],eax
    L_004459f7:
        mov dword ptr [data_00497888],3F800000h
    L_00445a01:
        mov dword ptr [data_0049788c],eax
    L_00445a06:
        mov dword ptr [data_004978a0],eax
    L_00445a0b:
        mov dword ptr [data_004978a4],3F800000h
    L_00445a15:
        mov dword ptr [data_004978b8],3F800000h
    L_00445a1f:
        mov dword ptr [data_004978bc],3F800000h
    L_00445a29:
        mov dword ptr [data_00497920],3F800000h
    L_00445a33:
        mov dword ptr [data_00497904],3F800000h
    L_00445a3d:
        mov dword ptr [data_004978e8],3F800000h
    L_00445a47:
        mov dword ptr [data_004978cc],3F800000h
    L_00445a51:
        mov dword ptr [data_004978d4],eax
    L_00445a56:
        mov dword ptr [data_004978d8],eax
    L_00445a5b:
        mov dword ptr [data_004978f0],3F800000h
    L_00445a65:
        mov dword ptr [data_004978f4],eax
    L_00445a6a:
        mov dword ptr [data_0049790c],eax
    L_00445a6f:
        mov dword ptr [data_00497910],3F800000h
    L_00445a79:
        mov dword ptr [data_00497928],3F800000h
    L_00445a83:
        mov dword ptr [data_0049792c],3F800000h
    L_00445a8d:
        mov dword ptr [ebp+3ADA74h],ebx
    L_00445a93:
        mov dword ptr [ebp+3ADA64h],ebx
    L_00445a99:
        mov byte ptr [ebp+3ADA68h],bl
    L_00445a9f:
        mov byte ptr [ebp+3ADA69h],bl
    L_00445aa5:
        mov dword ptr [ebp+3ADA60h],1
    L_00445aaf:
        mov byte ptr [ebp+3ADA6Ah],bl
    L_00445ab5:
        mov byte ptr [ebp+3ADA6Ch],0FFh
    L_00445abc:
        mov byte ptr [ebp+3ADA6Bh],bl
    L_00445ac2:
        mov dword ptr [ebp+4],0FFFFFFFFh
    L_00445ac9:
        mov dword ptr [ebp],0FFFFFFFFh
    L_00445ad0:
        lea edi,[ebp+68h]
    L_00445ad3:
        mov dword ptr [esp+10h],1000h
    L_00445adb:
        TH10_REL8(0xeb, 0x00445adb, VA_asm_GameStateInit_part_00445ae0)
    }
}

// 0x00445AE0..0x0044620A: GameStateInit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameStateInit_part_00445ae0() {
    __asm {
    L_00445ae0:
        mov edx,edi
    L_00445ae2:
        call asm_InitializeEntity_00401de0
    L_00445ae7:
        mov eax,dword ptr [esp+10h]
    L_00445aeb:
        add edi,3ACh
    L_00445af1:
        dec eax
    L_00445af2:
        mov dword ptr [esp+10h],eax
    L_00445af6:
        jne short L_00445ae0
    L_00445af8:
        push 24h
    L_00445afa:
        call asm_operator_new_00452493
    L_00445aff:
        add esp,4
    L_00445b02:
        cmp eax,ebx
    L_00445b04:
        je short L_00445b26
    L_00445b06:
        mov ecx,dword ptr [eax+4]
    L_00445b09:
        and ecx,esi
    L_00445b0b:
        mov dword ptr [eax+8],ebx
    L_00445b0e:
        mov dword ptr [eax+0Ch],ebx
    L_00445b11:
        mov dword ptr [eax+10h],ebx
    L_00445b14:
        mov dword ptr [eax],ebx
    L_00445b16:
        mov dword ptr [eax+4],ecx
    L_00445b19:
        mov dword ptr [eax+14h],eax
    L_00445b1c:
        mov dword ptr [eax+18h],ebx
    L_00445b1f:
        mov dword ptr [eax+1Ch],ebx
    L_00445b22:
        mov esi,eax
    L_00445b24:
        jmp short L_00445b28
    L_00445b26:
        xor esi,esi
    L_00445b28:
        mov eax,dword ptr [esi+4]
    L_00445b2b:
        mov ecx,dword ptr [data_00491be4]
    L_00445b31:
        or eax,3
    L_00445b34:
        push ecx
    L_00445b35:
        mov edi,1Ah
    L_00445b3a:
        mov dword ptr [esi+8],4485D0h
    L_00445b41:
        mov dword ptr [esi+0Ch],ebx
    L_00445b44:
        mov dword ptr [esi+10h],ebx
    L_00445b47:
        mov dword ptr [esi+20h],ebp
    L_00445b4a:
        mov dword ptr [esi+4],eax
    L_00445b4d:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_00445b52:
        push 24h
    L_00445b54:
        call asm_operator_new_00452493
    L_00445b59:
        add esp,4
    L_00445b5c:
        cmp eax,ebx
    L_00445b5e:
        je short L_00445b7f
    L_00445b60:
        mov ecx,dword ptr [eax+4]
    L_00445b63:
        mov dword ptr [eax+8],ebx
    L_00445b66:
        mov dword ptr [eax+0Ch],ebx
    L_00445b69:
        mov dword ptr [eax+10h],ebx
    L_00445b6c:
        mov dword ptr [eax],ebx
    L_00445b6e:
        and ecx,0FFFFFFFEh
    L_00445b71:
        mov dword ptr [eax+4],ecx
    L_00445b74:
        mov dword ptr [eax+14h],eax
    L_00445b77:
        mov dword ptr [eax+18h],ebx
    L_00445b7a:
        mov dword ptr [eax+1Ch],ebx
    L_00445b7d:
        jmp short L_00445b81
    L_00445b7f:
        xor eax,eax
    L_00445b81:
        mov ecx,dword ptr [eax+4]
    L_00445b84:
        mov edx,dword ptr [data_00491be4]
    L_00445b8a:
        or ecx,3
    L_00445b8d:
        push edx
    L_00445b8e:
        mov edi,8
    L_00445b93:
        mov esi,eax
    L_00445b95:
        mov dword ptr [eax+8],4485E0h
    L_00445b9c:
        mov dword ptr [eax+0Ch],ebx
    L_00445b9f:
        mov dword ptr [eax+10h],ebx
    L_00445ba2:
        mov dword ptr [eax+20h],ebp
    L_00445ba5:
        mov dword ptr [eax+4],ecx
    L_00445ba8:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_00445bad:
        push 24h
    L_00445baf:
        call asm_operator_new_00452493
    L_00445bb4:
        add esp,4
    L_00445bb7:
        cmp eax,ebx
    L_00445bb9:
        je short L_00445bda
    L_00445bbb:
        mov ecx,dword ptr [eax+4]
    L_00445bbe:
        mov dword ptr [eax+8],ebx
    L_00445bc1:
        mov dword ptr [eax+0Ch],ebx
    L_00445bc4:
        mov dword ptr [eax+10h],ebx
    L_00445bc7:
        mov dword ptr [eax],ebx
    L_00445bc9:
        and ecx,0FFFFFFFEh
    L_00445bcc:
        mov dword ptr [eax+4],ecx
    L_00445bcf:
        mov dword ptr [eax+14h],eax
    L_00445bd2:
        mov dword ptr [eax+18h],ebx
    L_00445bd5:
        mov dword ptr [eax+1Ch],ebx
    L_00445bd8:
        jmp short L_00445bdc
    L_00445bda:
        xor eax,eax
    L_00445bdc:
        or dword ptr [eax+4],3
    L_00445be0:
        mov ecx,dword ptr [data_00491be4]
    L_00445be6:
        push ecx
    L_00445be7:
        mov edi,9
    L_00445bec:
        mov esi,eax
    L_00445bee:
        mov dword ptr [eax+8],4485F0h
    L_00445bf5:
        mov dword ptr [eax+0Ch],ebx
    L_00445bf8:
        mov dword ptr [eax+10h],ebx
    L_00445bfb:
        mov dword ptr [eax+20h],ebp
    L_00445bfe:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00445c03:
        push 24h
    L_00445c05:
        call asm_operator_new_00452493
    L_00445c0a:
        add esp,4
    L_00445c0d:
        cmp eax,ebx
    L_00445c0f:
        je short L_00445c30
    L_00445c11:
        mov ecx,dword ptr [eax+4]
    L_00445c14:
        mov dword ptr [eax+8],ebx
    L_00445c17:
        mov dword ptr [eax+0Ch],ebx
    L_00445c1a:
        mov dword ptr [eax+10h],ebx
    L_00445c1d:
        mov dword ptr [eax],ebx
    L_00445c1f:
        and ecx,0FFFFFFFEh
    L_00445c22:
        mov dword ptr [eax+4],ecx
    L_00445c25:
        mov dword ptr [eax+14h],eax
    L_00445c28:
        mov dword ptr [eax+18h],ebx
    L_00445c2b:
        mov dword ptr [eax+1Ch],ebx
    L_00445c2e:
        jmp short L_00445c32
    L_00445c30:
        xor eax,eax
    L_00445c32:
        mov ecx,dword ptr [eax+4]
    L_00445c35:
        mov edx,dword ptr [data_00491be4]
    L_00445c3b:
        or ecx,3
    L_00445c3e:
        push edx
    L_00445c3f:
        mov edi,0Bh
    L_00445c44:
        mov esi,eax
    L_00445c46:
        mov dword ptr [eax+8],448600h
    L_00445c4d:
        mov dword ptr [eax+0Ch],ebx
    L_00445c50:
        mov dword ptr [eax+10h],ebx
    L_00445c53:
        mov dword ptr [eax+20h],ebp
    L_00445c56:
        mov dword ptr [eax+4],ecx
    L_00445c59:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00445c5e:
        push 24h
    L_00445c60:
        call asm_operator_new_00452493
    L_00445c65:
        add esp,4
    L_00445c68:
        cmp eax,ebx
    L_00445c6a:
        je short L_00445c8b
    L_00445c6c:
        mov ecx,dword ptr [eax+4]
    L_00445c6f:
        mov dword ptr [eax+8],ebx
    L_00445c72:
        mov dword ptr [eax+0Ch],ebx
    L_00445c75:
        mov dword ptr [eax+10h],ebx
    L_00445c78:
        mov dword ptr [eax],ebx
    L_00445c7a:
        and ecx,0FFFFFFFEh
    L_00445c7d:
        mov dword ptr [eax+4],ecx
    L_00445c80:
        mov dword ptr [eax+14h],eax
    L_00445c83:
        mov dword ptr [eax+18h],ebx
    L_00445c86:
        mov dword ptr [eax+1Ch],ebx
    L_00445c89:
        jmp short L_00445c8d
    L_00445c8b:
        xor eax,eax
    L_00445c8d:
        or dword ptr [eax+4],3
    L_00445c91:
        mov ecx,dword ptr [data_00491be4]
    L_00445c97:
        push ecx
    L_00445c98:
        mov edi,0Dh
    L_00445c9d:
        mov esi,eax
    L_00445c9f:
        mov dword ptr [eax+8],448610h
    L_00445ca6:
        mov dword ptr [eax+0Ch],ebx
    L_00445ca9:
        mov dword ptr [eax+10h],ebx
    L_00445cac:
        mov dword ptr [eax+20h],ebp
    L_00445caf:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00445cb4:
        push 24h
    L_00445cb6:
        call asm_operator_new_00452493
    L_00445cbb:
        add esp,4
    L_00445cbe:
        cmp eax,ebx
    L_00445cc0:
        je short L_00445ce1
    L_00445cc2:
        mov ecx,dword ptr [eax+4]
    L_00445cc5:
        mov dword ptr [eax+8],ebx
    L_00445cc8:
        mov dword ptr [eax+0Ch],ebx
    L_00445ccb:
        mov dword ptr [eax+10h],ebx
    L_00445cce:
        mov dword ptr [eax],ebx
    L_00445cd0:
        and ecx,0FFFFFFFEh
    L_00445cd3:
        mov dword ptr [eax+4],ecx
    L_00445cd6:
        mov dword ptr [eax+14h],eax
    L_00445cd9:
        mov dword ptr [eax+18h],ebx
    L_00445cdc:
        mov dword ptr [eax+1Ch],ebx
    L_00445cdf:
        jmp short L_00445ce3
    L_00445ce1:
        xor eax,eax
    L_00445ce3:
        mov ecx,dword ptr [eax+4]
    L_00445ce6:
        mov edx,dword ptr [data_00491be4]
    L_00445cec:
        or ecx,3
    L_00445cef:
        push edx
    L_00445cf0:
        mov edi,0Fh
    L_00445cf5:
        mov esi,eax
    L_00445cf7:
        mov dword ptr [eax+8],448620h
    L_00445cfe:
        mov dword ptr [eax+0Ch],ebx
    L_00445d01:
        mov dword ptr [eax+10h],ebx
    L_00445d04:
        mov dword ptr [eax+20h],ebp
    L_00445d07:
        mov dword ptr [eax+4],ecx
    L_00445d0a:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00445d0f:
        push 24h
    L_00445d11:
        call asm_operator_new_00452493
    L_00445d16:
        add esp,4
    L_00445d19:
        cmp eax,ebx
    L_00445d1b:
        je short L_00445d3c
    L_00445d1d:
        mov ecx,dword ptr [eax+4]
    L_00445d20:
        mov dword ptr [eax+8],ebx
    L_00445d23:
        mov dword ptr [eax+0Ch],ebx
    L_00445d26:
        mov dword ptr [eax+10h],ebx
    L_00445d29:
        mov dword ptr [eax],ebx
    L_00445d2b:
        and ecx,0FFFFFFFEh
    L_00445d2e:
        mov dword ptr [eax+4],ecx
    L_00445d31:
        mov dword ptr [eax+14h],eax
    L_00445d34:
        mov dword ptr [eax+18h],ebx
    L_00445d37:
        mov dword ptr [eax+1Ch],ebx
    L_00445d3a:
        jmp short L_00445d3e
    L_00445d3c:
        xor eax,eax
    L_00445d3e:
        or dword ptr [eax+4],3
    L_00445d42:
        mov ecx,dword ptr [data_00491be4]
    L_00445d48:
        push ecx
    L_00445d49:
        mov edi,10h
    L_00445d4e:
        mov esi,eax
    L_00445d50:
        mov dword ptr [eax+8],4486A0h
    L_00445d57:
        mov dword ptr [eax+0Ch],ebx
    L_00445d5a:
        mov dword ptr [eax+10h],ebx
    L_00445d5d:
        mov dword ptr [eax+20h],ebp
    L_00445d60:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00445d65:
        push 24h
    L_00445d67:
        call asm_operator_new_00452493
    L_00445d6c:
        add esp,4
    L_00445d6f:
        cmp eax,ebx
    L_00445d71:
        je short L_00445d92
    L_00445d73:
        mov ecx,dword ptr [eax+4]
    L_00445d76:
        mov dword ptr [eax+8],ebx
    L_00445d79:
        mov dword ptr [eax+0Ch],ebx
    L_00445d7c:
        mov dword ptr [eax+10h],ebx
    L_00445d7f:
        mov dword ptr [eax],ebx
    L_00445d81:
        and ecx,0FFFFFFFEh
    L_00445d84:
        mov dword ptr [eax+4],ecx
    L_00445d87:
        mov dword ptr [eax+14h],eax
    L_00445d8a:
        mov dword ptr [eax+18h],ebx
    L_00445d8d:
        mov dword ptr [eax+1Ch],ebx
    L_00445d90:
        jmp short L_00445d94
    L_00445d92:
        xor eax,eax
    L_00445d94:
        mov ecx,dword ptr [eax+4]
    L_00445d97:
        mov edx,dword ptr [data_00491be4]
    L_00445d9d:
        or ecx,3
    L_00445da0:
        push edx
    L_00445da1:
        mov edi,11h
    L_00445da6:
        mov esi,eax
    L_00445da8:
        mov dword ptr [eax+8],4486B0h
    L_00445daf:
        mov dword ptr [eax+0Ch],ebx
    L_00445db2:
        mov dword ptr [eax+10h],ebx
    L_00445db5:
        mov dword ptr [eax+20h],ebp
    L_00445db8:
        mov dword ptr [eax+4],ecx
    L_00445dbb:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00445dc0:
        push 24h
    L_00445dc2:
        call asm_operator_new_00452493
    L_00445dc7:
        add esp,4
    L_00445dca:
        cmp eax,ebx
    L_00445dcc:
        je short L_00445ded
    L_00445dce:
        mov ecx,dword ptr [eax+4]
    L_00445dd1:
        mov dword ptr [eax+8],ebx
    L_00445dd4:
        mov dword ptr [eax+0Ch],ebx
    L_00445dd7:
        mov dword ptr [eax+10h],ebx
    L_00445dda:
        mov dword ptr [eax],ebx
    L_00445ddc:
        and ecx,0FFFFFFFEh
    L_00445ddf:
        mov dword ptr [eax+4],ecx
    L_00445de2:
        mov dword ptr [eax+14h],eax
    L_00445de5:
        mov dword ptr [eax+18h],ebx
    L_00445de8:
        mov dword ptr [eax+1Ch],ebx
    L_00445deb:
        jmp short L_00445def
    L_00445ded:
        xor eax,eax
    L_00445def:
        or dword ptr [eax+4],3
    L_00445df3:
        mov ecx,dword ptr [data_00491be4]
    L_00445df9:
        push ecx
    L_00445dfa:
        mov edi,12h
    L_00445dff:
        mov esi,eax
    L_00445e01:
        mov dword ptr [eax+8],4486C0h
    L_00445e08:
        mov dword ptr [eax+0Ch],ebx
    L_00445e0b:
        mov dword ptr [eax+10h],ebx
    L_00445e0e:
        mov dword ptr [eax+20h],ebp
    L_00445e11:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00445e16:
        push 24h
    L_00445e18:
        call asm_operator_new_00452493
    L_00445e1d:
        add esp,4
    L_00445e20:
        cmp eax,ebx
    L_00445e22:
        je short L_00445e43
    L_00445e24:
        mov ecx,dword ptr [eax+4]
    L_00445e27:
        mov dword ptr [eax+8],ebx
    L_00445e2a:
        mov dword ptr [eax+0Ch],ebx
    L_00445e2d:
        mov dword ptr [eax+10h],ebx
    L_00445e30:
        mov dword ptr [eax],ebx
    L_00445e32:
        and ecx,0FFFFFFFEh
    L_00445e35:
        mov dword ptr [eax+4],ecx
    L_00445e38:
        mov dword ptr [eax+14h],eax
    L_00445e3b:
        mov dword ptr [eax+18h],ebx
    L_00445e3e:
        mov dword ptr [eax+1Ch],ebx
    L_00445e41:
        jmp short L_00445e45
    L_00445e43:
        xor eax,eax
    L_00445e45:
        mov ecx,dword ptr [eax+4]
    L_00445e48:
        mov edx,dword ptr [data_00491be4]
    L_00445e4e:
        or ecx,3
    L_00445e51:
        push edx
    L_00445e52:
        mov edi,13h
    L_00445e57:
        mov esi,eax
    L_00445e59:
        mov dword ptr [eax+8],4486D0h
    L_00445e60:
        mov dword ptr [eax+0Ch],ebx
    L_00445e63:
        mov dword ptr [eax+10h],ebx
    L_00445e66:
        mov dword ptr [eax+20h],ebp
    L_00445e69:
        mov dword ptr [eax+4],ecx
    L_00445e6c:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00445e71:
        push 24h
    L_00445e73:
        call asm_operator_new_00452493
    L_00445e78:
        add esp,4
    L_00445e7b:
        cmp eax,ebx
    L_00445e7d:
        je short L_00445e9e
    L_00445e7f:
        mov ecx,dword ptr [eax+4]
    L_00445e82:
        mov dword ptr [eax+8],ebx
    L_00445e85:
        mov dword ptr [eax+0Ch],ebx
    L_00445e88:
        mov dword ptr [eax+10h],ebx
    L_00445e8b:
        mov dword ptr [eax],ebx
    L_00445e8d:
        and ecx,0FFFFFFFEh
    L_00445e90:
        mov dword ptr [eax+4],ecx
    L_00445e93:
        mov dword ptr [eax+14h],eax
    L_00445e96:
        mov dword ptr [eax+18h],ebx
    L_00445e99:
        mov dword ptr [eax+1Ch],ebx
    L_00445e9c:
        jmp short L_00445ea0
    L_00445e9e:
        xor eax,eax
    L_00445ea0:
        or dword ptr [eax+4],3
    L_00445ea4:
        mov ecx,dword ptr [data_00491be4]
    L_00445eaa:
        push ecx
    L_00445eab:
        mov edi,15h
    L_00445eb0:
        mov esi,eax
    L_00445eb2:
        mov dword ptr [eax+8],4486E0h
    L_00445eb9:
        mov dword ptr [eax+0Ch],ebx
    L_00445ebc:
        mov dword ptr [eax+10h],ebx
    L_00445ebf:
        mov dword ptr [eax+20h],ebp
    L_00445ec2:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00445ec7:
        push 24h
    L_00445ec9:
        call asm_operator_new_00452493
    L_00445ece:
        add esp,4
    L_00445ed1:
        cmp eax,ebx
    L_00445ed3:
        je short L_00445ef4
    L_00445ed5:
        mov ecx,dword ptr [eax+4]
    L_00445ed8:
        mov dword ptr [eax+8],ebx
    L_00445edb:
        mov dword ptr [eax+0Ch],ebx
    L_00445ede:
        mov dword ptr [eax+10h],ebx
    L_00445ee1:
        mov dword ptr [eax],ebx
    L_00445ee3:
        and ecx,0FFFFFFFEh
    L_00445ee6:
        mov dword ptr [eax+4],ecx
    L_00445ee9:
        mov dword ptr [eax+14h],eax
    L_00445eec:
        mov dword ptr [eax+18h],ebx
    L_00445eef:
        mov dword ptr [eax+1Ch],ebx
    L_00445ef2:
        jmp short L_00445ef6
    L_00445ef4:
        xor eax,eax
    L_00445ef6:
        mov ecx,dword ptr [eax+4]
    L_00445ef9:
        mov edx,dword ptr [data_00491be4]
    L_00445eff:
        or ecx,3
    L_00445f02:
        push edx
    L_00445f03:
        mov edi,17h
    L_00445f08:
        mov esi,eax
    L_00445f0a:
        mov dword ptr [eax+8],4486F0h
    L_00445f11:
        mov dword ptr [eax+0Ch],ebx
    L_00445f14:
        mov dword ptr [eax+10h],ebx
    L_00445f17:
        mov dword ptr [eax+20h],ebp
    L_00445f1a:
        mov dword ptr [eax+4],ecx
    L_00445f1d:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00445f22:
        push 24h
    L_00445f24:
        call asm_operator_new_00452493
    L_00445f29:
        add esp,4
    L_00445f2c:
        cmp eax,ebx
    L_00445f2e:
        je short L_00445f4f
    L_00445f30:
        mov ecx,dword ptr [eax+4]
    L_00445f33:
        mov dword ptr [eax+8],ebx
    L_00445f36:
        mov dword ptr [eax+0Ch],ebx
    L_00445f39:
        mov dword ptr [eax+10h],ebx
    L_00445f3c:
        mov dword ptr [eax],ebx
    L_00445f3e:
        and ecx,0FFFFFFFEh
    L_00445f41:
        mov dword ptr [eax+4],ecx
    L_00445f44:
        mov dword ptr [eax+14h],eax
    L_00445f47:
        mov dword ptr [eax+18h],ebx
    L_00445f4a:
        mov dword ptr [eax+1Ch],ebx
    L_00445f4d:
        jmp short L_00445f51
    L_00445f4f:
        xor eax,eax
    L_00445f51:
        or dword ptr [eax+4],3
    L_00445f55:
        mov ecx,dword ptr [data_00491be4]
    L_00445f5b:
        push ecx
    L_00445f5c:
        mov edi,18h
    L_00445f61:
        mov esi,eax
    L_00445f63:
        mov dword ptr [eax+8],448700h
    L_00445f6a:
        mov dword ptr [eax+0Ch],ebx
    L_00445f6d:
        mov dword ptr [eax+10h],ebx
    L_00445f70:
        mov dword ptr [eax+20h],ebp
    L_00445f73:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00445f78:
        push 24h
    L_00445f7a:
        call asm_operator_new_00452493
    L_00445f7f:
        add esp,4
    L_00445f82:
        cmp eax,ebx
    L_00445f84:
        je short L_00445fa5
    L_00445f86:
        mov ecx,dword ptr [eax+4]
    L_00445f89:
        mov dword ptr [eax+8],ebx
    L_00445f8c:
        mov dword ptr [eax+0Ch],ebx
    L_00445f8f:
        mov dword ptr [eax+10h],ebx
    L_00445f92:
        mov dword ptr [eax],ebx
    L_00445f94:
        and ecx,0FFFFFFFEh
    L_00445f97:
        mov dword ptr [eax+4],ecx
    L_00445f9a:
        mov dword ptr [eax+14h],eax
    L_00445f9d:
        mov dword ptr [eax+18h],ebx
    L_00445fa0:
        mov dword ptr [eax+1Ch],ebx
    L_00445fa3:
        jmp short L_00445fa7
    L_00445fa5:
        xor eax,eax
    L_00445fa7:
        mov ecx,dword ptr [eax+4]
    L_00445faa:
        mov edx,dword ptr [data_00491be4]
    L_00445fb0:
        or ecx,3
    L_00445fb3:
        push edx
    L_00445fb4:
        mov edi,1Ah
    L_00445fb9:
        mov esi,eax
    L_00445fbb:
        mov dword ptr [eax+8],448710h
    L_00445fc2:
        mov dword ptr [eax+0Ch],ebx
    L_00445fc5:
        mov dword ptr [eax+10h],ebx
    L_00445fc8:
        mov dword ptr [eax+20h],ebp
    L_00445fcb:
        mov dword ptr [eax+4],ecx
    L_00445fce:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00445fd3:
        push 24h
    L_00445fd5:
        call asm_operator_new_00452493
    L_00445fda:
        add esp,4
    L_00445fdd:
        cmp eax,ebx
    L_00445fdf:
        je short L_00446000
    L_00445fe1:
        mov ecx,dword ptr [eax+4]
    L_00445fe4:
        mov dword ptr [eax+8],ebx
    L_00445fe7:
        mov dword ptr [eax+0Ch],ebx
    L_00445fea:
        mov dword ptr [eax+10h],ebx
    L_00445fed:
        mov dword ptr [eax],ebx
    L_00445fef:
        and ecx,0FFFFFFFEh
    L_00445ff2:
        mov dword ptr [eax+4],ecx
    L_00445ff5:
        mov dword ptr [eax+14h],eax
    L_00445ff8:
        mov dword ptr [eax+18h],ebx
    L_00445ffb:
        mov dword ptr [eax+1Ch],ebx
    L_00445ffe:
        jmp short L_00446002
    L_00446000:
        xor eax,eax
    L_00446002:
        or dword ptr [eax+4],3
    L_00446006:
        mov ecx,dword ptr [data_00491be4]
    L_0044600c:
        push ecx
    L_0044600d:
        mov edi,1Ch
    L_00446012:
        mov esi,eax
    L_00446014:
        mov dword ptr [eax+8],448720h
    L_0044601b:
        mov dword ptr [eax+0Ch],ebx
    L_0044601e:
        mov dword ptr [eax+10h],ebx
    L_00446021:
        mov dword ptr [eax+20h],ebp
    L_00446024:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00446029:
        push 24h
    L_0044602b:
        call asm_operator_new_00452493
    L_00446030:
        add esp,4
    L_00446033:
        cmp eax,ebx
    L_00446035:
        je short L_00446056
    L_00446037:
        mov ecx,dword ptr [eax+4]
    L_0044603a:
        mov dword ptr [eax+8],ebx
    L_0044603d:
        mov dword ptr [eax+0Ch],ebx
    L_00446040:
        mov dword ptr [eax+10h],ebx
    L_00446043:
        mov dword ptr [eax],ebx
    L_00446045:
        and ecx,0FFFFFFFEh
    L_00446048:
        mov dword ptr [eax+4],ecx
    L_0044604b:
        mov dword ptr [eax+14h],eax
    L_0044604e:
        mov dword ptr [eax+18h],ebx
    L_00446051:
        mov dword ptr [eax+1Ch],ebx
    L_00446054:
        jmp short L_00446058
    L_00446056:
        xor eax,eax
    L_00446058:
        mov ecx,dword ptr [eax+4]
    L_0044605b:
        mov edx,dword ptr [data_00491be4]
    L_00446061:
        or ecx,3
    L_00446064:
        push edx
    L_00446065:
        mov edi,21h
    L_0044606a:
        mov esi,eax
    L_0044606c:
        mov dword ptr [eax+8],448730h
    L_00446073:
        mov dword ptr [eax+0Ch],ebx
    L_00446076:
        mov dword ptr [eax+10h],ebx
    L_00446079:
        mov dword ptr [eax+20h],ebp
    L_0044607c:
        mov dword ptr [eax+4],ecx
    L_0044607f:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00446084:
        push 24h
    L_00446086:
        call asm_operator_new_00452493
    L_0044608b:
        add esp,4
    L_0044608e:
        cmp eax,ebx
    L_00446090:
        je short L_004460b1
    L_00446092:
        mov ecx,dword ptr [eax+4]
    L_00446095:
        mov dword ptr [eax+8],ebx
    L_00446098:
        mov dword ptr [eax+0Ch],ebx
    L_0044609b:
        mov dword ptr [eax+10h],ebx
    L_0044609e:
        mov dword ptr [eax],ebx
    L_004460a0:
        and ecx,0FFFFFFFEh
    L_004460a3:
        mov dword ptr [eax+4],ecx
    L_004460a6:
        mov dword ptr [eax+14h],eax
    L_004460a9:
        mov dword ptr [eax+18h],ebx
    L_004460ac:
        mov dword ptr [eax+1Ch],ebx
    L_004460af:
        jmp short L_004460b3
    L_004460b1:
        xor eax,eax
    L_004460b3:
        or dword ptr [eax+4],3
    L_004460b7:
        mov ecx,dword ptr [data_00491be4]
    L_004460bd:
        push ecx
    L_004460be:
        mov edi,24h
    L_004460c3:
        mov esi,eax
    L_004460c5:
        mov dword ptr [eax+8],448740h
    L_004460cc:
        mov dword ptr [eax+0Ch],ebx
    L_004460cf:
        mov dword ptr [eax+10h],ebx
    L_004460d2:
        mov dword ptr [eax+20h],ebp
    L_004460d5:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004460da:
        push edi
    L_004460db:
        call asm_operator_new_00452493
    L_004460e0:
        add esp,4
    L_004460e3:
        cmp eax,ebx
    L_004460e5:
        je short L_00446106
    L_004460e7:
        mov ecx,dword ptr [eax+4]
    L_004460ea:
        mov dword ptr [eax+8],ebx
    L_004460ed:
        mov dword ptr [eax+0Ch],ebx
    L_004460f0:
        mov dword ptr [eax+10h],ebx
    L_004460f3:
        mov dword ptr [eax],ebx
    L_004460f5:
        and ecx,0FFFFFFFEh
    L_004460f8:
        mov dword ptr [eax+4],ecx
    L_004460fb:
        mov dword ptr [eax+14h],eax
    L_004460fe:
        mov dword ptr [eax+18h],ebx
    L_00446101:
        mov dword ptr [eax+1Ch],ebx
    L_00446104:
        jmp short L_00446108
    L_00446106:
        xor eax,eax
    L_00446108:
        mov ecx,dword ptr [eax+4]
    L_0044610b:
        mov edx,dword ptr [data_00491be4]
    L_00446111:
        or ecx,3
    L_00446114:
        push edx
    L_00446115:
        mov edi,29h
    L_0044611a:
        mov esi,eax
    L_0044611c:
        mov dword ptr [eax+8],448770h
    L_00446123:
        mov dword ptr [eax+0Ch],ebx
    L_00446126:
        mov dword ptr [eax+10h],ebx
    L_00446129:
        mov dword ptr [eax+20h],ebp
    L_0044612c:
        mov dword ptr [eax+4],ecx
    L_0044612f:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00446134:
        push 24h
    L_00446136:
        call asm_operator_new_00452493
    L_0044613b:
        add esp,4
    L_0044613e:
        cmp eax,ebx
    L_00446140:
        je short L_00446161
    L_00446142:
        mov ecx,dword ptr [eax+4]
    L_00446145:
        mov dword ptr [eax+8],ebx
    L_00446148:
        mov dword ptr [eax+0Ch],ebx
    L_0044614b:
        mov dword ptr [eax+10h],ebx
    L_0044614e:
        mov dword ptr [eax],ebx
    L_00446150:
        and ecx,0FFFFFFFEh
    L_00446153:
        mov dword ptr [eax+4],ecx
    L_00446156:
        mov dword ptr [eax+14h],eax
    L_00446159:
        mov dword ptr [eax+18h],ebx
    L_0044615c:
        mov dword ptr [eax+1Ch],ebx
    L_0044615f:
        jmp short L_00446163
    L_00446161:
        xor eax,eax
    L_00446163:
        or dword ptr [eax+4],3
    L_00446167:
        mov ecx,dword ptr [data_00491be4]
    L_0044616d:
        push ecx
    L_0044616e:
        mov edi,2Ah
    L_00446173:
        mov esi,eax
    L_00446175:
        mov dword ptr [eax+8],4487C0h
    L_0044617c:
        mov dword ptr [eax+0Ch],ebx
    L_0044617f:
        mov dword ptr [eax+10h],ebx
    L_00446182:
        mov dword ptr [eax+20h],ebp
    L_00446185:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0044618a:
        push 24h
    L_0044618c:
        call asm_operator_new_00452493
    L_00446191:
        add esp,4
    L_00446194:
        cmp eax,ebx
    L_00446196:
        je short L_004461b7
    L_00446198:
        mov ecx,dword ptr [eax+4]
    L_0044619b:
        mov dword ptr [eax+8],ebx
    L_0044619e:
        mov dword ptr [eax+0Ch],ebx
    L_004461a1:
        mov dword ptr [eax+10h],ebx
    L_004461a4:
        mov dword ptr [eax],ebx
    L_004461a6:
        and ecx,0FFFFFFFEh
    L_004461a9:
        mov dword ptr [eax+4],ecx
    L_004461ac:
        mov dword ptr [eax+14h],eax
    L_004461af:
        mov dword ptr [eax+18h],ebx
    L_004461b2:
        mov dword ptr [eax+1Ch],ebx
    L_004461b5:
        jmp short L_004461b9
    L_004461b7:
        xor eax,eax
    L_004461b9:
        mov ecx,dword ptr [eax+4]
    L_004461bc:
        mov edx,dword ptr [data_00491be4]
    L_004461c2:
        or ecx,3
    L_004461c5:
        push edx
    L_004461c6:
        mov edi,2Dh
    L_004461cb:
        mov esi,eax
    L_004461cd:
        mov dword ptr [eax+8],448810h
    L_004461d4:
        mov dword ptr [eax+0Ch],ebx
    L_004461d7:
        mov dword ptr [eax+10h],ebx
    L_004461da:
        mov dword ptr [eax+20h],ebp
    L_004461dd:
        mov dword ptr [eax+4],ecx
    L_004461e0:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004461e5:
        mov eax,dword ptr [data_00491c30]
    L_004461ea:
        mov ecx,dword ptr [eax]
    L_004461ec:
        push ebx
    L_004461ed:
        push eax
    L_004461ee:
        call dword ptr [ecx+170h]
    L_004461f4:
        mov ecx,dword ptr [esp+14h]
    L_004461f8:
        pop edi
    L_004461f9:
        pop esi
    L_004461fa:
        mov eax,ebp
    L_004461fc:
        pop ebp
    L_004461fd:
        pop ebx
    L_004461fe:
        mov dword ptr fs:[0],ecx
    L_00446205:
        add esp,10h
    L_00446208:
        ret 4
    }
}
