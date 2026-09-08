#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421E00..0x00421EE0: FUN_00421e00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421e00_00421e00() {
    __asm {
    L_00421e00:
        push esi
    L_00421e01:
        push edi
    L_00421e02:
        mov edi,eax
    L_00421e04:
        mov ecx,dword ptr [edi+5208h]
    L_00421e0a:
        xor esi,esi
    L_00421e0c:
        cmp ecx,esi
    L_00421e0e:
        je asm_target_00421ede
    L_00421e14:
        cmp dword ptr [ecx+1Ch],1
    L_00421e18:
        jne short L_00421e4c
    L_00421e1a:
        mov eax,dword ptr [ecx+14h]
    L_00421e1d:
        dec eax
    L_00421e1e:
        cmp eax,esi
    L_00421e20:
        mov dword ptr [ecx+14h],eax
    L_00421e23:
        jg short L_00421e35
    L_00421e25:
        mov eax,dword ptr [ecx+4]
    L_00421e28:
        mov dword ptr [ecx+1Ch],esi
    L_00421e2b:
        mov eax,dword ptr [eax]
    L_00421e2d:
        mov ecx,dword ptr [eax]
    L_00421e2f:
        push eax
    L_00421e30:
        call dword ptr [ecx+48h]
    L_00421e33:
        jmp short L_00421e4c
    L_00421e35:
        imul eax,1388h
    L_00421e3b:
        cdq
    L_00421e3c:
        idiv dword ptr [ecx+18h]
    L_00421e3f:
        sub eax,1388h
    L_00421e44:
        push eax
    L_00421e45:
        mov eax,ecx
    L_00421e47:
        call asm_Platform_SetOperationDeadline_0044d4e0
    L_00421e4c:
        mov ecx,dword ptr [edi+5208h]
    L_00421e52:
        cmp dword ptr [ecx+1Ch],2
    L_00421e56:
        jne short L_00421e7a
    L_00421e58:
        mov eax,dword ptr [ecx+14h]
    L_00421e5b:
        dec eax
    L_00421e5c:
        cmp eax,esi
    L_00421e5e:
        mov dword ptr [ecx+14h],eax
    L_00421e61:
        jg short L_00421e68
    L_00421e63:
        mov dword ptr [ecx+1Ch],esi
    L_00421e66:
        jmp short L_00421e7a
    L_00421e68:
        imul eax,0FFFFEC78h
    L_00421e6e:
        cdq
    L_00421e6f:
        idiv dword ptr [ecx+18h]
    L_00421e72:
        push eax
    L_00421e73:
        mov eax,ecx
    L_00421e75:
        call asm_Platform_SetOperationDeadline_0044d4e0
    L_00421e7a:
        mov ecx,dword ptr [edi+5208h]
    L_00421e80:
        cmp dword ptr [ecx+1Ch],4
    L_00421e84:
        jne short L_00421ead
    L_00421e86:
        mov eax,dword ptr [ecx+14h]
    L_00421e89:
        dec eax
    L_00421e8a:
        cmp eax,esi
    L_00421e8c:
        mov dword ptr [ecx+14h],eax
    L_00421e8f:
        jg short L_00421e96
    L_00421e91:
        mov dword ptr [ecx+1Ch],esi
    L_00421e94:
        jmp short L_00421ead
    L_00421e96:
        imul eax,3E8h
    L_00421e9c:
        cdq
    L_00421e9d:
        idiv dword ptr [ecx+18h]
    L_00421ea0:
        sub eax,3E8h
    L_00421ea5:
        push eax
    L_00421ea6:
        mov eax,ecx
    L_00421ea8:
        call asm_Platform_SetOperationDeadline_0044d4e0
    L_00421ead:
        mov ecx,dword ptr [edi+5208h]
    L_00421eb3:
        cmp dword ptr [ecx+1Ch],3
    L_00421eb7:
        jne short L_00421ede
    L_00421eb9:
        mov edi,dword ptr [ecx+14h]
    L_00421ebc:
        dec edi
    L_00421ebd:
        mov eax,edi
    L_00421ebf:
        cmp eax,esi
    L_00421ec1:
        mov dword ptr [ecx+14h],edi
    L_00421ec4:
        jg short L_00421ecc
    L_00421ec6:
        pop edi
    L_00421ec7:
        mov dword ptr [ecx+1Ch],esi
    L_00421eca:
        pop esi
    L_00421ecb:
        ret
    L_00421ecc:
        imul eax,0FFFFFC18h
    L_00421ed2:
        cdq
    L_00421ed3:
        idiv dword ptr [ecx+18h]
    L_00421ed6:
        push eax
    L_00421ed7:
        mov eax,ecx
    L_00421ed9:
        call asm_Platform_SetOperationDeadline_0044d4e0
    L_00421ede:
        pop edi
    L_00421edf:
        pop esi
    L_00421ee0:
        ret
    }
}
