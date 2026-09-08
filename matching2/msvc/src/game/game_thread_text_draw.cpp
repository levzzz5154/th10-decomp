#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00447BB0..0x00447C71: FUN_00447bb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00447bb0_00447bb0() {
    __asm {
    L_00447bb0:
        sub esp,84h
    L_00447bb6:
        mov eax,dword ptr [data_00473660]
    L_00447bbb:
        xor eax,esp
    L_00447bbd:
        push ebx
    L_00447bbe:
        mov dword ptr [esp+84h],eax
    L_00447bc5:
        mov al,byte ptr [esi+3A0h]
    L_00447bcb:
        test al,al
    L_00447bcd:
        push ebp
    L_00447bce:
        push edi
    L_00447bcf:
        mov ebp,11h
    L_00447bd4:
        jbe short L_00447bd9
    L_00447bd6:
        movzx ebp,al
    L_00447bd9:
        mov ecx,dword ptr [esp+9Ch]
    L_00447be0:
        lea eax,[esp+0A0h]
    L_00447be7:
        push eax
    L_00447be8:
        push ecx
    L_00447be9:
        lea edx,[esp+14h]
    L_00447bed:
        push edx
    L_00447bee:
        call asm_vsprintf_004524a6
    L_00447bf3:
        lea eax,[esp+18h]
    L_00447bf7:
        add esp,0Ch
    L_00447bfa:
        lea edx,[eax+1]
    L_00447bfd:
        TH10_NOP_LEA_ECX_DISP8()
    L_00447c00:
        mov cl,byte ptr [eax]
    L_00447c02:
        inc eax
    L_00447c03:
        test cl,cl
    L_00447c05:
        jne short L_00447c00
    L_00447c07:
        mov ecx,dword ptr [esi+360h]
    L_00447c0d:
        mov edi,dword ptr [esi+394h]
    L_00447c13:
        fld dword ptr [edi+34h]
    L_00447c16:
        sub eax,edx
    L_00447c18:
        mov edx,dword ptr [esp+98h]
    L_00447c1f:
        lea ebx,[ebp-1]
    L_00447c22:
        imul ebx,eax
    L_00447c25:
        shr ecx,1
    L_00447c27:
        and ecx,1
    L_00447c2a:
        push ecx
    L_00447c2b:
        push edx
    L_00447c2c:
        shr ebx,2
    L_00447c2f:
        call asm_FUN_00463b2c_00463b2c
    L_00447c34:
        cdq
    L_00447c35:
        sub eax,edx
    L_00447c37:
        sar eax,1
    L_00447c39:
        sub eax,ebx
    L_00447c3b:
        push eax
    L_00447c3c:
        mov eax,dword ptr [edi+4]
    L_00447c3f:
        push eax
    L_00447c40:
        lea ebx,[esp+1Ch]
    L_00447c44:
        mov eax,ebp
    L_00447c46:
        call asm_Recovery_DispatchRandomText_004479d0
    L_00447c4b:
        mov eax,dword ptr [esi+35Ch]
    L_00447c51:
        mov ecx,dword ptr [esp+8Ch]
    L_00447c58:
        pop edi
    L_00447c59:
        pop ebp
    L_00447c5a:
        or eax,1
    L_00447c5d:
        pop ebx
    L_00447c5e:
        xor ecx,esp
    L_00447c60:
        mov dword ptr [esi+35Ch],eax
    L_00447c66:
        call asm_security_check_cookie_00458ea5
    L_00447c6b:
        add esp,84h
    L_00447c71:
        ret
    }
}
