// 0041DD80: FUN_0041dd80
// Original size: 1248 bytes, actual code: 345 instructions
extern "C" void FUN_0041bb00(void);
extern "C" void FUN_0041c510(void);
extern "C" void FUN_0041f800(void);
extern "C" void FUN_0043e710(void);
extern "C" void FUN_004489d0(void);
extern "C" void FUN_00449950(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0041dd80(void) {
    __asm {
        push  ebp
        mov  ebp,esp
        and  esp,0xfffffff8
        sub  esp,0x334
        mov  eax,ds:0x473660
        push  ebx
        mov  ebx,ecx
        xor  eax,ebp
        push  esi
        mov  DWORD PTR [esp+0x338],eax
        lea  esi,[ebx+0x24]
        mov  eax,esi
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x44],ecx
        mov  ecx,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [eax+0x8]
        push  edi
        mov  DWORD PTR [esp+0x4c],ecx
        mov  DWORD PTR [esp+0x50],eax
        xor  eax,eax
        mov  ecx,0x40
        lea  edi,[esp+0x238]
        rep stosd
        mov  ecx,DWORD PTR [ebx+0x3c]
        push  0x40c00000
        xor  edx,edx
        push  ecx
        lea  ecx,[esp+0x28]
        mov  DWORD PTR [esp+0x44],ebx
        mov  DWORD PTR [esp+0x34],edx
        mov  DWORD PTR [esp+0x4c],edx
        mov  DWORD PTR [esp+0x48],esi
        mov  DWORD PTR [esp+0x18],0x40c00000
        mov  DWORD PTR [esp+0x30],eax
        call FUN_0041f800
        fld  DWORD PTR [esp+0x20]
        fadd  DWORD PTR [esi]
        fstp  DWORD PTR [esp+0x30]
        mov  eax,DWORD PTR [esp+0x30]
        fld  DWORD PTR [esp+0x24]
        mov  DWORD PTR [esp+0x14],eax
        fadd  DWORD PTR [esi+0x4]
        fstp  DWORD PTR [esp+0x34]
        mov  ecx,DWORD PTR [esp+0x34]
        fld  DWORD PTR [esp+0x28]
        mov  DWORD PTR [esp+0x18],ecx
        fadd  DWORD PTR [esi+0x8]
        fstp  DWORD PTR [esp+0x38]
        mov  eax,DWORD PTR [esp+0x38]
        fld  DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x1c],eax
        fadd  st(0),st
        mov  DWORD PTR [esp+0x1c],edx
        fstp  DWORD PTR [esp+0x20]
        fld  DWORD PTR [esp+0x24]
        fadd  st(0),st
        fstp  DWORD PTR [esp+0x24]
        fld  DWORD PTR [esp+0x28]
        fadd  st(0),st
        fstp  DWORD PTR [esp+0x28]
        fld  DWORD PTR [ebp+0xc]
        fmul  DWORD PTR [ebp+0xc]
        fstp  DWORD PTR [ebp+0xc]
        fld  DWORD PTR ds:0x470cd8
        fcomp DWORD PTR [ebx+0x40]
        fnstsw ax
        test  ah,0x41
        jp loc_0041E23B
        nop
    loc_0041DE70:
        mov  eax,DWORD PTR [ebp+0x8]
        fld  DWORD PTR [eax+0x4]
        fsub  DWORD PTR [esp+0x18]
        fld  DWORD PTR [eax]
        fsub  DWORD PTR [esp+0x14]
        fld  st(0)
        fmul  st,st(1)
        fld  st(2)
        fmul  st,st(3)
        faddp st(1),st
        fcomp DWORD PTR [ebp+0xc]
        fnstsw ax
        fstp  st(0)
        test  ah,0x41
        fstp  st(0)
        je loc_0041DFB8
        mov  ecx,DWORD PTR [esp+0x2c]
        mov  eax,DWORD PTR [ebp+0x10]
        inc  ecx
        test  eax,eax
        mov  BYTE PTR [esp+edx*1+0x238],0x1
        mov  DWORD PTR [esp+0x2c],ecx
        je loc_0041DF2C
        fld  DWORD PTR [esp+0x14]
        fadd  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x41
        jnp loc_0041DF2C
        fld  DWORD PTR [esp+0x14]
        fsub  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        test  ah,0x1
        je loc_0041DF2C
        fld  DWORD PTR [esp+0x18]
        fadd  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x41
        jnp loc_0041DF2C
        fld  DWORD PTR [esp+0x18]
        fsub  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b38
        fnstsw ax
        test  ah,0x1
        je loc_0041DF2C
        mov  eax,ds:0x477818
        push  0x3f19999a
        push  0xbfc90fdb
        push  0xffffffff
        push  0x8
        lea  ecx,[esp+0x24]
        call FUN_0041bb00
    loc_0041DF2C:
        movsx ebx,WORD PTR [ebx+0x44a]
        mov  ecx,DWORD PTR ds:0x47781c
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ecx+0x458]
        lea  ebx,[ebx+ebx*1+0x11]
        call FUN_00449950
        mov  edx,DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esp+0x14]
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x35c]
        fadd  DWORD PTR ds:0x470b4c
        or   eax,0x40000000
        mov  DWORD PTR [esi+0x35c],eax
        mov  DWORD PTR [esi+0x20],0x0
        fstp  DWORD PTR [esi+0x340]
        mov  eax,esi
        fld  DWORD PTR [esp+0x18]
        mov  ecx,edi
        fadd  DWORD PTR ds:0x470b48
        mov  DWORD PTR [esi+0x348],edx
        fstp  DWORD PTR [esi+0x344]
        call FUN_0043e710
        mov  edx,DWORD PTR ds:0x491c10
        mov  ebx,esi
        lea  eax,[esp+0x54]
        call FUN_004489d0
        mov  esi,DWORD PTR [esp+0x40]
        mov  edx,DWORD PTR [esp+0x44]
        mov  ebx,DWORD PTR [esp+0x3c]
    loc_0041DFB8:
        fld  DWORD PTR [esp+0x14]
        inc  edx
        fadd  DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x44],edx
        fstp  DWORD PTR [esp+0x14]
        fld  DWORD PTR [esp+0x18]
        fadd  DWORD PTR [esp+0x24]
        fstp  DWORD PTR [esp+0x18]
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [esp+0x28]
        fstp  DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esp+0x10]
        fadd  DWORD PTR ds:0x470cd8
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [esp+0x10]
        fadd  DWORD PTR ds:0x470d1c
        fcomp DWORD PTR [ebx+0x40]
        fnstsw ax
        test  ah,0x41
        jnp loc_0041DE70
        mov  eax,DWORD PTR [esp+0x2c]
        test  eax,eax
        je loc_0041E23B
        cmp  eax,edx
        jl loc_0041E032
        mov  BYTE PTR [ebx+0x50],0x1
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x330]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret  0xc
    loc_0041E032:
        xor  ebx,ebx
        test  edx,edx
        mov  DWORD PTR [esp+0x10],ebx
        jle loc_0041E0C7
    loc_0041E040:
        mov  al,BYTE PTR [esp+ebx*1+0x238]
        test  al,al
        je loc_0041E050
        inc  ebx
        cmp  ebx,edx
        jl loc_0041E040
    loc_0041E050:
        test  ebx,ebx
        mov  DWORD PTR [esp+0x10],ebx
        je loc_0041E0C7
        fild  DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [esp+0x3c]
        fld  st(0)
        fld  DWORD PTR [esp+0x20]
        fmul  st,st(1)
        fld  DWORD PTR [esp+0x24]
        fmul  st,st(2)
        fstp  DWORD PTR [esp+0x34]
        fxch  st(1)
        fmul  DWORD PTR [esp+0x28]
        fstp  DWORD PTR [esp+0x38]
        fadd  DWORD PTR [esi]
        fstp  DWORD PTR [esi]
        fld  DWORD PTR [esp+0x34]
        fadd  DWORD PTR [esi+0x4]
        fstp  DWORD PTR [esi+0x4]
        fld  DWORD PTR [esp+0x38]
        fadd  DWORD PTR [esi+0x8]
        fstp  DWORD PTR [esi+0x8]
        fmul  DWORD PTR ds:0x470cd8
        fld  DWORD PTR [ecx+0x40]
        fsub  st,st(1)
        fcom  DWORD PTR ds:0x470c0c
        fst  DWORD PTR [ecx+0x40]
        fnstsw ax
        test  ah,0x41
        jne loc_0041E0BA
        fstp  DWORD PTR [ecx+0x434]
        fstp  DWORD PTR [ecx+0x4c]
        jmp loc_0041E0CB
    loc_0041E0BA:
        fstp  st(0)
        mov  BYTE PTR [ecx+0x50],0x1
        fstp  st(0)
        jmp loc_0041E23B
    loc_0041E0C7:
        mov  ecx,DWORD PTR [esp+0x3c]
    loc_0041E0CB:
        xor  eax,eax
        cmp  ebx,edx
        mov  DWORD PTR [esp+0x10],eax
        jge loc_0041E23B
        nop
    loc_0041E0E0:
        cmp  BYTE PTR [esp+ebx*1+0x238],0x0
        jne loc_0041E0F9
        inc  ebx
        inc  eax
        cmp  ebx,edx
        jl loc_0041E0E0
        mov  DWORD PTR [esp+0x10],eax
        jmp loc_0041E23B
    loc_0041E0F9:
        cmp  ebx,edx
        mov  DWORD PTR [esp+0x10],eax
        jge loc_0041E23B
        fild  DWORD PTR [esp+0x10]
        fmul  DWORD PTR ds:0x470cd8
        fld  DWORD PTR [ecx+0x40]
        fsub  st,st(1)
        fsubr DWORD PTR [ecx+0x434]
        fstp  DWORD PTR [ecx+0x434]
        fst  DWORD PTR [ecx+0x40]
        fcomp DWORD PTR ds:0x470c0c
        fnstsw ax
        test  ah,0x5
        jp loc_0041E140
        mov  BYTE PTR [ecx+0x50],0x1
        jmp loc_0041E140
    loc_0041E136:
        mov  ecx,DWORD PTR [esp+0x3c]
        lea  ebx,[ebx+0x0]
    loc_0041E140:
        cmp  ebx,edx
        jge loc_0041E23B
        jmp loc_0041E150
        lea  ebx,[ebx+0x0]
    loc_0041E150:
        mov  al,BYTE PTR [esp+ebx*1+0x238]
        test  al,al
        je loc_0041E165
        inc  ebx
        cmp  ebx,edx
        jl loc_0041E150
        jmp loc_0041E23B
    loc_0041E165:
        cmp  ebx,edx
        jge loc_0041E23B
        xor  eax,eax
        mov  DWORD PTR [esp+0x10],eax
        mov  DWORD PTR [esp+0x40],ebx
        jmp loc_0041E180
        nop
    loc_0041E180:
        cmp  BYTE PTR [esp+ebx*1+0x238],0x0
        jne loc_0041E190
        inc  ebx
        inc  eax
        cmp  ebx,edx
        jl loc_0041E180
    loc_0041E190:
        mov  DWORD PTR [esp+0x10],eax
        fild  DWORD PTR [esp+0x10]
        lea  esi,[ecx+0x424]
        mov  ecx,0x77
        lea  edi,[esp+0x58]
        fmul  DWORD PTR ds:0x470cd8
        rep movsd
        fst  DWORD PTR [esp+0x6c]
        fst  DWORD PTR [esp+0x68]
        fcomp DWORD PTR ds:0x470c0c
        fnstsw ax
        test  ah,0x41
        jne loc_0041E233
        fild  DWORD PTR [esp+0x40]
        mov  esi,DWORD PTR ds:0x47781c
        fld  DWORD PTR [esp+0x20]
        push  0x0
        lea  edi,[esp+0x5c]
        fmul  st,st(1)
        fld  st(1)
        fmul  DWORD PTR [esp+0x28]
        fstp  DWORD PTR [esp+0x1c]
        fxch  st(1)
        fmul  DWORD PTR [esp+0x2c]
        fstp  DWORD PTR [esp+0x20]
        fld  DWORD PTR [esp+0x4c]
        fadd  st,st(1)
        fstp  DWORD PTR [esp+0x34]
        mov  eax,DWORD PTR [esp+0x34]
        mov  DWORD PTR [esp+0x5c],eax
        fstp  st(0)
        fld  DWORD PTR [esp+0x50]
        fadd  DWORD PTR [esp+0x1c]
        fstp  DWORD PTR [esp+0x38]
        mov  ecx,DWORD PTR [esp+0x38]
        fld  DWORD PTR [esp+0x54]
        mov  DWORD PTR [esp+0x60],ecx
        fadd  DWORD PTR [esp+0x20]
        fstp  DWORD PTR [esp+0x3c]
        mov  edx,DWORD PTR [esp+0x3c]
        mov  DWORD PTR [esp+0x64],edx
        call FUN_0041c510
        mov  edx,DWORD PTR [esp+0x44]
    loc_0041E233:
        cmp  ebx,edx
        jl loc_0041E136
    loc_0041E23B:
        mov  ecx,DWORD PTR [esp+0x33c]
        mov  eax,DWORD PTR [esp+0x2c]
        pop  edi
        pop  esi
        xor  ecx,ebp
        pop  ebx
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret  0xc
    }
}
