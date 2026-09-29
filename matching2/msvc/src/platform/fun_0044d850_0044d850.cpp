#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// Full typed candidate (including the 0x0044D9F0 continuation):
// reference/semantic_candidates/sound_stream_service.cpp. The busy check uses
// the DirectSound write cursor. Repeat reads rewind to the music loop start.
// See recovery_notes/sound_stream_restart_service_worker.md; native matching
// remains pending for both manifest rows and their private helper edges.

// 0x0044D850..0x0044D9EC: FUN_0044d850
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044d850_0044d850() {
    __asm {
    L_0044d850:
        sub esp,1Ch
    L_0044d853:
        push ebp
    L_0044d854:
        mov ebp,dword ptr [esp+24h]
    L_0044d858:
        mov eax,dword ptr [ebp+4]
    L_0044d85b:
        push edi
    L_0044d85c:
        xor edi,edi
    L_0044d85e:
        cmp eax,edi
    L_0044d860:
        je asm_target_0044dac0
    L_0044d866:
        cmp dword ptr [ebp+0Ch],edi
    L_0044d869:
        je asm_target_0044dac0
    L_0044d86f:
        mov eax,dword ptr [eax]
    L_0044d871:
        mov ecx,dword ptr [eax]
    L_0044d873:
        push ebx
    L_0044d874:
        lea edx,[esp+18h]
    L_0044d878:
        push edx
    L_0044d879:
        lea edx,[esp+24h]
    L_0044d87d:
        push edx
    L_0044d87e:
        push eax
    L_0044d87f:
        call dword ptr [ecx+10h]
    L_0044d882:
        mov ecx,dword ptr [esp+18h]
    L_0044d886:
        mov ebx,dword ptr [ebp+6Ch]
    L_0044d889:
        mov eax,dword ptr [ebp+64h]
    L_0044d88c:
        mov edx,ecx
    L_0044d88e:
        sub edx,ebx
    L_0044d890:
        cmp eax,edx
    L_0044d892:
        jb short L_0044d8a6
    L_0044d894:
        cmp eax,ecx
    L_0044d896:
        jae short L_0044d8a6
    L_0044d898:
        pop ebx
    L_0044d899:
        pop edi
    L_0044d89a:
        mov eax,800401F0h
    L_0044d89f:
        pop ebp
    L_0044d8a0:
        add esp,1Ch
    L_0044d8a3:
        ret 8
    L_0044d8a6:
        mov eax,dword ptr [ebp+4]
    L_0044d8a9:
        push esi
    L_0044d8aa:
        mov esi,dword ptr [eax]
    L_0044d8ac:
        lea ebx,[esp+14h]
    L_0044d8b0:
        call asm_Platform_RunInterface_0044d300
    L_0044d8b5:
        cmp eax,edi
    L_0044d8b7:
        jl short L_0044d8d7
    L_0044d8b9:
        cmp dword ptr [esp+14h],edi
    L_0044d8bd:
        push edi
    L_0044d8be:
        je short L_0044d8e1
    L_0044d8c0:
        mov ecx,dword ptr [ebp+4]
    L_0044d8c3:
        mov edx,dword ptr [ecx]
    L_0044d8c5:
        push edx
    L_0044d8c6:
        mov eax,ebp
    L_0044d8c8:
        call asm_Streamer_FillBufferRetail_0044d110
    L_0044d8cd:
        xor ecx,ecx
    L_0044d8cf:
        cmp eax,edi
    L_0044d8d1:
        setge cl
    L_0044d8d4:
        dec ecx
    L_0044d8d5:
        and eax,ecx
    L_0044d8d7:
        pop esi
    L_0044d8d8:
        pop ebx
    L_0044d8d9:
        pop edi
    L_0044d8da:
        pop ebp
    L_0044d8db:
        add esp,1Ch
    L_0044d8de:
        ret 8
    L_0044d8e1:
        mov edx,dword ptr [ebp+4]
    L_0044d8e4:
        mov dword ptr [esp+14h],edi
    L_0044d8e8:
        mov dword ptr [esp+1Ch],edi
    L_0044d8ec:
        mov eax,dword ptr [edx]
    L_0044d8ee:
        mov ecx,dword ptr [eax]
    L_0044d8f0:
        lea edx,[esp+2Ch]
    L_0044d8f4:
        push edx
    L_0044d8f5:
        lea edx,[esp+20h]
    L_0044d8f9:
        push edx
    L_0044d8fa:
        lea edx,[esp+3Ch]
    L_0044d8fe:
        push edx
    L_0044d8ff:
        lea edx,[esp+20h]
    L_0044d903:
        push edx
    L_0044d904:
        mov edx,dword ptr [ebp+6Ch]
    L_0044d907:
        push edx
    L_0044d908:
        mov edx,dword ptr [ebp+64h]
    L_0044d90b:
        push edx
    L_0044d90c:
        push eax
    L_0044d90d:
        call dword ptr [ecx+2Ch]
    L_0044d910:
        cmp eax,edi
    L_0044d912:
        jl short L_0044d8d7
    L_0044d914:
        cmp dword ptr [esp+18h],edi
    L_0044d918:
        je short L_0044d929
    L_0044d91a:
        pop esi
    L_0044d91b:
        pop ebx
    L_0044d91c:
        pop edi
    L_0044d91d:
        mov eax,8000FFFFh
    L_0044d922:
        pop ebp
    L_0044d923:
        add esp,1Ch
    L_0044d926:
        ret 8
    L_0044d929:
        cmp dword ptr [ebp+68h],edi
    L_0044d92c:
        jne short L_0044d9ad
    L_0044d92e:
        mov ecx,dword ptr [esp+10h]
    L_0044d932:
        mov edx,dword ptr [esp+30h]
    L_0044d936:
        lea eax,[esp+14h]
    L_0044d93a:
        push eax
    L_0044d93b:
        mov eax,dword ptr [ebp+0Ch]
    L_0044d93e:
        push ecx
    L_0044d93f:
        call asm_ArchiveCursor_ReadRetail_0044de10
    L_0044d944:
        cmp eax,edi
    L_0044d946:
        jl short L_0044d8d7
    L_0044d948:
        mov edi,dword ptr [esp+14h]
    L_0044d94c:
        mov ecx,dword ptr [esp+30h]
    L_0044d950:
        cmp edi,ecx
    L_0044d952:
        jae asm_target_0044da33
    L_0044d958:
        mov eax,dword ptr [esp+34h]
    L_0044d95c:
        test eax,eax
    L_0044d95e:
        jne asm_FUN_0044d850_part_0044d9f0
    L_0044d964:
        mov eax,dword ptr [ebp+0Ch]
    L_0044d967:
        mov edx,dword ptr [eax+90h]
    L_0044d96d:
        sub ecx,edi
    L_0044d96f:
        cmp word ptr [edx+2Eh],8
    L_0044d974:
        mov edx,dword ptr [esp+10h]
    L_0044d978:
        setne al
    L_0044d97b:
        dec al
    L_0044d97d:
        add edi,edx
    L_0044d97f:
        mov edx,ecx
    L_0044d981:
        shr ecx,2
    L_0044d984:
        and eax,80h
    L_0044d989:
        movzx eax,al
    L_0044d98c:
        mov bl,al
    L_0044d98e:
        mov bh,bl
    L_0044d990:
        mov eax,ebx
    L_0044d992:
        shl eax,10h
    L_0044d995:
        mov ax,bx
    L_0044d998:
        rep stosd
    L_0044d99a:
        mov ecx,edx
    L_0044d99c:
        and ecx,3
    L_0044d99f:
        rep stosb
    L_0044d9a1:
        mov dword ptr [ebp+68h],1
    L_0044d9a8:
        jmp asm_target_0044da33
    L_0044d9ad:
        mov edx,dword ptr [ebp+0Ch]
    L_0044d9b0:
        mov eax,dword ptr [edx+90h]
    L_0044d9b6:
        cmp word ptr [eax+2Eh],8
    L_0044d9bb:
        mov ecx,dword ptr [esp+30h]
    L_0044d9bf:
        setne dl
    L_0044d9c2:
        dec dl
    L_0044d9c4:
        mov edi,dword ptr [esp+10h]
    L_0044d9c8:
        and edx,80h
    L_0044d9ce:
        movzx eax,dl
    L_0044d9d1:
        mov bl,al
    L_0044d9d3:
        mov bh,bl
    L_0044d9d5:
        mov edx,ecx
    L_0044d9d7:
        shr ecx,2
    L_0044d9da:
        mov eax,ebx
    L_0044d9dc:
        shl eax,10h
    L_0044d9df:
        mov ax,bx
    L_0044d9e2:
        rep stosd
    L_0044d9e4:
        mov ecx,edx
    L_0044d9e6:
        and ecx,3
    L_0044d9e9:
        rep stosb
    L_0044d9eb:
        TH10_REL8(0xeb, 0x0044d9eb, VA_asm_target_0044da33)
    }
}
