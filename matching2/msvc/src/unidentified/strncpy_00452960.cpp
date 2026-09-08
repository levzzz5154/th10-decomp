#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452960..0x00452A83: _strncpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_strncpy_00452960() {
    __asm {
    L_00452960:
        mov ecx,dword ptr [esp+0Ch]
    L_00452964:
        push edi
    L_00452965:
        test ecx,ecx
    L_00452967:
        je asm_target_004529ff
    L_0045296d:
        push esi
    L_0045296e:
        push ebx
    L_0045296f:
        mov ebx,ecx
    L_00452971:
        mov esi,dword ptr [esp+14h]
    L_00452975:
        test esi,3
    L_0045297b:
        mov edi,dword ptr [esp+10h]
    L_0045297f:
        jne short L_0045298c
    L_00452981:
        shr ecx,2
    L_00452984:
        jne asm_target_00452a0f
    L_0045298a:
        jmp short L_004529b3
    L_0045298c:
        mov al,byte ptr [esi]
    L_0045298e:
        add esi,1
    L_00452991:
        mov byte ptr [edi],al
    L_00452993:
        add edi,1
    L_00452996:
        sub ecx,1
    L_00452999:
        je short L_004529c6
    L_0045299b:
        test al,al
    L_0045299d:
        je short L_004529ce
    L_0045299f:
        test esi,3
    L_004529a5:
        jne short L_0045298c
    L_004529a7:
        mov ebx,ecx
    L_004529a9:
        shr ecx,2
    L_004529ac:
        jne short L_00452a0f
    L_004529ae:
        and ebx,3
    L_004529b1:
        je short L_004529c6
    L_004529b3:
        mov al,byte ptr [esi]
    L_004529b5:
        add esi,1
    L_004529b8:
        mov byte ptr [edi],al
    L_004529ba:
        add edi,1
    L_004529bd:
        test al,al
    L_004529bf:
        je short L_004529f8
    L_004529c1:
        sub ebx,1
    L_004529c4:
        jne short L_004529b3
    L_004529c6:
        mov eax,dword ptr [esp+10h]
    L_004529ca:
        pop ebx
    L_004529cb:
        pop esi
    L_004529cc:
        pop edi
    L_004529cd:
        ret
    L_004529ce:
        test edi,3
    L_004529d4:
        je short L_004529ec
    L_004529d6:
        mov byte ptr [edi],al
    L_004529d8:
        add edi,1
    L_004529db:
        sub ecx,1
    L_004529de:
        je asm_target_00452a7c
    L_004529e4:
        test edi,3
    L_004529ea:
        jne short L_004529d6
    L_004529ec:
        mov ebx,ecx
    L_004529ee:
        shr ecx,2
    L_004529f1:
        jne short L_00452a67
    L_004529f3:
        mov byte ptr [edi],al
    L_004529f5:
        add edi,1
    L_004529f8:
        sub ebx,1
    L_004529fb:
        jne short L_004529f3
    L_004529fd:
        pop ebx
    L_004529fe:
        pop esi
    L_004529ff:
        mov eax,dword ptr [esp+8]
    L_00452a03:
        pop edi
    L_00452a04:
        ret
    L_00452a05:
        mov dword ptr [edi],edx
    L_00452a07:
        add edi,4
    L_00452a0a:
        sub ecx,1
    L_00452a0d:
        je short L_004529ae
    L_00452a0f:
        mov edx,7EFEFEFFh
    L_00452a14:
        mov eax,dword ptr [esi]
    L_00452a16:
        add edx,eax
    L_00452a18:
        xor eax,0FFFFFFFFh
    L_00452a1b:
        xor eax,edx
    L_00452a1d:
        mov edx,dword ptr [esi]
    L_00452a1f:
        add esi,4
    L_00452a22:
        test eax,81010100h
    L_00452a27:
        je short L_00452a05
    L_00452a29:
        test dl,dl
    L_00452a2b:
        je short L_00452a59
    L_00452a2d:
        test dh,dh
    L_00452a2f:
        je short L_00452a4f
    L_00452a31:
        test edx,0FF0000h
    L_00452a37:
        je short L_00452a45
    L_00452a39:
        test edx,0FF000000h
    L_00452a3f:
        jne short L_00452a05
    L_00452a41:
        mov dword ptr [edi],edx
    L_00452a43:
        jmp short L_00452a5d
    L_00452a45:
        and edx,0FFFFh
    L_00452a4b:
        mov dword ptr [edi],edx
    L_00452a4d:
        jmp short L_00452a5d
    L_00452a4f:
        and edx,0FFh
    L_00452a55:
        mov dword ptr [edi],edx
    L_00452a57:
        jmp short L_00452a5d
    L_00452a59:
        xor edx,edx
    L_00452a5b:
        mov dword ptr [edi],edx
    L_00452a5d:
        add edi,4
    L_00452a60:
        xor eax,eax
    L_00452a62:
        sub ecx,1
    L_00452a65:
        je short L_00452a73
    L_00452a67:
        xor eax,eax
    L_00452a69:
        mov dword ptr [edi],eax
    L_00452a6b:
        add edi,4
    L_00452a6e:
        sub ecx,1
    L_00452a71:
        jne short L_00452a69
    L_00452a73:
        and ebx,3
    L_00452a76:
        jne asm_target_004529f3
    L_00452a7c:
        mov eax,dword ptr [esp+10h]
    L_00452a80:
        pop ebx
    L_00452a81:
        pop esi
    L_00452a82:
        pop edi
    L_00452a83:
        ret
    }
}
