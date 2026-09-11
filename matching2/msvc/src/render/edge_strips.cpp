#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00444B10..0x00444BD8: FUN_00444b10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00444b10_00444b10() {
    __asm {
    L_00444b10:
        sub esp,8
    L_00444b13:
        push esi
    L_00444b14:
        mov esi,eax
    L_00444b16:
        cmp esi,3
    L_00444b19:
        jge short L_00444b23
    L_00444b1b:
        or eax,0FFFFFFFFh
    L_00444b1e:
        pop esi
    L_00444b1f:
        add esp,8
    L_00444b22:
        ret
    L_00444b23:
        mov eax,dword ptr [ecx+394h]
    L_00444b29:
        fld dword ptr [ecx+54h]
    L_00444b2c:
        fadd dword ptr [eax+28h]
    L_00444b2f:
        push edi
    L_00444b30:
        fld dword ptr [eax+24h]
    L_00444b33:
        mov edi,3F800000h
    L_00444b38:
        fadd dword ptr [ecx+58h]
    L_00444b3b:
        fstp dword ptr [esp+8]
    L_00444b3f:
        fld dword ptr [eax+28h]
    L_00444b42:
        fsub dword ptr [eax+20h]
    L_00444b45:
        lea eax,[esi+1]
    L_00444b48:
        cdq
    L_00444b49:
        sub eax,edx
    L_00444b4b:
        sar eax,1
    L_00444b4d:
        dec eax
    L_00444b4e:
        test esi,esi
    L_00444b50:
        mov dword ptr [esp+0Ch],eax
    L_00444b54:
        fidiv dword ptr [esp+0Ch]
    L_00444b58:
        fstp dword ptr [esp+0Ch]
    L_00444b5c:
        fld st(0)
    L_00444b5e:
        jle short L_00444b90
    L_00444b60:
        lea edx,[esi-1]
    L_00444b63:
        shr edx,1
    L_00444b65:
        lea eax,[ebx+18h]
    L_00444b68:
        inc edx
    L_00444b69:
        push ebp
    L_00444b6a:
        lea ebx,[ebx+force_disp32_zero]
    L_00444b70:
        mov ebp,dword ptr [esp+0Ch]
    L_00444b74:
        fst dword ptr [eax-4]
    L_00444b77:
        fsub dword ptr [esp+10h]
    L_00444b7b:
        mov dword ptr [eax],ebp
    L_00444b7d:
        mov ebp,dword ptr [ecx+2FCh]
    L_00444b83:
        mov dword ptr [eax-8],ebp
    L_00444b86:
        mov dword ptr [eax-0Ch],edi
    L_00444b89:
        add eax,38h
    L_00444b8c:
        dec edx
    L_00444b8d:
        jne short L_00444b70
    L_00444b8f:
        pop ebp
    L_00444b90:
        cmp esi,1
    L_00444b93:
        fstp st(0)
    L_00444b95:
        mov eax,dword ptr [ecx+394h]
    L_00444b9b:
        fld dword ptr [eax+2Ch]
    L_00444b9e:
        fadd dword ptr [ecx+58h]
    L_00444ba1:
        fstp dword ptr [esp+8]
    L_00444ba5:
        jle short L_00444bcf
    L_00444ba7:
        lea edx,[esi-2]
    L_00444baa:
        shr edx,1
    L_00444bac:
        lea eax,[ebx+34h]
    L_00444baf:
        inc edx
    L_00444bb0:
        mov esi,dword ptr [esp+8]
    L_00444bb4:
        fst dword ptr [eax-4]
    L_00444bb7:
        fsub dword ptr [esp+0Ch]
    L_00444bbb:
        mov dword ptr [eax],esi
    L_00444bbd:
        mov esi,dword ptr [ecx+2FCh]
    L_00444bc3:
        mov dword ptr [eax-8],esi
    L_00444bc6:
        mov dword ptr [eax-0Ch],edi
    L_00444bc9:
        add eax,38h
    L_00444bcc:
        dec edx
    L_00444bcd:
        jne short L_00444bb0
    L_00444bcf:
        pop edi
    L_00444bd0:
        fstp st(0)
    L_00444bd2:
        xor eax,eax
    L_00444bd4:
        pop esi
    L_00444bd5:
        add esp,8
    L_00444bd8:
        ret
    }
}

