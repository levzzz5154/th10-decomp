// 00408210: FUN_00408210
// Original size: 1104 bytes, actual code: 149 instructions
extern "C" void FUN_0041bb00(void);
extern "C" void FUN_00448db0(void);
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_00408210(void) {
    __asm {
        sub  esp,0x3c
        fld  DWORD PTR [ebx+0x50]
        push  esi
        fmul  DWORD PTR ds:0x470b0c
        push  edi
        lea  esi,[ebx+0x60]
        mov  DWORD PTR [esp+0xc],0x7d0
        fstp  DWORD PTR [esp+0x20]
        mov  eax,DWORD PTR [esp+0x20]
        fld  DWORD PTR [ebx+0x54]
        mov  DWORD PTR [esp+0x14],eax
        fmul  DWORD PTR ds:0x470b0c
        fstp  DWORD PTR [esp+0x24]
        mov  ecx,DWORD PTR [esp+0x24]
        fld  DWORD PTR [ebx+0x58]
        mov  DWORD PTR [esp+0x18],ecx
        fmul  DWORD PTR ds:0x470b0c
        fstp  DWORD PTR [esp+0x28]
        mov  edx,DWORD PTR [esp+0x28]
        fld  DWORD PTR [ebx+0x44]
        mov  DWORD PTR [esp+0x1c],edx
        fsub  DWORD PTR [esp+0x14]
        fstp  DWORD PTR [esp+0x20]
        mov  eax,DWORD PTR [esp+0x20]
        fld  DWORD PTR [ebx+0x48]
        mov  DWORD PTR [esp+0x2c],eax
        fsub  DWORD PTR [esp+0x18]
        fstp  DWORD PTR [esp+0x24]
        mov  ecx,DWORD PTR [esp+0x24]
        fld  DWORD PTR [ebx+0x4c]
        mov  DWORD PTR [esp+0x30],ecx
        fsub  DWORD PTR [esp+0x1c]
        fstp  DWORD PTR [esp+0x28]
        mov  edx,DWORD PTR [esp+0x28]
        fld  DWORD PTR [esp+0x14]
        mov  DWORD PTR [esp+0x34],edx
        fadd  DWORD PTR [ebx+0x44]
        fstp  DWORD PTR [esp+0x20]
        mov  eax,DWORD PTR [esp+0x20]
        fld  DWORD PTR [esp+0x18]
        mov  DWORD PTR [esp+0x14],eax
        fadd  DWORD PTR [ebx+0x48]
        fstp  DWORD PTR [esp+0x24]
        mov  ecx,DWORD PTR [esp+0x24]
        fld  DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esp+0x18],ecx
        fadd  DWORD PTR [ebx+0x4c]
        fstp  DWORD PTR [esp+0x28]
        mov  edx,DWORD PTR [esp+0x28]
        mov  DWORD PTR [esp+0x1c],edx
        jmp loc_004082E0
        nop
        lea  ebx,[ebx+0x0]
    loc_004082E0:
        mov  ax,WORD PTR [esi+0x446]
        test  ax,ax
        je loc_0040843A
        cmp  ax,0x3
        je loc_0040843A
        fld  DWORD PTR [esi+0x3f0]
        lea  edi,[esi+0x3b4]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [edi]
        fsub  st,st(1)
        fstp  DWORD PTR [esp+0x20]
        fld  DWORD PTR [esi+0x3f4]
        fmul  DWORD PTR ds:0x470b0c
        fstp  DWORD PTR [esp+0x8]
        fld  DWORD PTR [esi+0x3b8]
        fsub  DWORD PTR [esp+0x8]
        fstp  DWORD PTR [esp+0x24]
        fadd  DWORD PTR [edi]
        fld  DWORD PTR [esp+0x8]
        fadd  DWORD PTR [esi+0x3b8]
        fstp  DWORD PTR [esp+0x3c]
        fcomp DWORD PTR [esp+0x2c]
        fnstsw ax
        test  ah,0x5
        jnp loc_0040843A
        fld  DWORD PTR [esp+0x20]
        fcomp DWORD PTR [esp+0x14]
        fnstsw ax
        test  ah,0x41
        je loc_0040843A
        fld  DWORD PTR [esp+0x3c]
        fcomp DWORD PTR [esp+0x30]
        fnstsw ax
        test  ah,0x5
        jnp loc_0040843A
        fld  DWORD PTR [esp+0x24]
        fcomp DWORD PTR [esp+0x18]
        fnstsw ax
        test  ah,0x41
        je loc_0040843A
        mov  ecx,DWORD PTR [esi]
        mov  eax,DWORD PTR [esp+0x48]
        or   ecx,0x8
        test  eax,eax
        mov  DWORD PTR [esi],ecx
        je loc_004083B3
        mov  eax,ds:0x477818
        push  0x3f19999a
        push  0xbfc90fdb
        push  0xffffffff
        push  0x8
        mov  ecx,edi
        call FUN_0041bb00
    loc_004083B3:
        mov  ecx,DWORD PTR [ebx+0x3e0b50]
        push  0x173
        lea  eax,[esp+0x14]
        push  eax
        push  ecx
        call FUN_00448db0
        mov  edx,DWORD PTR [eax]
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        call FUN_004491c0
        mov  ecx,DWORD PTR [esi+0x39c]
        test  ecx,ecx
        mov  edx,eax
        je loc_00408430
        fld  DWORD PTR [ecx+0x34]
        fcomp DWORD PTR ds:0x470b48
        fnstsw ax
        test  ah,0x41
        jp loc_00408403
        movsx eax,WORD PTR [esi+0x7ec]
        mov  ecx,DWORD PTR [eax*4+0x474350]
        jmp loc_0040842A
    loc_00408403:
        fld  DWORD PTR [ecx+0x34]
        fcomp DWORD PTR ds:0x470bcc
        fnstsw ax
        test  ah,0x41
        movsx eax,WORD PTR [esi+0x7ec]
        jp loc_00408423
        mov  ecx,DWORD PTR [eax*4+0x474390]
        jmp loc_0040842A
    loc_00408423:
        mov  ecx,DWORD PTR [eax*4+0x4743b0]
    loc_0040842A:
        mov  DWORD PTR [edx+0x2fc],ecx
    loc_00408430:
        mov  DWORD PTR [esi+0x450],0x0
    loc_0040843A:
        mov  eax,DWORD PTR [esp+0xc]
        add  esi,0x7f0
        dec  eax
        mov  DWORD PTR [esp+0xc],eax
        jne loc_004082E0
        pop  edi
        xor  eax,eax
        pop  esi
        add  esp,0x3c
        ret  0x4
    }
}
