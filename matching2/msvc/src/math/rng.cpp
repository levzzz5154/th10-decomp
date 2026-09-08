#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044B9E0..0x0044BA2D: ?Rng_NextU32@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Rng_NextU32_0044b9e0() {
    __asm {
    L_0044b9e0:
        xor eax,eax
    L_0044b9e2:
        mov ax,word ptr [ecx]
    L_0044b9e5:
        xor ax,9630h
    L_0044b9e9:
        xor edx,edx
    L_0044b9eb:
        push esi
    L_0044b9ec:
        xor esi,esi
    L_0044b9ee:
        sub eax,6553h
    L_0044b9f3:
        mov dx,ax
    L_0044b9f6:
        shl eax,2
    L_0044b9f9:
        shr dx,0Eh
    L_0044b9fd:
        add edx,eax
    L_0044b9ff:
        mov eax,edx
    L_0044ba01:
        xor eax,9630h
    L_0044ba06:
        sub eax,6553h
    L_0044ba0b:
        mov si,ax
    L_0044ba0e:
        shr si,0Eh
    L_0044ba12:
        shl eax,2
    L_0044ba15:
        mov word ptr [ecx],dx
    L_0044ba18:
        add esi,eax
    L_0044ba1a:
        add dword ptr [ecx+4],2
    L_0044ba1e:
        mov word ptr [ecx],si
    L_0044ba21:
        movzx eax,dx
    L_0044ba24:
        movzx ecx,si
    L_0044ba27:
        shl eax,10h
    L_0044ba2a:
        or eax,ecx
    L_0044ba2c:
        pop esi
    L_0044ba2d:
        ret
    }
}

// 0x0044BA80..0x0044BB1A: ?Rng_NextU32DoubleStep@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Rng_NextU32DoubleStep_0044ba80() {
    __asm {
    L_0044ba80:
        sub esp,0Ch
    L_0044ba83:
        mov eax,dword ptr [data_00473660]
    L_0044ba88:
        xor eax,esp
    L_0044ba8a:
        mov dword ptr [esp+8],eax
    L_0044ba8e:
        xor eax,eax
    L_0044ba90:
        mov ax,word ptr [ecx]
    L_0044ba93:
        xor ax,9630h
    L_0044ba97:
        xor edx,edx
    L_0044ba99:
        sub eax,6553h
    L_0044ba9e:
        mov dx,ax
    L_0044baa1:
        shl eax,2
    L_0044baa4:
        shr dx,0Eh
    L_0044baa8:
        add eax,edx
    L_0044baaa:
        mov word ptr [ecx],ax
    L_0044baad:
        mov word ptr [esp],ax
    L_0044bab1:
        xor eax,9630h
    L_0044bab6:
        sub eax,6553h
    L_0044babb:
        xor edx,edx
    L_0044babd:
        mov dx,ax
    L_0044bac0:
        shr dx,0Eh
    L_0044bac4:
        shl eax,2
    L_0044bac7:
        add eax,edx
    L_0044bac9:
        mov word ptr [ecx],ax
    L_0044bacc:
        mov word ptr [esp+2],ax
    L_0044bad1:
        xor eax,9630h
    L_0044bad6:
        sub eax,6553h
    L_0044badb:
        mov edx,eax
    L_0044badd:
        xor eax,eax
    L_0044badf:
        mov ax,dx
    L_0044bae2:
        shr ax,0Eh
    L_0044bae6:
        shl edx,2
    L_0044bae9:
        add eax,edx
    L_0044baeb:
        xor eax,9630h
    L_0044baf0:
        sub eax,6553h
    L_0044baf5:
        xor edx,edx
    L_0044baf7:
        mov dx,ax
    L_0044bafa:
        shr dx,0Eh
    L_0044bafe:
        shl eax,2
    L_0044bb01:
        add edx,eax
    L_0044bb03:
        add dword ptr [ecx+4],4
    L_0044bb07:
        mov eax,dword ptr [esp]
    L_0044bb0a:
        mov word ptr [ecx],dx
    L_0044bb0d:
        mov ecx,dword ptr [esp+8]
    L_0044bb11:
        xor ecx,esp
    L_0044bb13:
        add esp,0Ch
    L_0044bb16:
        jmp asm_security_check_cookie_00458ea5
    }
}

// 0x0044BB20..0x0044BB8C: ?Rng_NextFloat@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Rng_NextFloat_0044bb20() {
    __asm {
    L_0044bb20:
        push ecx
    L_0044bb21:
        xor eax,eax
    L_0044bb23:
        mov ax,word ptr [ecx]
    L_0044bb26:
        xor ax,9630h
    L_0044bb2a:
        xor edx,edx
    L_0044bb2c:
        push esi
    L_0044bb2d:
        xor esi,esi
    L_0044bb2f:
        sub eax,6553h
    L_0044bb34:
        mov dx,ax
    L_0044bb37:
        shr dx,0Eh
    L_0044bb3b:
        shl eax,2
    L_0044bb3e:
        add edx,eax
    L_0044bb40:
        mov eax,edx
    L_0044bb42:
        xor eax,9630h
    L_0044bb47:
        sub eax,6553h
    L_0044bb4c:
        mov si,ax
    L_0044bb4f:
        shr si,0Eh
    L_0044bb53:
        shl eax,2
    L_0044bb56:
        mov word ptr [ecx],dx
    L_0044bb59:
        add eax,esi
    L_0044bb5b:
        mov esi,dword ptr [ecx+4]
    L_0044bb5e:
        add esi,2
    L_0044bb61:
        mov word ptr [ecx],ax
    L_0044bb64:
        mov dword ptr [ecx+4],esi
    L_0044bb67:
        movzx ecx,dx
    L_0044bb6a:
        movzx edx,ax
    L_0044bb6d:
        shl ecx,10h
    L_0044bb70:
        or ecx,edx
    L_0044bb72:
        test ecx,ecx
    L_0044bb74:
        mov dword ptr [esp+4],ecx
    L_0044bb78:
        fild dword ptr [esp+4]
    L_0044bb7c:
        jge short L_0044bb84
    L_0044bb7e:
        fadd dword ptr [data_00470b98]
    L_0044bb84:
        fmul dword ptr [data_00470bf0]
    L_0044bb8a:
        pop esi
    L_0044bb8b:
        pop ecx
    L_0044bb8c:
        ret
    }
}

// 0x0044BB90..0x0044BC02: ?Rng_NextFloatSigned@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Rng_NextFloatSigned_0044bb90() {
    __asm {
    L_0044bb90:
        push ecx
    L_0044bb91:
        xor eax,eax
    L_0044bb93:
        mov ax,word ptr [ecx]
    L_0044bb96:
        xor ax,9630h
    L_0044bb9a:
        xor edx,edx
    L_0044bb9c:
        push esi
    L_0044bb9d:
        xor esi,esi
    L_0044bb9f:
        sub eax,6553h
    L_0044bba4:
        mov dx,ax
    L_0044bba7:
        shr dx,0Eh
    L_0044bbab:
        shl eax,2
    L_0044bbae:
        add edx,eax
    L_0044bbb0:
        mov eax,edx
    L_0044bbb2:
        xor eax,9630h
    L_0044bbb7:
        sub eax,6553h
    L_0044bbbc:
        mov si,ax
    L_0044bbbf:
        shr si,0Eh
    L_0044bbc3:
        shl eax,2
    L_0044bbc6:
        mov word ptr [ecx],dx
    L_0044bbc9:
        add eax,esi
    L_0044bbcb:
        mov esi,dword ptr [ecx+4]
    L_0044bbce:
        add esi,2
    L_0044bbd1:
        mov word ptr [ecx],ax
    L_0044bbd4:
        mov dword ptr [ecx+4],esi
    L_0044bbd7:
        movzx ecx,dx
    L_0044bbda:
        movzx edx,ax
    L_0044bbdd:
        shl ecx,10h
    L_0044bbe0:
        or ecx,edx
    L_0044bbe2:
        test ecx,ecx
    L_0044bbe4:
        mov dword ptr [esp+4],ecx
    L_0044bbe8:
        fild dword ptr [esp+4]
    L_0044bbec:
        jge short L_0044bbf4
    L_0044bbee:
        fadd dword ptr [data_00470b98]
    L_0044bbf4:
        fmul dword ptr [data_00470bec]
    L_0044bbfa:
        pop esi
    L_0044bbfb:
        fsub dword ptr [data_00470afc]
    L_0044bc01:
        pop ecx
    L_0044bc02:
        ret
    }
}
