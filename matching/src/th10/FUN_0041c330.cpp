// 0041C330: FUN_0041c330
// Original size: 480 bytes, actual code: 93 instructions
extern "C" void _free(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0041c330(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR [edi+0x18]
        test  esi,esi
        je loc_0041C43B
        push  ebx
        nop
    loc_0041C340:
        mov  al,BYTE PTR [esi+0x50]
        test  al,al
        mov  ebx,DWORD PTR [esi+0x8]
        je loc_0041C359
        inc  al
        cmp  al,0x2
        mov  BYTE PTR [esi+0x50],al
        jb loc_0041C359
        mov  eax,DWORD PTR [esi]
        mov  ecx,esi
        jmp loc_0041C363
    loc_0041C359:
        cmp  DWORD PTR [esi+0xc],0x1
        mov  eax,DWORD PTR [esi]
        mov  ecx,esi
        jne loc_0041C3A1
    loc_0041C363:
        call  DWORD PTR [eax+0x10]
        dec  DWORD PTR [edi+0x438]
        mov  edx,DWORD PTR [esi+0x8]
        mov  ecx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [ecx+0x8],edx
        mov  eax,DWORD PTR [esi+0x8]
        test  eax,eax
        je loc_0041C382
        mov  ecx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [eax+0x4],ecx
    loc_0041C382:
        cmp  DWORD PTR [edi+0x434],esi
        jne loc_0041C393
        mov  edx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [edi+0x434],edx
    loc_0041C393:
        push  esi
        call _free
        add  esp,0x4
        jmp loc_0041C430
    loc_0041C3A1:
        call  DWORD PTR [eax+0x8]
        test  eax,eax
        je loc_0041C3E7
        mov  edx,DWORD PTR [esi]
        mov  ecx,esi
        call  DWORD PTR [edx+0x10]
        dec  DWORD PTR [edi+0x438]
        mov  eax,DWORD PTR [esi+0x4]
        mov  ecx,DWORD PTR [esi+0x8]
        mov  DWORD PTR [eax+0x8],ecx
        mov  eax,DWORD PTR [esi+0x8]
        test  eax,eax
        je loc_0041C3CB
        mov  edx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [eax+0x4],edx
    loc_0041C3CB:
        cmp  DWORD PTR [edi+0x434],esi
        jne loc_0041C3DC
        mov  eax,DWORD PTR [esi+0x4]
        mov  DWORD PTR [edi+0x434],eax
    loc_0041C3DC:
        push  esi
        call _free
        add  esp,0x4
        jmp loc_0041C430
    loc_0041C3E7:
        mov  edx,DWORD PTR [esi+0x14]
        mov  ecx,DWORD PTR [esi+0x1c]
        mov  DWORD PTR [esi+0x10],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_0041C420
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0041C420
        fld  DWORD PTR [esi+0x18]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x14],edx
        fstp  DWORD PTR [esi+0x18]
        jmp loc_0041C430
    loc_0041C420:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [esi+0x18]
        fst  DWORD PTR [esi+0x18]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x14],eax
    loc_0041C430:
        test  ebx,ebx
        mov  esi,ebx
        jne loc_0041C340
        pop  ebx
    loc_0041C43B:
        mov  eax,0x1
        pop  esi
        ret
    }
}
