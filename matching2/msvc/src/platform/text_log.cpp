#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044B810..0x0044B8D8: ?TextLog_Append@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_TextLog_Append_0044b810() {
    __asm {
    L_0044b810:
        mov eax,2004h
    L_0044b815:
        call asm_chkstk_00458ec0
    L_0044b81a:
        mov eax,dword ptr [data_00473660]
    L_0044b81f:
        xor eax,esp
    L_0044b821:
        push esi
    L_0044b822:
        push edi
    L_0044b823:
        push 4922BCh
    L_0044b828:
        mov dword ptr [esp+200Ch],eax
    L_0044b82f:
        mov edi,ecx
    L_0044b831:
        call dword ptr [data_004660b0]
    L_0044b837:
        mov al,byte ptr [data_0049231f]
    L_0044b83c:
        mov ecx,dword ptr [esp+2010h]
    L_0044b843:
        inc al
    L_0044b845:
        mov byte ptr [data_0049231f],al
    L_0044b84a:
        lea eax,[esp+2014h]
    L_0044b851:
        push eax
    L_0044b852:
        push ecx
    L_0044b853:
        lea edx,[esp+10h]
    L_0044b857:
        push edx
    L_0044b858:
        call asm_vsprintf_004524a6
    L_0044b85d:
        lea eax,[esp+14h]
    L_0044b861:
        add esp,0Ch
    L_0044b864:
        lea edx,[eax+1]
    L_0044b867:
        mov cl,byte ptr [eax]
    L_0044b869:
        inc eax
    L_0044b86a:
        test cl,cl
    L_0044b86c:
        jne short L_0044b867
    L_0044b86e:
        mov esi,dword ptr [edi+2000h]
    L_0044b874:
        sub eax,edx
    L_0044b876:
        lea ecx,[esi+eax]
    L_0044b879:
        lea edx,[edi+1FFFh]
    L_0044b87f:
        cmp ecx,edx
    L_0044b881:
        jae short L_0044b8a4
    L_0044b883:
        lea edx,[esp+8]
    L_0044b887:
        mov cl,byte ptr [edx]
    L_0044b889:
        inc edx
    L_0044b88a:
        mov byte ptr [esi],cl
    L_0044b88c:
        inc esi
    L_0044b88d:
        test cl,cl
    L_0044b88f:
        jne short L_0044b887
    L_0044b891:
        mov ecx,dword ptr [edi+2000h]
    L_0044b897:
        add ecx,eax
    L_0044b899:
        mov dword ptr [edi+2000h],ecx
    L_0044b89f:
        mov edi,ecx
    L_0044b8a1:
        mov byte ptr [edi],0
    L_0044b8a4:
        push 4922BCh
    L_0044b8a9:
        call dword ptr [data_004660b4]
    L_0044b8af:
        mov al,byte ptr [data_0049231f]
    L_0044b8b4:
        mov ecx,dword ptr [esp+2008h]
    L_0044b8bb:
        dec al
    L_0044b8bd:
        pop edi
    L_0044b8be:
        pop esi
    L_0044b8bf:
        mov byte ptr [data_0049231f],al
    L_0044b8c4:
        mov eax,dword ptr [esp+2008h]
    L_0044b8cb:
        xor ecx,esp
    L_0044b8cd:
        call asm_security_check_cookie_00458ea5
    L_0044b8d2:
        add esp,2004h
    L_0044b8d8:
        ret
    }
}

