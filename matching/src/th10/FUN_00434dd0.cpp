// 00434DD0: FUN_00434dd0
// Original size: 288 bytes, actual code: 121 instructions
extern "C" void FUN_00434f30(void);
extern "C" void FUN_00435dc0(void);
extern "C" void FUN_0044b0d0(void);
extern "C" void _free(void);
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_00434dd0(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        mov  eax,DWORD PTR [ebp+0xc]
        test  eax,eax
        jne loc_00434DE2
        xor  eax,eax
        pop  ebp
        ret  0x8
    loc_00434DE2:
        push  ebx
        push  esi
        push  edi
        mov  ebx,ecx
        mov  eax,ebp
        call FUN_00434f30
        mov  ebx,eax
        test  ebx,ebx
        je loc_00434E4B
        mov  esi,DWORD PTR [ebx+0x14]
        mov  edx,DWORD PTR [ebx+0x4]
        mov  eax,DWORD PTR [ebx+0x8]
        sub  esi,edx
        cmp  esi,eax
        mov  DWORD PTR [esp+0x14],eax
        jne loc_00434E0F
        mov  edi,DWORD PTR [esp+0x18]
        test  edi,edi
        jne loc_00434E1E
    loc_00434E0F:
        push  esi
        call _malloc
        mov  edi,eax
        add  esp,0x4
        test  edi,edi
        je loc_00434E4B
    loc_00434E1E:
        mov  ecx,DWORD PTR [ebp+0xc]
        mov  edx,DWORD PTR [ebx+0x4]
        mov  eax,DWORD PTR [ecx]
        push  0x0
        push  edx
        call  DWORD PTR [eax+0x18]
        test  al,al
        je loc_00434E3E
        mov  ecx,DWORD PTR [ebp+0xc]
        mov  eax,DWORD PTR [ecx]
        push  esi
        push  edi
        call  DWORD PTR [eax+0x8]
        test  eax,eax
        jne loc_00434E54
    loc_00434E3E:
        test  edi,edi
        je loc_00434E4B
        push  edi
        call _free
        add  esp,0x4
    loc_00434E4B:
        pop  edi
        pop  esi
        pop  ebx
        xor  eax,eax
        pop  ebp
        ret  0x8
    loc_00434E54:
        mov  ebx,DWORD PTR [ebx]
        mov  eax,ebx
        lea  edx,[eax+0x1]
        jmp loc_00434E60
        nop
    loc_00434E60:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00434E60
        sub  eax,edx
        mov  edx,ebx
        je loc_00434E76
        nop
    loc_00434E70:
        add  cl,BYTE PTR [edx]
        inc  edx
        dec  eax
        jne loc_00434E70
    loc_00434E76:
        movzx eax,cl
        and  eax,0x80000007
        jns loc_00434E85
        dec  eax
        or   eax,0xfffffff8
        inc  eax
    loc_00434E85:
        movzx eax,al
        lea  eax,[eax+eax*2]
        shl  eax,0x2
        mov  ecx,DWORD PTR [eax+0x474be0]
        mov  edx,DWORD PTR [eax+0x474bdc]
        push  ecx
        xor  ecx,ecx
        mov  cl,BYTE PTR [eax+0x474bd9]
        mov  al,BYTE PTR [eax+0x474bd8]
        push  edx
        push  ecx
        push  esi
        push  edi
        call FUN_0044b0d0
        mov  eax,DWORD PTR [esp+0x14]
        cmp  esi,eax
        je loc_00434ECB
        mov  edx,DWORD PTR [esp+0x18]
        push  eax
        push  edx
        push  esi
        push  edi
        call FUN_00435dc0
        mov  esi,eax
        jmp loc_00434ECD
    loc_00434ECB:
        mov  esi,edi
    loc_00434ECD:
        cmp  edi,DWORD PTR [esp+0x18]
        je loc_00434EE0
        test  edi,edi
        je loc_00434EE0
        push  edi
        call _free
        add  esp,0x4
    loc_00434EE0:
        pop  edi
        mov  eax,esi
        pop  esi
        pop  ebx
        pop  ebp
        ret  0x8
    }
}
