// 0041EFA0: FUN_0041efa0
// Original size: 1120 bytes, actual code: 302 instructions
extern "C" void FUN_0041bb00(void);
extern "C" void FUN_0041c510(void);
extern "C" void FUN_0041f800(void);
extern "C" void FUN_0043e710(void);
extern "C" void FUN_004489d0(void);
extern "C" void FUN_00449950(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0041efa0(void) {
    __asm {
        push  ebp
        mov  ebp,esp
        and  esp,0xfffffff8
        sub  esp,0x32c
        mov  eax,ds:0x473660
        push  ebx
        xor  eax,ebp
        push  esi
        mov  esi,ecx
        mov  DWORD PTR [esp+0x330],eax
        lea  ebx,[esi+0x24]
        mov  eax,ebx
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x40],ecx
        mov  ecx,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [eax+0x8]
        push  edi
        mov  DWORD PTR [esp+0x48],ecx
        mov  DWORD PTR [esp+0x4c],eax
        xor  eax,eax
        mov  ecx,0x40
        lea  edi,[esp+0x230]
        rep stosd
        mov  ecx,DWORD PTR [esi+0x3c]
        push  0x40c00000
        xor  edx,edx
        push  ecx
        lea  ecx,[esp+0x24]
        mov  DWORD PTR [esp+0x44],esi
        mov  DWORD PTR [esp+0x30],edx
        mov  DWORD PTR [esp+0x34],edx
        mov  DWORD PTR [esp+0x14],0x40c00000
        mov  DWORD PTR [esp+0x2c],eax
        call FUN_0041f800
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [ebx]
        fstp  DWORD PTR [esp+0x30]
        mov  eax,DWORD PTR [esp+0x30]
        fld  DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x10],eax
        fadd  DWORD PTR [ebx+0x4]
        fstp  DWORD PTR [esp+0x34]
        mov  ecx,DWORD PTR [esp+0x34]
        fld  DWORD PTR [esp+0x24]
        mov  DWORD PTR [esp+0x14],ecx
        fadd  DWORD PTR [ebx+0x8]
        fstp  DWORD PTR [esp+0x38]
        mov  eax,DWORD PTR [esp+0x38]
        fld  DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esp+0x18],eax
        fadd  st(0),st
        mov  DWORD PTR [esp+0x18],edx
        fstp  DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esp+0x20]
        fadd  st(0),st
        fstp  DWORD PTR [esp+0x20]
        fld  DWORD PTR [esp+0x24]
        fadd  st(0),st
        fstp  DWORD PTR [esp+0x24]
        fld  DWORD PTR [ebp+0xc]
        fmul  DWORD PTR [ebp+0xc]
        fstp  DWORD PTR [ebp+0xc]
        fld  DWORD PTR ds:0x470cd8
        fcomp DWORD PTR [esi+0x40]
        fnstsw ax
        test  ah,0x5
        jp loc_0041F3D9
        jmp loc_0041F090
        nop
    loc_0041F090:
        mov  eax,DWORD PTR [ebp+0x8]
        fld  DWORD PTR [eax+0x4]
        fsub  DWORD PTR [esp+0x14]
        fld  DWORD PTR [eax]
        fsub  DWORD PTR [esp+0x10]
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
        je loc_0041F1D4
        mov  ecx,DWORD PTR [esp+0x28]
        mov  eax,DWORD PTR [ebp+0x10]
        inc  ecx
        test  eax,eax
        mov  BYTE PTR [esp+edx*1+0x230],0x1
        mov  DWORD PTR [esp+0x28],ecx
        je loc_0041F14C
        fld  DWORD PTR [esp+0x10]
        fadd  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x41
        jnp loc_0041F14C
        fld  DWORD PTR [esp+0x10]
        fsub  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        test  ah,0x1
        je loc_0041F14C
        fld  DWORD PTR [esp+0x14]
        fadd  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x41
        jnp loc_0041F14C
        fld  DWORD PTR [esp+0x14]
        fsub  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b38
        fnstsw ax
        test  ah,0x1
        je loc_0041F14C
        mov  eax,ds:0x477818
        push  0x3f19999a
        push  0xbfc90fdb
        push  0xffffffff
        push  0x8
        lea  ecx,[esp+0x20]
        call FUN_0041bb00
    loc_0041F14C:
        movsx ebx,WORD PTR [esi+0x466]
        mov  ecx,DWORD PTR ds:0x47781c
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ecx+0x458]
        lea  ebx,[ebx+ebx*1+0x11]
        call FUN_00449950
        mov  edx,DWORD PTR [esp+0x18]
        fld  DWORD PTR [esp+0x10]
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x35c]
        fadd  DWORD PTR ds:0x470b4c
        or   eax,0x40000000
        mov  DWORD PTR [esi+0x35c],eax
        mov  DWORD PTR [esi+0x20],0x0
        fstp  DWORD PTR [esi+0x340]
        mov  eax,esi
        fld  DWORD PTR [esp+0x14]
        mov  ecx,edi
        fadd  DWORD PTR ds:0x470b48
        mov  DWORD PTR [esi+0x348],edx
        fstp  DWORD PTR [esi+0x344]
        call FUN_0043e710
        mov  edx,DWORD PTR ds:0x491c10
        mov  ebx,esi
        lea  eax,[esp+0x40]
        call FUN_004489d0
        mov  edx,DWORD PTR [esp+0x2c]
        mov  esi,DWORD PTR [esp+0x3c]
    loc_0041F1D4:
        fld  DWORD PTR [esp+0x10]
        inc  edx
        fadd  DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esp+0x2c],edx
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [esp+0x14]
        fadd  DWORD PTR [esp+0x20]
        fstp  DWORD PTR [esp+0x14]
        fld  DWORD PTR [esp+0x18]
        fadd  DWORD PTR [esp+0x24]
        fstp  DWORD PTR [esp+0x18]
        fld  DWORD PTR [esp+0xc]
        fadd  DWORD PTR ds:0x470cd8
        fstp  DWORD PTR [esp+0xc]
        fld  DWORD PTR [esp+0xc]
        fadd  DWORD PTR ds:0x470d1c
        fcomp DWORD PTR [esi+0x40]
        fnstsw ax
        test  ah,0x5
        jnp loc_0041F090
        mov  eax,DWORD PTR [esp+0x28]
        test  eax,eax
        je loc_0041F3D9
        xor  eax,eax
        xor  ebx,ebx
        cmp  edx,eax
        jle loc_0041F259
        jmp loc_0041F240
        nop
    loc_0041F240:
        mov  cl,BYTE PTR [esp+ebx*1+0x230]
        test  cl,cl
        je loc_0041F250
        inc  ebx
        cmp  ebx,edx
        jl loc_0041F240
    loc_0041F250:
        cmp  ebx,eax
        je loc_0041F259
        mov  DWORD PTR [esi+0x40],eax
        jmp loc_0041F298
    loc_0041F259:
        cmp  edx,eax
        mov  DWORD PTR [esp+0xc],eax
        jle loc_0041F3D9
    loc_0041F265:
        mov  cl,BYTE PTR [esp+ebx*1+0x230]
        test  cl,cl
        jne loc_0041F27F
        inc  ebx
        inc  eax
        cmp  ebx,edx
        jl loc_0041F265
        mov  DWORD PTR [esp+0xc],eax
        jmp loc_0041F3D9
    loc_0041F27F:
        cmp  ebx,edx
        mov  DWORD PTR [esp+0xc],eax
        jge loc_0041F3D9
        fild  DWORD PTR [esp+0xc]
        fmul  DWORD PTR ds:0x470cd8
        fstp  DWORD PTR [esi+0x40]
    loc_0041F298:
        cmp  ebx,edx
        jge loc_0041F3D9
        jmp loc_0041F2B0
    loc_0041F2A2:
        mov  edx,DWORD PTR [esp+0x2c]
        mov  esi,DWORD PTR [esp+0x3c]
        lea  ebx,[ebx+0x0]
    loc_0041F2B0:
        cmp  ebx,edx
        jge loc_0041F3D9
        jmp loc_0041F2C0
        lea  ebx,[ebx+0x0]
    loc_0041F2C0:
        mov  al,BYTE PTR [esp+ebx*1+0x230]
        test  al,al
        je loc_0041F2D5
        inc  ebx
        cmp  ebx,edx
        jl loc_0041F2C0
        jmp loc_0041F3D9
    loc_0041F2D5:
        cmp  ebx,edx
        jge loc_0041F3D9
        xor  eax,eax
        mov  DWORD PTR [esp+0xc],eax
        mov  DWORD PTR [esp+0x40],ebx
        jmp loc_0041F2F0
        nop
    loc_0041F2F0:
        mov  cl,BYTE PTR [esp+ebx*1+0x230]
        test  cl,cl
        jne loc_0041F301
        inc  ebx
        inc  eax
        cmp  ebx,edx
        jl loc_0041F2F0
    loc_0041F301:
        mov  DWORD PTR [esp+0xc],eax
        fild  DWORD PTR [esp+0xc]
        xor  eax,eax
        mov  ecx,0x77
        lea  edi,[esp+0x50]
        fmul  DWORD PTR ds:0x470cd8
        rep stosd
        fst  DWORD PTR [esp+0x64]
        fstp  DWORD PTR [esp+0x60]
        push  0x0
        fild  DWORD PTR [esp+0x44]
        lea  edi,[esp+0x54]
        mov  DWORD PTR [esp+0x74],0x41000000
        fld  st(0)
        fld  DWORD PTR [esp+0x20]
        fmul  st,st(1)
        fld  DWORD PTR [esp+0x24]
        fmul  st,st(2)
        fstp  DWORD PTR [esp+0x18]
        fxch  st(1)
        fmul  DWORD PTR [esp+0x28]
        fstp  DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esp+0x48]
        fadd  st,st(1)
        fstp  DWORD PTR [esp+0x34]
        mov  eax,DWORD PTR [esp+0x34]
        mov  DWORD PTR [esp+0x54],eax
        mov  eax,DWORD PTR [esi+0x3c]
        fstp  st(0)
        fld  DWORD PTR [esp+0x4c]
        mov  DWORD PTR [esp+0x60],eax
        fadd  DWORD PTR [esp+0x18]
        mov  ax,WORD PTR [esi+0x466]
        mov  WORD PTR [esp+0x7a],ax
        fstp  DWORD PTR [esp+0x38]
        mov  ecx,DWORD PTR [esp+0x38]
        fld  DWORD PTR [esp+0x50]
        mov  DWORD PTR [esp+0x58],ecx
        fadd  DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR [esi+0x44]
        mov  DWORD PTR [esp+0x70],ecx
        fstp  DWORD PTR [esp+0x3c]
        mov  edx,DWORD PTR [esp+0x3c]
        mov  DWORD PTR [esp+0x5c],edx
        fmul  DWORD PTR ds:0x470cd8
        mov  dx,WORD PTR [esi+0x464]
        mov  WORD PTR [esp+0x78],dx
        fsubr DWORD PTR [esi+0x444]
        mov  esi,DWORD PTR ds:0x47781c
        fstp  DWORD PTR [esp+0x6c]
        call FUN_0041c510
        cmp  ebx,DWORD PTR [esp+0x2c]
        jl loc_0041F2A2
    loc_0041F3D9:
        mov  ecx,DWORD PTR [esp+0x334]
        mov  eax,DWORD PTR [esp+0x28]
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
