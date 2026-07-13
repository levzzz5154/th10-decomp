// 0041F400: FUN_0041f400
// Original size: 928 bytes, actual code: 230 instructions
extern "C" void FUN_0041bb00(void);
extern "C" void FUN_0041f800(void);
extern "C" void FUN_0043e710(void);
extern "C" void FUN_004489d0(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_0041f400(void) {
    __asm {
        sub  esp,0x30
        push  ebp
        mov  ebp,ecx
        mov  eax,DWORD PTR [ebp+0x3c]
        push  0x40c00000
        xor  edx,edx
        push  eax
        lea  ecx,[esp+0x24]
        mov  DWORD PTR [esp+0x10],edx
        mov  DWORD PTR [esp+0xc],0x40c00000
        call FUN_0041f800
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [ebp+0x24]
        mov  ecx,DWORD PTR [ebp+0x2c]
        mov  DWORD PTR [esp+0x30],ecx
        mov  DWORD PTR [esp+0x24],edx
        fstp  DWORD PTR [esp+0x28]
        mov  eax,DWORD PTR [esp+0x28]
        fld  DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x10],eax
        fadd  DWORD PTR [ebp+0x28]
        mov  eax,DWORD PTR [esp+0x30]
        mov  DWORD PTR [esp+0x18],eax
        fstp  DWORD PTR [esp+0x2c]
        mov  ecx,DWORD PTR [esp+0x2c]
        fld  DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esp+0x14],ecx
        fadd  st(0),st
        fstp  DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esp+0x20]
        fadd  st(0),st
        fstp  DWORD PTR [esp+0x20]
        fld  DWORD PTR ds:0x470cd8
        fcomp DWORD PTR [ebp+0x40]
        fnstsw ax
        test  ah,0x5
        jp loc_0041F65F
        push  ebx
        push  esi
        push  edi
        lea  ebx,[ebx+0x0]
    loc_0041F490:
        fld  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [esp+0x14]
        fadd  DWORD PTR ds:0x470b48
        inc  eax
        mov  DWORD PTR [esp+0x14],eax
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x41
        jnp loc_0041F604
        fld  DWORD PTR [esp+0x1c]
        fsub  DWORD PTR ds:0x470b48
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        test  ah,0x1
        je loc_0041F604
        fld  DWORD PTR [esp+0x20]
        fadd  DWORD PTR ds:0x470b48
        fst  DWORD PTR [esp+0x18]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x41
        jnp loc_0041F604
        fld  DWORD PTR [esp+0x20]
        fsub  DWORD PTR ds:0x470b48
        fcomp DWORD PTR ds:0x470b38
        fnstsw ax
        test  ah,0x1
        je loc_0041F604
        movsx ebx,WORD PTR [ebp+0x466]
        mov  ecx,DWORD PTR ds:0x47781c
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ecx+0x458]
        lea  ebx,[ebx+ebx*1+0x11]
        call FUN_00449950
        mov  edx,DWORD PTR [esp+0x18]
        fld  DWORD PTR [esp+0x1c]
        mov  esi,eax
        mov  ecx,DWORD PTR [esi+0x35c]
        fadd  DWORD PTR ds:0x470b4c
        mov  eax,DWORD PTR [esp+0x24]
        or   ecx,0x40000000
        mov  DWORD PTR [esi+0x35c],ecx
        mov  DWORD PTR [esi+0x20],0x0
        mov  DWORD PTR [esi+0x348],eax
        fstp  DWORD PTR [esi+0x340]
        mov  eax,esi
        mov  ecx,edi
        mov  DWORD PTR [esi+0x344],edx
        call FUN_0043e710
        mov  edx,DWORD PTR ds:0x491c10
        mov  ebx,esi
        lea  eax,[esp+0x18]
        call FUN_004489d0
        mov  eax,DWORD PTR [esp+0x44]
        test  eax,eax
        je loc_0041F604
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x41
        jnp loc_0041F604
        fld  DWORD PTR [esp+0x1c]
        fsub  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        test  ah,0x1
        je loc_0041F604
        fld  DWORD PTR [esp+0x20]
        fadd  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x41
        jnp loc_0041F604
        fld  DWORD PTR [esp+0x20]
        fsub  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b38
        fnstsw ax
        test  ah,0x1
        je loc_0041F604
        mov  eax,ds:0x477818
        push  0x3f19999a
        push  0xbfc90fdb
        push  0xffffffff
        push  0x8
        lea  ecx,[esp+0x2c]
        call FUN_0041bb00
    loc_0041F604:
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [esp+0x28]
        fstp  DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esp+0x20]
        fadd  DWORD PTR [esp+0x2c]
        fstp  DWORD PTR [esp+0x20]
        fld  DWORD PTR [esp+0x24]
        fadd  DWORD PTR [esp+0x30]
        fstp  DWORD PTR [esp+0x24]
        fld  DWORD PTR [esp+0x10]
        fadd  DWORD PTR ds:0x470cd8
        fst  DWORD PTR [esp+0x10]
        fadd  DWORD PTR ds:0x470d1c
        fcomp DWORD PTR [ebp+0x40]
        fnstsw ax
        test  ah,0x5
        jnp loc_0041F490
        mov  eax,DWORD PTR [esp+0x14]
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR [ebp+0xc],0x1
        pop  ebp
        add  esp,0x30
        ret  0x4
    loc_0041F65F:
        mov  DWORD PTR [ebp+0xc],0x1
        mov  eax,edx
        pop  ebp
        add  esp,0x30
        ret  0x4
    }
}
