#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044B810..0x0044B8D8: ?TextLog_Append@@
// Naked body preserves the retail register/stack ABI.

// 0x0044B8E0..0x0044B9A8: TextLog_AppendLine
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_TextLog_AppendLine_0044b8e0() {
    __asm {
    L_0044b8e0:
        sub esp,204h
    L_0044b8e6:
        mov eax,dword ptr [data_00473660]
    L_0044b8eb:
        xor eax,esp
    L_0044b8ed:
        push 4922BCh
    L_0044b8f2:
        mov dword ptr [esp+204h],eax
    L_0044b8f9:
        call dword ptr [data_004660b0]
    L_0044b8ff:
        mov al,byte ptr [data_0049231f]
    L_0044b904:
        mov ecx,dword ptr [esp+208h]
    L_0044b90b:
        inc al
    L_0044b90d:
        mov byte ptr [data_0049231f],al
    L_0044b912:
        lea eax,[esp+20Ch]
    L_0044b919:
        push eax
    L_0044b91a:
        push ecx
    L_0044b91b:
        lea edx,[esp+8]
    L_0044b91f:
        push edx
    L_0044b920:
        call asm_vsprintf_004524a6
    L_0044b925:
        lea eax,[esp+0Ch]
    L_0044b929:
        add esp,0Ch
    L_0044b92c:
        lea edx,[eax+1]
    L_0044b92f:
        nop
    L_0044b930:
        mov cl,byte ptr [eax]
    L_0044b932:
        inc eax
    L_0044b933:
        test cl,cl
    L_0044b935:
        jne short L_0044b930
    L_0044b937:
        sub eax,edx
    L_0044b939:
        push esi
    L_0044b93a:
        mov esi,dword ptr [edi+2000h]
    L_0044b940:
        lea ecx,[esi+eax]
    L_0044b943:
        lea edx,[edi+1FFFh]
    L_0044b949:
        cmp ecx,edx
    L_0044b94b:
        jae short L_0044b96e
    L_0044b94d:
        lea edx,[esp+4]
    L_0044b951:
        mov cl,byte ptr [edx]
    L_0044b953:
        inc edx
    L_0044b954:
        mov byte ptr [esi],cl
    L_0044b956:
        inc esi
    L_0044b957:
        test cl,cl
    L_0044b959:
        jne short L_0044b951
    L_0044b95b:
        mov ecx,dword ptr [edi+2000h]
    L_0044b961:
        add ecx,eax
    L_0044b963:
        mov eax,ecx
    L_0044b965:
        mov dword ptr [edi+2000h],ecx
    L_0044b96b:
        mov byte ptr [eax],0
    L_0044b96e:
        push 4922BCh
    L_0044b973:
        mov byte ptr [edi+2004h],1
    L_0044b97a:
        call dword ptr [data_004660b4]
    L_0044b980:
        mov al,byte ptr [data_0049231f]
    L_0044b985:
        mov ecx,dword ptr [esp+204h]
    L_0044b98c:
        dec al
    L_0044b98e:
        pop esi
    L_0044b98f:
        mov byte ptr [data_0049231f],al
    L_0044b994:
        mov eax,dword ptr [esp+208h]
    L_0044b99b:
        xor ecx,esp
    L_0044b99d:
        call asm_security_check_cookie_00458ea5
    L_0044b9a2:
        add esp,204h
    L_0044b9a8:
        ret
    }
}
