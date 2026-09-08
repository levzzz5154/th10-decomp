#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045CDAE..0x0045CF48: FUN_0045cdae
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045cdae_0045cdae() {
    __asm {
    L_0045cdae:
        push ebp
    L_0045cdaf:
        lea ebp,[esp-498h]
    L_0045cdb6:
        sub esp,518h
    L_0045cdbc:
        mov eax,dword ptr [data_00473660]
    L_0045cdc1:
        xor eax,ebp
    L_0045cdc3:
        mov dword ptr [ebp+494h],eax
    L_0045cdc9:
        push esi
    L_0045cdca:
        lea eax,[ebp-80h]
    L_0045cdcd:
        push eax
    L_0045cdce:
        push dword ptr [data_004980a4]
    L_0045cdd4:
        call dword ptr [data_00466064]
    L_0045cdda:
        cmp eax,1
    L_0045cddd:
        mov esi,100h
    L_0045cde2:
        jne asm_target_0045ceef
    L_0045cde8:
        xor eax,eax
    L_0045cdea:
        mov byte ptr [ebp+eax+394h],al
    L_0045cdf1:
        inc eax
    L_0045cdf2:
        cmp eax,esi
    L_0045cdf4:
        jb short L_0045cdea
    L_0045cdf6:
        mov al,byte ptr [ebp-7Ah]
    L_0045cdf9:
        test al,al
    L_0045cdfb:
        mov byte ptr [ebp+394h],20h
    L_0045ce02:
        je short L_0045ce3a
    L_0045ce04:
        push ebx
    L_0045ce05:
        lea edx,[ebp-79h]
    L_0045ce08:
        push edi
    L_0045ce09:
        movzx ecx,byte ptr [edx]
    L_0045ce0c:
        movzx eax,al
    L_0045ce0f:
        cmp eax,ecx
    L_0045ce11:
        ja short L_0045ce30
    L_0045ce13:
        sub ecx,eax
    L_0045ce15:
        inc ecx
    L_0045ce16:
        mov ebx,ecx
    L_0045ce18:
        shr ecx,2
    L_0045ce1b:
        lea edi,[ebp+eax+394h]
    L_0045ce22:
        mov eax,20202020h
    L_0045ce27:
        rep stosd
    L_0045ce29:
        mov ecx,ebx
    L_0045ce2b:
        and ecx,3
    L_0045ce2e:
        rep stosb
    L_0045ce30:
        inc edx
    L_0045ce31:
        mov al,byte ptr [edx]
    L_0045ce33:
        inc edx
    L_0045ce34:
        test al,al
    L_0045ce36:
        jne short L_0045ce09
    L_0045ce38:
        pop edi
    L_0045ce39:
        pop ebx
    L_0045ce3a:
        push 0
    L_0045ce3c:
        push dword ptr [data_00497f90]
    L_0045ce42:
        lea eax,[ebp-6Ch]
    L_0045ce45:
        push dword ptr [data_004980a4]
    L_0045ce4b:
        push eax
    L_0045ce4c:
        push esi
    L_0045ce4d:
        lea eax,[ebp+394h]
    L_0045ce53:
        push eax
    L_0045ce54:
        push 1
    L_0045ce56:
        call asm_crtGetStringTypeA_0045a25d
    L_0045ce5b:
        push 0
    L_0045ce5d:
        push dword ptr [data_004980a4]
    L_0045ce63:
        lea eax,[ebp+294h]
    L_0045ce69:
        push esi
    L_0045ce6a:
        push eax
    L_0045ce6b:
        push esi
    L_0045ce6c:
        lea eax,[ebp+394h]
    L_0045ce72:
        push eax
    L_0045ce73:
        push esi
    L_0045ce74:
        push dword ptr [data_00497f90]
    L_0045ce7a:
        call asm_FUN_0045ee1d_0045ee1d
    L_0045ce7f:
        push 0
    L_0045ce81:
        push dword ptr [data_004980a4]
    L_0045ce87:
        lea eax,[ebp+194h]
    L_0045ce8d:
        push esi
    L_0045ce8e:
        push eax
    L_0045ce8f:
        push esi
    L_0045ce90:
        lea eax,[ebp+394h]
    L_0045ce96:
        push eax
    L_0045ce97:
        push 200h
    L_0045ce9c:
        push dword ptr [data_00497f90]
    L_0045cea2:
        call asm_FUN_0045ee1d_0045ee1d
    L_0045cea7:
        add esp,5Ch
    L_0045ceaa:
        xor eax,eax
    L_0045ceac:
        mov cx,word ptr [ebp+eax*2-6Ch]
    L_0045ceb1:
        test cl,1
    L_0045ceb4:
        je short L_0045cecc
    L_0045ceb6:
        or byte ptr [eax+497FA1h],10h
    L_0045cebd:
        mov cl,byte ptr [ebp+eax+294h]
    L_0045cec4:
        mov byte ptr [eax+4980C0h],cl
    L_0045ceca:
        jmp short L_0045cee8
    L_0045cecc:
        test cl,2
    L_0045cecf:
        je short L_0045cee1
    L_0045ced1:
        or byte ptr [eax+497FA1h],20h
    L_0045ced8:
        mov cl,byte ptr [ebp+eax+194h]
    L_0045cedf:
        jmp short L_0045cec4
    L_0045cee1:
        mov byte ptr [eax+4980C0h],0
    L_0045cee8:
        inc eax
    L_0045cee9:
        cmp eax,esi
    L_0045ceeb:
        jb short L_0045ceac
    L_0045ceed:
        jmp short L_0045cf33
    L_0045ceef:
        xor eax,eax
    L_0045cef1:
        cmp eax,41h
    L_0045cef4:
        jb short L_0045cf0f
    L_0045cef6:
        cmp eax,5Ah
    L_0045cef9:
        ja short L_0045cf0f
    L_0045cefb:
        or byte ptr [eax+497FA1h],10h
    L_0045cf02:
        mov cl,al
    L_0045cf04:
        add cl,20h
    L_0045cf07:
        mov byte ptr [eax+4980C0h],cl
    L_0045cf0d:
        jmp short L_0045cf2e
    L_0045cf0f:
        cmp eax,61h
    L_0045cf12:
        jb short L_0045cf27
    L_0045cf14:
        cmp eax,7Ah
    L_0045cf17:
        ja short L_0045cf27
    L_0045cf19:
        or byte ptr [eax+497FA1h],20h
    L_0045cf20:
        mov cl,al
    L_0045cf22:
        sub cl,20h
    L_0045cf25:
        jmp short L_0045cf07
    L_0045cf27:
        mov byte ptr [eax+4980C0h],0
    L_0045cf2e:
        inc eax
    L_0045cf2f:
        cmp eax,esi
    L_0045cf31:
        jb short L_0045cef1
    L_0045cf33:
        mov ecx,dword ptr [ebp+494h]
    L_0045cf39:
        xor ecx,ebp
    L_0045cf3b:
        pop esi
    L_0045cf3c:
        call asm_security_check_cookie_00458ea5
    L_0045cf41:
        add ebp,498h
    L_0045cf47:
        leave
    L_0045cf48:
        ret
    }
}
