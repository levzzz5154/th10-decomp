#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CD20..0x0040CD7E: FUN_0040cd20
// Naked body preserves the retail register/stack ABI.

// 0x0040CD20..0x0040CD7E: FUN_0040cd20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040cd20_0040cd20() {
    __asm {
    L_0040cd20:
        mov eax,dword ptr [esp+4]
    L_0040cd24:
        push ebx
    L_0040cd25:
        push esi
    L_0040cd26:
        mov ebx,ecx
    L_0040cd28:
        push edi
    L_0040cd29:
        mov byte ptr [data_00497c38],0
    L_0040cd30:
        mov ecx,eax
    L_0040cd32:
        mov dl,byte ptr [eax]
    L_0040cd34:
        inc eax
    L_0040cd35:
        test dl,dl
    L_0040cd37:
        jne short L_0040cd32
    L_0040cd39:
        mov edi,497C38h
    L_0040cd3e:
        sub eax,ecx
    L_0040cd40:
        mov esi,ecx
    L_0040cd42:
        dec edi
    L_0040cd43:
        mov cl,byte ptr [edi+1]
    L_0040cd46:
        inc edi
    L_0040cd47:
        test cl,cl
    L_0040cd49:
        jne short L_0040cd43
    L_0040cd4b:
        mov ecx,eax
    L_0040cd4d:
        shr ecx,2
    L_0040cd50:
        rep movsd
    L_0040cd52:
        mov ecx,eax
    L_0040cd54:
        push 0
    L_0040cd56:
        and ecx,3
    L_0040cd59:
        push 0
    L_0040cd5b:
        mov eax,497C38h
    L_0040cd60:
        rep movsb
    L_0040cd62:
        call asm_FUN_0044b360_0044b360
    L_0040cd67:
        push eax
    L_0040cd68:
        mov ecx,ebx
    L_0040cd6a:
        call asm_FUN_00450220_00450220
    L_0040cd6f:
        xor ecx,ecx
    L_0040cd71:
        test eax,eax
    L_0040cd73:
        setge cl
    L_0040cd76:
        pop edi
    L_0040cd77:
        pop esi
    L_0040cd78:
        pop ebx
    L_0040cd79:
        dec ecx
    L_0040cd7a:
        mov eax,ecx
    L_0040cd7c:
        ret 4
    }
}
