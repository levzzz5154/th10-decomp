#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00458B53..0x00458C24: FUN_00458b53
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00458b53_00458b53() {
    __asm {
    L_00458b53:
        push ebp
    L_00458b54:
        mov ebp,esp
    L_00458b56:
        sub esp,20h
    L_00458b59:
        mov eax,dword ptr [data_00473660]
    L_00458b5e:
        xor eax,ebp
    L_00458b60:
        mov dword ptr [ebp-4],eax
    L_00458b63:
        xor eax,eax
    L_00458b65:
        push ebx
    L_00458b66:
        push esi
    L_00458b67:
        mov dword ptr [ebp-1Ch],eax
    L_00458b6a:
        mov dword ptr [ebp-18h],eax
    L_00458b6d:
        mov byte ptr [ebp-14h],al
    L_00458b70:
        push ebx
    L_00458b71:
        pushfd
    L_00458b72:
        pop eax
    L_00458b73:
        mov ecx,eax
    L_00458b75:
        xor eax,200000h
    L_00458b7a:
        push eax
    L_00458b7b:
        popfd
    L_00458b7c:
        pushfd
    L_00458b7d:
        pop edx
    L_00458b7e:
        sub edx,ecx
    L_00458b80:
        je short L_00458ba1
    L_00458b82:
        push ecx
    L_00458b83:
        popfd
    L_00458b84:
        xor eax,eax
    L_00458b86:
        cpuid
    L_00458b88:
        mov dword ptr [ebp-20h],eax
    L_00458b8b:
        mov dword ptr [ebp-14h],ebx
    L_00458b8e:
        mov dword ptr [ebp-10h],edx
    L_00458b91:
        mov dword ptr [ebp-0Ch],ecx
    L_00458b94:
        mov eax,1
    L_00458b99:
        cpuid
    L_00458b9b:
        mov dword ptr [ebp-1Ch],edx
    L_00458b9e:
        mov dword ptr [ebp-18h],eax
    L_00458ba1:
        pop ebx
    L_00458ba2:
        and dword ptr [data_00499304],0
    L_00458ba9:
        and dword ptr [data_00499300],0
    L_00458bb0:
        test byte ptr [ebp-19h],4
    L_00458bb4:
        je short L_00458c15
    L_00458bb6:
        call asm_FUN_00458b1e_00458b1e
    L_00458bbb:
        test eax,eax
    L_00458bbd:
        je short L_00458c15
    L_00458bbf:
        push 0Ch
    L_00458bc1:
        lea eax,[ebp-14h]
    L_00458bc4:
        xor esi,esi
    L_00458bc6:
        push eax
    L_00458bc7:
        inc esi
    L_00458bc8:
        push 46AC14h
    L_00458bcd:
        mov dword ptr [data_00499304],esi
    L_00458bd3:
        call asm_strncmp_00452f80
    L_00458bd8:
        add esp,0Ch
    L_00458bdb:
        test eax,eax
    L_00458bdd:
        jne short L_00458c0f
    L_00458bdf:
        mov ecx,dword ptr [ebp-18h]
    L_00458be2:
        mov eax,ecx
    L_00458be4:
        sar eax,8
    L_00458be7:
        and eax,0Fh
    L_00458bea:
        sar ecx,14h
    L_00458bed:
        mov edx,eax
    L_00458bef:
        sub edx,0Fh
    L_00458bf2:
        and ecx,0FFh
    L_00458bf8:
        neg edx
    L_00458bfa:
        sbb edx,edx
    L_00458bfc:
        not edx
    L_00458bfe:
        and edx,ecx
    L_00458c00:
        add edx,eax
    L_00458c02:
        sub edx,0Fh
    L_00458c05:
        neg edx
    L_00458c07:
        sbb edx,edx
    L_00458c09:
        inc edx
    L_00458c0a:
        mov dword ptr [ebp-20h],edx
    L_00458c0d:
        jne short L_00458c15
    L_00458c0f:
        mov dword ptr [data_00499300],esi
    L_00458c15:
        mov ecx,dword ptr [ebp-4]
    L_00458c18:
        pop esi
    L_00458c19:
        xor ecx,ebp
    L_00458c1b:
        xor eax,eax
    L_00458c1d:
        pop ebx
    L_00458c1e:
        call asm_security_check_cookie_00458ea5
    L_00458c23:
        leave
    L_00458c24:
        ret
    }
}
