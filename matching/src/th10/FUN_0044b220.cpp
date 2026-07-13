// 0044B220: FUN_0044b220
// Original size: 320 bytes, actual code: 119 instructions
extern "C" void _free(void);
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_0044b220(void) {
    __asm {
        sub  esp,0x8
        push  ebx
        push  ebp
        push  esi
        mov  esi,DWORD PTR [esp+0x24]
        mov  bl,al
        push  edi
        mov  edi,DWORD PTR [esp+0x20]
        mov  eax,edi
        cdq
        idiv  esi
        mov  eax,esi
        mov  esi,DWORD PTR [esp+0x2c]
        mov  ecx,edx
        cdq
        and  edx,0x3
        add  eax,edx
        xor  edx,edx
        sar  eax,0x2
        cmp  ecx,eax
        setge dl
        dec  edx
        and  edx,ecx
        cmp  esi,edi
        mov  DWORD PTR [esp+0x20],edx
        jle loc_0044B25B
        mov  esi,edi
    loc_0044B25B:
        mov  ebp,DWORD PTR [esp+0x1c]
        push  esi
        call _malloc
        add  esp,0x4
        test  eax,eax
        mov  DWORD PTR [esp+0x10],eax
        mov  DWORD PTR [esp+0x14],eax
        je loc_0044B345
        mov  edx,DWORD PTR [esp+0x20]
        mov  ecx,edi
        and  ecx,0x1
        add  ecx,edx
        sub  edi,ecx
        mov  ecx,esi
        mov  edx,ecx
        shr  ecx,0x2
        mov  DWORD PTR [esp+0x20],edi
        mov  esi,ebp
        mov  edi,eax
        rep movsd
        mov  ecx,edx
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        mov  ecx,DWORD PTR [esp+0x20]
        test  ecx,ecx
        jle loc_0044B33C
        mov  edi,eax
        jmp loc_0044B2B1
    loc_0044B2AD:
        mov  ecx,DWORD PTR [esp+0x20]
    loc_0044B2B1:
        mov  edx,DWORD PTR [esp+0x2c]
        test  edx,edx
        jle loc_0044B33C
        mov  esi,DWORD PTR [esp+0x28]
        cmp  ecx,esi
        jge loc_0044B2CB
        mov  DWORD PTR [esp+0x28],ecx
        mov  esi,ecx
    loc_0044B2CB:
        lea  eax,[esi+0x1]
        cdq
        sub  eax,edx
        add  edi,esi
        sar  eax,1
        test  eax,eax
        mov  DWORD PTR [esp+0x14],edi
        lea  ecx,[edi-0x1]
        jle loc_0044B2F4
    loc_0044B2E0:
        mov  dl,BYTE PTR [ecx]
        xor  dl,bl
        mov  BYTE PTR [ebp+0x0],dl
        mov  dl,BYTE PTR [esp+0x24]
        sub  ecx,0x2
        add  bl,dl
        inc  ebp
        dec  eax
        jne loc_0044B2E0
    loc_0044B2F4:
        mov  eax,esi
        cdq
        sub  eax,edx
        sar  eax,1
        test  eax,eax
        lea  ecx,[edi-0x2]
        jle loc_0044B31C
        mov  edi,eax
    loc_0044B304:
        mov  al,BYTE PTR [ecx]
        xor  al,bl
        mov  BYTE PTR [ebp+0x0],al
        mov  al,BYTE PTR [esp+0x24]
        sub  ecx,0x2
        add  bl,al
        inc  ebp
        dec  edi
        jne loc_0044B304
        mov  edi,DWORD PTR [esp+0x14]
    loc_0044B31C:
        mov  eax,DWORD PTR [esp+0x20]
        mov  edx,DWORD PTR [esp+0x2c]
        sub  eax,esi
        sub  edx,esi
        mov  DWORD PTR [esp+0x20],eax
        test  eax,eax
        mov  eax,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0x2c],edx
        jg loc_0044B2AD
    loc_0044B33C:
        push  eax
        call _free
        add  esp,0x4
    loc_0044B345:
        mov  eax,DWORD PTR [esp+0x1c]
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        add  esp,0x8
        ret  0x14
    }
}
