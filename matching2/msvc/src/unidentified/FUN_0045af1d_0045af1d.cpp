#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045AF1D..0x0045AFDF: FUN_0045af1d
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045af1d_0045af1d() {
    __asm {
    L_0045af1d:
        push ebp
    L_0045af1e:
        mov ebp,esp
    L_0045af20:
        push ecx
    L_0045af21:
        push ecx
    L_0045af22:
        mov eax,dword ptr [ebp+0Ch]
    L_0045af25:
        mov dword ptr [ebp-8],eax
    L_0045af28:
        mov eax,dword ptr [ebp+1Ch]
    L_0045af2b:
        test eax,eax
    L_0045af2d:
        push edi
    L_0045af2e:
        mov edi,dword ptr [ebp+8]
    L_0045af31:
        jne short L_0045af36
    L_0045af33:
        mov eax,dword ptr [edi+4Ch]
    L_0045af36:
        mov dword ptr [ebp-4],eax
    L_0045af39:
        mov eax,dword ptr [ebp+10h]
    L_0045af3c:
        test eax,eax
    L_0045af3e:
        je asm_target_0045afdd
    L_0045af44:
        test eax,eax
    L_0045af46:
        push ebx
    L_0045af47:
        push esi
    L_0045af48:
        mov dword ptr [ebp+1Ch],eax
    L_0045af4b:
        jbe asm_target_0045afd3
    L_0045af51:
        mov esi,dword ptr [ebp+14h]
    L_0045af54:
        mov al,byte ptr [esi]
    L_0045af56:
        test al,al
    L_0045af58:
        je short L_0045afbf
    L_0045af5a:
        cmp al,25h
    L_0045af5c:
        je short L_0045af92
    L_0045af5e:
        mov edx,dword ptr [edi+48h]
    L_0045af61:
        movzx ecx,al
    L_0045af64:
        test byte ptr [edx+ecx*2+1],80h
    L_0045af69:
        je short L_0045af82
    L_0045af6b:
        cmp dword ptr [ebp+1Ch],1
    L_0045af6f:
        jbe short L_0045af82
    L_0045af71:
        inc esi
    L_0045af72:
        cmp byte ptr [esi],0
    L_0045af75:
        je short L_0045afd3
    L_0045af77:
        mov ecx,dword ptr [ebp+0Ch]
    L_0045af7a:
        mov byte ptr [ecx],al
    L_0045af7c:
        inc dword ptr [ebp+0Ch]
    L_0045af7f:
        dec dword ptr [ebp+1Ch]
    L_0045af82:
        mov al,byte ptr [esi]
    L_0045af84:
        mov ecx,dword ptr [ebp+0Ch]
    L_0045af87:
        mov byte ptr [ecx],al
    L_0045af89:
        inc dword ptr [ebp+0Ch]
    L_0045af8c:
        inc esi
    L_0045af8d:
        dec dword ptr [ebp+1Ch]
    L_0045af90:
        jmp short L_0045afb9
    L_0045af92:
        inc esi
    L_0045af93:
        xor eax,eax
    L_0045af95:
        cmp byte ptr [esi],23h
    L_0045af98:
        jne short L_0045af9c
    L_0045af9a:
        inc eax
    L_0045af9b:
        inc esi
    L_0045af9c:
        push eax
    L_0045af9d:
        push dword ptr [ebp-4]
    L_0045afa0:
        mov al,byte ptr [esi]
    L_0045afa2:
        push dword ptr [ebp+18h]
    L_0045afa5:
        lea ebx,[ebp+1Ch]
    L_0045afa8:
        push edi
    L_0045afa9:
        lea ecx,[ebp+0Ch]
    L_0045afac:
        call asm_expandtime_0045a82d
    L_0045afb1:
        add esp,10h
    L_0045afb4:
        test eax,eax
    L_0045afb6:
        je short L_0045afd3
    L_0045afb8:
        inc esi
    L_0045afb9:
        cmp dword ptr [ebp+1Ch],0
    L_0045afbd:
        ja short L_0045af54
    L_0045afbf:
        cmp dword ptr [ebp+1Ch],0
    L_0045afc3:
        jbe short L_0045afd3
    L_0045afc5:
        mov eax,dword ptr [ebp+0Ch]
    L_0045afc8:
        mov byte ptr [eax],0
    L_0045afcb:
        mov eax,dword ptr [ebp+10h]
    L_0045afce:
        sub eax,dword ptr [ebp+1Ch]
    L_0045afd1:
        jmp short L_0045afdb
    L_0045afd3:
        mov eax,dword ptr [ebp-8]
    L_0045afd6:
        mov byte ptr [eax],0
    L_0045afd9:
        xor eax,eax
    L_0045afdb:
        pop esi
    L_0045afdc:
        pop ebx
    L_0045afdd:
        pop edi
    L_0045afde:
        leave
    L_0045afdf:
        ret
    }
}
