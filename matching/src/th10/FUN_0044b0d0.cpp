// 0044B0D0: FUN_0044b0d0
// Original size: 336 bytes, actual code: 123 instructions
extern "C" void _free(void);
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_0044b0d0(void) {
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
        jle loc_0044B10B
        mov  esi,edi
    loc_0044B10B:
        mov  eax,DWORD PTR [esp+0x1c]
        push  esi
        mov  DWORD PTR [esp+0x14],eax
        call _malloc
        add  esp,0x4
        test  eax,eax
        mov  DWORD PTR [esp+0x14],eax
        mov  ebp,eax
        je loc_0044B205
        mov  edx,DWORD PTR [esp+0x20]
        mov  ecx,edi
        and  ecx,0x1
        add  ecx,edx
        sub  edi,ecx
        mov  ecx,esi
        mov  esi,DWORD PTR [esp+0x1c]
        mov  edx,ecx
        shr  ecx,0x2
        mov  DWORD PTR [esp+0x20],edi
        mov  edi,eax
        rep movsd
        mov  ecx,edx
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        mov  ecx,DWORD PTR [esp+0x20]
        test  ecx,ecx
        jle loc_0044B1FC
        jmp loc_0044B163
    loc_0044B15F:
        mov  ecx,DWORD PTR [esp+0x20]
    loc_0044B163:
        mov  edx,DWORD PTR [esp+0x2c]
        test  edx,edx
        jle loc_0044B1FC
        mov  esi,DWORD PTR [esp+0x28]
        cmp  ecx,esi
        jge loc_0044B17D
        mov  DWORD PTR [esp+0x28],ecx
        mov  esi,ecx
    loc_0044B17D:
        mov  eax,DWORD PTR [esp+0x10]
        lea  edi,[eax+esi*1]
        lea  eax,[esi+0x1]
        cdq
        sub  eax,edx
        sar  eax,1
        test  eax,eax
        mov  DWORD PTR [esp+0x10],edi
        lea  ecx,[edi-0x1]
        jle loc_0044B1AB
    loc_0044B197:
        mov  dl,BYTE PTR [ebp+0x0]
        xor  dl,bl
        mov  BYTE PTR [ecx],dl
        mov  dl,BYTE PTR [esp+0x24]
        sub  ecx,0x2
        add  bl,dl
        inc  ebp
        dec  eax
        jne loc_0044B197
    loc_0044B1AB:
        mov  eax,esi
        cdq
        sub  eax,edx
        sar  eax,1
        test  eax,eax
        lea  ecx,[edi-0x2]
        jle loc_0044B1D8
        mov  edi,eax
        jmp loc_0044B1C0
        nop
    loc_0044B1C0:
        mov  al,BYTE PTR [ebp+0x0]
        xor  al,bl
        mov  BYTE PTR [ecx],al
        mov  al,BYTE PTR [esp+0x24]
        sub  ecx,0x2
        add  bl,al
        inc  ebp
        dec  edi
        jne loc_0044B1C0
        mov  edi,DWORD PTR [esp+0x10]
    loc_0044B1D8:
        mov  eax,DWORD PTR [esp+0x20]
        mov  edx,DWORD PTR [esp+0x2c]
        sub  eax,esi
        sub  edx,esi
        mov  DWORD PTR [esp+0x20],eax
        test  eax,eax
        mov  eax,DWORD PTR [esp+0x14]
        mov  DWORD PTR [esp+0x10],edi
        mov  DWORD PTR [esp+0x2c],edx
        jg loc_0044B15F
    loc_0044B1FC:
        push  eax
        call _free
        add  esp,0x4
    loc_0044B205:
        mov  eax,DWORD PTR [esp+0x1c]
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        add  esp,0x8
        ret  0x14
    }
}
