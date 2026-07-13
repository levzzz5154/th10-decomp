// 00419650: FUN_00419650
// Original size: 592 bytes, actual code: 169 instructions
extern "C" void FUN_00419120(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00419650(void) {
    __asm {
        mov  eax,DWORD PTR [ebx+0xd8]
        mov  ecx,DWORD PTR ds:0x474c84
        sub  esp,0x10
        cmp  eax,ecx
        je loc_0041966A
        mov  DWORD PTR [ebx+0x14],0x0
    loc_0041966A:
        mov  eax,ds:0x474c7c
        push  ebp
        push  esi
        push  edi
        push  0x1
        lea  ecx,[eax+eax*2]
        mov  eax,DWORD PTR [ebx+ecx*4+0x1c]
        push  ebx
        call FUN_00419120
        mov  eax,ds:0x477834
        fld  DWORD PTR [eax+0x3c0]
        lea  edi,[ebx+0x17c]
        fadd  DWORD PTR ds:0x470b4c
        lea  ebp,[ebx+0x108]
        fld  DWORD PTR [eax+0x3c4]
        mov  DWORD PTR [esp+0x18],0xa
        fadd  DWORD PTR ds:0x470b48
    loc_004196B2:
        mov  ecx,DWORD PTR [edi-0xa0]
        test  ecx,ecx
        jne loc_004196C0
    loc_004196BC:
        xor  esi,esi
        jmp loc_004196FE
    loc_004196C0:
        mov  edx,DWORD PTR ds:0x491c10
        mov  eax,DWORD PTR [edx+0x72dad4]
        test  eax,eax
        je loc_004196DD
    loc_004196D0:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_004196F8
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004196D0
    loc_004196DD:
        mov  eax,DWORD PTR [edx+0x72dadc]
        test  eax,eax
        je loc_004196BC
    loc_004196E7:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_004196F8
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004196E7
        xor  esi,esi
        jmp loc_004196FE
    loc_004196F8:
        mov  esi,DWORD PTR [eax]
        test  esi,esi
        jne loc_00419710
    loc_004196FE:
        test  esi,esi
        mov  DWORD PTR [edi-0xa0],0x0
        je loc_00419858
    loc_00419710:
        mov  eax,DWORD PTR [esi+0x12c]
        test  eax,eax
        jne loc_00419858
        fld  st(1)
        fsub  DWORD PTR [ebp-0x4]
        fabs
        fld  st(1)
        fsub  DWORD PTR [ebp+0x0]
        fabs
        fstp  DWORD PTR [esp+0xc]
        fld  DWORD PTR [edi]
        fmul  DWORD PTR ds:0x470b0c
        fstp  DWORD PTR [esp+0x10]
        fcom  DWORD PTR [esp+0x10]
        fnstsw ax
        test  ah,0x5
        jp loc_00419774
        fld  DWORD PTR [esi+0x50]
        fmul  DWORD PTR [esi+0x40]
        fmul  DWORD PTR ds:0x470b0c
        fcomp DWORD PTR [esp+0xc]
        fnstsw ax
        test  ah,0x41
        jne loc_00419774
        mov  al,BYTE PTR [esi+0x310]
        fstp  st(0)
        shr  al,0x2
        mov  BYTE PTR [esi+0x2ff],al
        jmp loc_00419858
    loc_00419774:
        fld  DWORD PTR [esp+0x10]
        fadd  DWORD PTR ds:0x470bcc
        fstp  DWORD PTR [esp+0x14]
        fcom  DWORD PTR [esp+0x14]
        fnstsw ax
        test  ah,0x5
        jp loc_004197E3
        fld  DWORD PTR [esi+0x50]
        fmul  DWORD PTR [esi+0x40]
        fmul  DWORD PTR ds:0x470b0c
        fcomp DWORD PTR [esp+0xc]
        fnstsw ax
        test  ah,0x41
        jne loc_004197E3
        mov  eax,DWORD PTR [esi+0x310]
        mov  DWORD PTR [esp+0x10],eax
        fild  DWORD PTR [esp+0x10]
        lea  eax,[eax+eax*2]
        fld  DWORD PTR [esp+0x14]
        cdq
        and  edx,0x3
        fsub  st,st(2)
        add  eax,edx
        sar  eax,0x2
        mov  DWORD PTR [esp+0x14],eax
        fimul DWORD PTR [esp+0x14]
        fmul  DWORD PTR ds:0x470d20
        fsubp st(1),st
        call FUN_00463b2c
        fstp  st(0)
        mov  BYTE PTR [esi+0x2ff],al
        jmp loc_00419858
    loc_004197E3:
        fcomp DWORD PTR [esp+0x10]
        fnstsw ax
        test  ah,0x5
        jp loc_0041984C
        fld  DWORD PTR [esi+0x50]
        fmul  DWORD PTR [esi+0x40]
        fmul  DWORD PTR ds:0x470b0c
        fadd  DWORD PTR ds:0x470bcc
        fld  DWORD PTR [esp+0xc]
        fcomp st(1)
        fnstsw ax
        test  ah,0x5
        jp loc_0041984A
        mov  eax,DWORD PTR [esi+0x310]
        mov  DWORD PTR [esp+0x10],eax
        fild  DWORD PTR [esp+0x10]
        lea  eax,[eax+eax*2]
        cdq
        fxch  st(1)
        fsub  DWORD PTR [esp+0xc]
        and  edx,0x3
        add  eax,edx
        sar  eax,0x2
        mov  DWORD PTR [esp+0x14],eax
        fimul DWORD PTR [esp+0x14]
        fmul  DWORD PTR ds:0x470d20
        fsubp st(1),st
        call FUN_00463b2c
        mov  BYTE PTR [esi+0x2ff],al
        jmp loc_00419858
    loc_0041984A:
        fstp  st(0)
    loc_0041984C:
        mov  cl,BYTE PTR [esi+0x310]
        mov  BYTE PTR [esi+0x2ff],cl
    loc_00419858:
        mov  eax,DWORD PTR [esp+0x18]
        add  edi,0x4
        add  ebp,0xc
        dec  eax
        mov  DWORD PTR [esp+0x18],eax
        jne loc_004196B2
        mov  ecx,DWORD PTR [ebx+0x10]
        fstp  st(0)
        mov  eax,DWORD PTR [ebx+0x14]
        fstp  st(0)
        inc  ecx
        pop  edi
        inc  eax
        pop  esi
        mov  DWORD PTR [ebx+0x14],eax
        mov  DWORD PTR [ebx+0x10],ecx
        mov  eax,0x1
        pop  ebp
        add  esp,0x10
        ret
    }
}
