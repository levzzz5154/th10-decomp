#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00458EFD..0x00459074: FUN_00458efd
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00458efd_00458efd() {
    __asm {
    L_00458efd:
        push ebp
    L_00458efe:
        lea ebp,[esp-90h]
    L_00458f05:
        sub esp,110h
    L_00458f0b:
        mov eax,dword ptr [data_00473660]
    L_00458f10:
        mov ecx,dword ptr [ebp+98h]
    L_00458f16:
        push ebx
    L_00458f17:
        xor eax,ebp
    L_00458f19:
        push esi
    L_00458f1a:
        mov dword ptr [ebp+8Ch],eax
    L_00458f20:
        xor edx,edx
    L_00458f22:
        push edi
    L_00458f23:
        xor eax,eax
    L_00458f25:
        cmp ecx,dword ptr [eax*8+473670h]
    L_00458f2c:
        je short L_00458f34
    L_00458f2e:
        inc eax
    L_00458f2f:
        cmp eax,13h
    L_00458f32:
        jb short L_00458f25
    L_00458f34:
        mov esi,eax
    L_00458f36:
        shl esi,3
    L_00458f39:
        cmp ecx,dword ptr [esi+473670h]
    L_00458f3f:
        jne asm_target_00459057
    L_00458f45:
        mov eax,dword ptr [data_0047720c]
    L_00458f4a:
        cmp eax,1
    L_00458f4d:
        je asm_target_00459032
    L_00458f53:
        cmp eax,edx
    L_00458f55:
        jne short L_00458f64
    L_00458f57:
        cmp dword ptr [data_00473074],1
    L_00458f5e:
        je asm_target_00459032
    L_00458f64:
        cmp ecx,0FCh
    L_00458f6a:
        je asm_target_00459057
    L_00458f70:
        push 104h
    L_00458f75:
        lea eax,[ebp-7Ch]
    L_00458f78:
        push eax
    L_00458f79:
        push edx
    L_00458f7a:
        mov byte ptr [ebp+88h],dl
    L_00458f80:
        call dword ptr [data_004660dc]
    L_00458f86:
        test eax,eax
    L_00458f88:
        jne short L_00458f9a
    L_00458f8a:
        lea eax,[ebp-7Ch]
    L_00458f8d:
        push 46B02Ch
    L_00458f92:
        push eax
    L_00458f93:
        call asm_FUN_0045bd80_0045bd80
    L_00458f98:
        pop ecx
    L_00458f99:
        pop ecx
    L_00458f9a:
        lea edi,[ebp-7Ch]
    L_00458f9d:
        mov eax,edi
    L_00458f9f:
        push eax
    L_00458fa0:
        call asm_strlen_00456720
    L_00458fa5:
        inc eax
    L_00458fa6:
        cmp eax,3Ch
    L_00458fa9:
        pop ecx
    L_00458faa:
        jbe short L_00458fce
    L_00458fac:
        mov eax,edi
    L_00458fae:
        push eax
    L_00458faf:
        call asm_strlen_00456720
    L_00458fb4:
        mov edi,eax
    L_00458fb6:
        lea eax,[ebp-7Ch]
    L_00458fb9:
        sub eax,3Bh
    L_00458fbc:
        push 3
    L_00458fbe:
        add edi,eax
    L_00458fc0:
        push 46B028h
    L_00458fc5:
        push edi
    L_00458fc6:
        call asm_strncpy_00452960
    L_00458fcb:
        add esp,10h
    L_00458fce:
        push edi
    L_00458fcf:
        call asm_strlen_00456720
    L_00458fd4:
        push dword ptr [esi+473674h]
    L_00458fda:
        mov ebx,eax
    L_00458fdc:
        call asm_strlen_00456720
    L_00458fe1:
        lea eax,[ebx+eax+1Ch]
    L_00458fe5:
        pop ecx
    L_00458fe6:
        add eax,3
    L_00458fe9:
        pop ecx
    L_00458fea:
        and eax,0FFFFFFFCh
    L_00458fed:
        call asm_chkstk_00458ec0
    L_00458ff2:
        mov ebx,esp
    L_00458ff4:
        push 46B00Ch
    L_00458ff9:
        push ebx
    L_00458ffa:
        call asm_FUN_0045bd80_0045bd80
    L_00458fff:
        push edi
    L_00459000:
        push ebx
    L_00459001:
        call asm_FUN_0045bd90_0045bd90
    L_00459006:
        push 46B008h
    L_0045900b:
        push ebx
    L_0045900c:
        call asm_FUN_0045bd90_0045bd90
    L_00459011:
        push dword ptr [esi+473674h]
    L_00459017:
        push ebx
    L_00459018:
        call asm_FUN_0045bd90_0045bd90
    L_0045901d:
        push 12010h
    L_00459022:
        push 46AFE0h
    L_00459027:
        push ebx
    L_00459028:
        call asm_crtMessageBoxA_0045f3d0
    L_0045902d:
        add esp,2Ch
    L_00459030:
        jmp short L_00459057
    L_00459032:
        push edx
    L_00459033:
        lea eax,[ebp-80h]
    L_00459036:
        push eax
    L_00459037:
        lea esi,[esi+473674h]
    L_0045903d:
        push dword ptr [esi]
    L_0045903f:
        call asm_strlen_00456720
    L_00459044:
        pop ecx
    L_00459045:
        push eax
    L_00459046:
        push dword ptr [esi]
    L_00459048:
        push 0FFFFFFF4h
    L_0045904a:
        call dword ptr [data_00466098]
    L_00459050:
        push eax
    L_00459051:
        call dword ptr [data_004660d4]
    L_00459057:
        lea esp,[ebp-8Ch]
    L_0045905d:
        pop edi
    L_0045905e:
        pop esi
    L_0045905f:
        pop ebx
    L_00459060:
        mov ecx,dword ptr [ebp+8Ch]
    L_00459066:
        xor ecx,ebp
    L_00459068:
        call asm_security_check_cookie_00458ea5
    L_0045906d:
        add ebp,90h
    L_00459073:
        leave
    L_00459074:
        ret
    }
}
