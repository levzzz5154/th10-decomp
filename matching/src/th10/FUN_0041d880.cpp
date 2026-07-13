// 0041D880: FUN_0041d880
// Original size: 1280 bytes, actual code: 360 instructions
extern "C" void FUN_0041bb00(void);
extern "C" void FUN_0041c510(void);
extern "C" void FUN_0041f7a0(void);
extern "C" void FUN_0041f800(void);
extern "C" void FUN_00448db0(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0041d880(void) {
    __asm {
        push  ebp
        mov  ebp,esp
        and  esp,0xfffffff8
        sub  esp,0x344
        mov  eax,ds:0x473660
        xor  eax,ebp
        push  ebx
        mov  ebx,ecx
        mov  DWORD PTR [esp+0x344],eax
        mov  eax,DWORD PTR [ebp+0xc]
        mov  DWORD PTR [esp+0x28],eax
        mov  DWORD PTR [esp+0x14],ebx
        mov  edx,DWORD PTR [ebp+0x8]
        add  ebx,0x24
        mov  ecx,ebx
        mov  eax,DWORD PTR [ecx]
        mov  DWORD PTR [esp+0x54],eax
        mov  eax,DWORD PTR [ecx+0x4]
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esp+0x5c],ecx
        push  esi
        mov  DWORD PTR [esp+0x5c],eax
        push  edi
        xor  eax,eax
        mov  ecx,0x40
        lea  edi,[esp+0x248]
        rep stosd
        mov  eax,DWORD PTR [esp+0x30]
        mov  edi,DWORD PTR [esp+0x1c]
        xor  esi,esi
        fld  DWORD PTR [eax]
        push  0x40c00000
        fmul  DWORD PTR ds:0x470b0c
        mov  DWORD PTR [esp+0x30],esi
        mov  DWORD PTR [esp+0x10],0x40c00000
        mov  DWORD PTR [esp+0x2c],esi
        fstp  DWORD PTR [esp+0x14]
        fld  DWORD PTR [eax+0x4]
        fmul  DWORD PTR ds:0x470b0c
        fstp  DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [esp+0x18]
        fld  DWORD PTR [eax+0x8]
        mov  eax,DWORD PTR [esp+0x14]
        fmul  DWORD PTR ds:0x470b0c
        mov  DWORD PTR [esp+0x38],eax
        mov  DWORD PTR [esp+0x3c],ecx
        fstp  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [esp+0x1c]
        fld  DWORD PTR [edx]
        mov  DWORD PTR [esp+0x40],eax
        fsub  DWORD PTR [esp+0x38]
        fstp  DWORD PTR [esp+0x14]
        mov  ecx,DWORD PTR [esp+0x14]
        fld  DWORD PTR [edx+0x4]
        mov  DWORD PTR [esp+0x44],ecx
        fsub  DWORD PTR [esp+0x3c]
        fstp  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [esp+0x18]
        fld  DWORD PTR [edx+0x8]
        mov  DWORD PTR [esp+0x48],eax
        fsub  DWORD PTR [esp+0x40]
        fstp  DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esp+0x38]
        mov  DWORD PTR [esp+0x4c],ecx
        fadd  DWORD PTR [edx]
        fstp  DWORD PTR [esp+0x14]
        fld  DWORD PTR [esp+0x3c]
        fadd  DWORD PTR [edx+0x4]
        fstp  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [esp+0x18]
        fld  DWORD PTR [esp+0x40]
        mov  DWORD PTR [esp+0x3c],eax
        fadd  DWORD PTR [edx+0x8]
        mov  edx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [esp+0x38],edx
        mov  edx,DWORD PTR [edi+0x3c]
        fstp  DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esp+0x40],ecx
        push  edx
        lea  ecx,[esp+0x28]
        call FUN_0041f800
        fld  DWORD PTR [esp+0x20]
        fadd  DWORD PTR [ebx]
        fstp  DWORD PTR [esp+0x4c]
        mov  eax,DWORD PTR [esp+0x4c]
        fld  DWORD PTR [esp+0x24]
        mov  DWORD PTR [esp+0x10],eax
        fadd  DWORD PTR [ebx+0x4]
        fstp  DWORD PTR [esp+0x50]
        mov  ecx,DWORD PTR [esp+0x50]
        fld  DWORD PTR [esp+0x28]
        mov  DWORD PTR [esp+0x14],ecx
        fadd  DWORD PTR [ebx+0x8]
        fstp  DWORD PTR [esp+0x54]
        mov  edx,DWORD PTR [esp+0x54]
        fld  DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x18],edx
        fadd  st(0),st
        mov  DWORD PTR [esp+0x18],esi
        fstp  DWORD PTR [esp+0x20]
        fld  DWORD PTR [esp+0x24]
        fadd  st(0),st
        fstp  DWORD PTR [esp+0x24]
        fld  DWORD PTR [esp+0x28]
        fadd  st(0),st
        fstp  DWORD PTR [esp+0x28]
        fld  DWORD PTR ds:0x470cd8
        fcomp DWORD PTR [edi+0x40]
        fnstsw ax
        test  ah,0x41
        jp loc_0041DD5A
        mov  ebx,DWORD PTR [ebp+0x10]
    loc_0041DA21:
        fld  DWORD PTR [esp+0x10]
        fcomp DWORD PTR [esp+0x40]
        fnstsw ax
        test  ah,0x5
        jnp loc_0041DAD7
        fld  DWORD PTR [esp+0x10]
        fcomp DWORD PTR [esp+0x34]
        fnstsw ax
        test  ah,0x41
        je loc_0041DAD7
        fld  DWORD PTR [esp+0x14]
        fcomp DWORD PTR [esp+0x44]
        fnstsw ax
        test  ah,0x5
        jnp loc_0041DAD7
        fld  DWORD PTR [esp+0x14]
        fcomp DWORD PTR [esp+0x38]
        fnstsw ax
        test  ah,0x41
        je loc_0041DAD7
        mov  ecx,DWORD PTR [esp+0x2c]
        inc  ecx
        test  ebx,ebx
        mov  BYTE PTR [esp+esi*1+0x248],0x1
        mov  DWORD PTR [esp+0x2c],ecx
        je loc_0041DAAD
        push  0x42000000
        push  0x42000000
        lea  ecx,[esp+0x18]
        call FUN_0041f7a0
        test  eax,eax
        jne loc_0041DAAD
        mov  eax,ds:0x477818
        push  0x3f19999a
        push  0xbfc90fdb
        push  0xffffffff
        push  0x8
        call FUN_0041bb00
    loc_0041DAAD:
        movsx eax,WORD PTR [edi+0x44a]
        lea  ecx,[eax+eax*1+0x11]
        mov  eax,ds:0x47781c
        push  ecx
        mov  ecx,DWORD PTR [eax+0x458]
        lea  edx,[esp+0x5c]
        push  edx
        push  ecx
        lea  edi,[esp+0x1c]
        call FUN_00448db0
        mov  edi,DWORD PTR [esp+0x1c]
    loc_0041DAD7:
        fld  DWORD PTR [esp+0x20]
        inc  esi
        fadd  DWORD PTR [esp+0x10]
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [esp+0x24]
        fadd  DWORD PTR [esp+0x14]
        fstp  DWORD PTR [esp+0x14]
        fld  DWORD PTR [esp+0x18]
        fadd  DWORD PTR [esp+0x28]
        fstp  DWORD PTR [esp+0x18]
        fld  DWORD PTR [esp+0xc]
        fadd  DWORD PTR ds:0x470cd8
        fstp  DWORD PTR [esp+0xc]
        fld  DWORD PTR [esp+0xc]
        fadd  DWORD PTR ds:0x470d1c
        fcomp DWORD PTR [edi+0x40]
        fnstsw ax
        test  ah,0x41
        jnp loc_0041DA21
        mov  eax,DWORD PTR [esp+0x2c]
        test  eax,eax
        mov  DWORD PTR [esp+0x30],esi
        je loc_0041DD5A
        cmp  eax,esi
        jl loc_0041DB51
        mov  BYTE PTR [edi+0x50],0x1
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x340]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret  0xc
    loc_0041DB51:
        xor  ebx,ebx
        test  esi,esi
        mov  DWORD PTR [esp+0xc],ebx
        jle loc_0041DBEE
        nop
    loc_0041DB60:
        mov  al,BYTE PTR [esp+ebx*1+0x248]
        test  al,al
        je loc_0041DB70
        inc  ebx
        cmp  ebx,esi
        jl loc_0041DB60
    loc_0041DB70:
        test  ebx,ebx
        mov  DWORD PTR [esp+0xc],ebx
        je loc_0041DBEE
        fild  DWORD PTR [esp+0xc]
        mov  eax,DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR [esp+0x1c]
        add  eax,0x24
        fld  st(0)
        fld  DWORD PTR [esp+0x20]
        fmul  st,st(1)
        fld  DWORD PTR [esp+0x24]
        fmul  st,st(2)
        fstp  DWORD PTR [esp+0x44]
        fxch  st(1)
        fmul  DWORD PTR [esp+0x28]
        fstp  DWORD PTR [esp+0x48]
        fadd  DWORD PTR [eax]
        fstp  DWORD PTR [eax]
        fld  DWORD PTR [esp+0x44]
        fadd  DWORD PTR [eax+0x4]
        fstp  DWORD PTR [eax+0x4]
        fld  DWORD PTR [esp+0x48]
        fadd  DWORD PTR [eax+0x8]
        fstp  DWORD PTR [eax+0x8]
        fmul  DWORD PTR ds:0x470cd8
        fld  DWORD PTR [ecx+0x40]
        fsub  st,st(1)
        fcom  DWORD PTR ds:0x470c0c
        fst  DWORD PTR [ecx+0x40]
        fnstsw ax
        test  ah,0x41
        jne loc_0041DBE1
        fstp  DWORD PTR [ecx+0x434]
        fstp  DWORD PTR [ecx+0x4c]
        jmp loc_0041DBF2
    loc_0041DBE1:
        fstp  st(0)
        mov  BYTE PTR [ecx+0x50],0x1
        fstp  st(0)
        jmp loc_0041DD5A
    loc_0041DBEE:
        mov  ecx,DWORD PTR [esp+0x1c]
    loc_0041DBF2:
        xor  eax,eax
        cmp  ebx,esi
        mov  DWORD PTR [esp+0xc],eax
        jge loc_0041DD5A
    loc_0041DC00:
        mov  dl,BYTE PTR [esp+ebx*1+0x248]
        test  dl,dl
        jne loc_0041DC1A
        inc  ebx
        inc  eax
        cmp  ebx,esi
        jl loc_0041DC00
        mov  DWORD PTR [esp+0xc],eax
        jmp loc_0041DD5A
    loc_0041DC1A:
        cmp  ebx,esi
        mov  DWORD PTR [esp+0xc],eax
        jge loc_0041DD5A
        fild  DWORD PTR [esp+0xc]
        fmul  DWORD PTR ds:0x470cd8
        fld  DWORD PTR [ecx+0x40]
        fsub  st,st(1)
        fsubr DWORD PTR [ecx+0x434]
        fstp  DWORD PTR [ecx+0x434]
        fst  DWORD PTR [ecx+0x40]
        fcomp DWORD PTR ds:0x470c0c
        fnstsw ax
        test  ah,0x5
        jp loc_0041DC60
        mov  BYTE PTR [ecx+0x50],0x1
        jmp loc_0041DC60
    loc_0041DC57:
        mov  esi,DWORD PTR [esp+0x30]
        mov  ecx,DWORD PTR [esp+0x1c]
        nop
    loc_0041DC60:
        cmp  ebx,esi
        jge loc_0041DD5A
        jmp loc_0041DC70
        lea  ebx,[ebx+0x0]
    loc_0041DC70:
        mov  al,BYTE PTR [esp+ebx*1+0x248]
        test  al,al
        je loc_0041DC85
        inc  ebx
        cmp  ebx,esi
        jl loc_0041DC70
        jmp loc_0041DD5A
    loc_0041DC85:
        cmp  ebx,esi
        jge loc_0041DD5A
        xor  eax,eax
        mov  DWORD PTR [esp+0xc],eax
        mov  DWORD PTR [esp+0x58],ebx
        jmp loc_0041DCA0
        nop
    loc_0041DCA0:
        mov  dl,BYTE PTR [esp+ebx*1+0x248]
        test  dl,dl
        jne loc_0041DCB1
        inc  ebx
        inc  eax
        cmp  ebx,esi
        jl loc_0041DCA0
    loc_0041DCB1:
        mov  DWORD PTR [esp+0xc],eax
        fild  DWORD PTR [esp+0xc]
        lea  esi,[ecx+0x424]
        mov  ecx,0x77
        lea  edi,[esp+0x68]
        fmul  DWORD PTR ds:0x470cd8
        rep movsd
        fst  DWORD PTR [esp+0x7c]
        fst  DWORD PTR [esp+0x78]
        fcomp DWORD PTR ds:0x470c0c
        fnstsw ax
        test  ah,0x41
        jne loc_0041DD50
        fild  DWORD PTR [esp+0x58]
        mov  esi,DWORD PTR ds:0x47781c
        fld  DWORD PTR [esp+0x20]
        push  0x0
        lea  edi,[esp+0x6c]
        fmul  st,st(1)
        fld  DWORD PTR [esp+0x28]
        fmul  st,st(2)
        fstp  DWORD PTR [esp+0x48]
        fxch  st(1)
        fmul  DWORD PTR [esp+0x2c]
        fstp  DWORD PTR [esp+0x4c]
        fld  DWORD PTR [esp+0x60]
        fadd  st,st(1)
        fstp  DWORD PTR [esp+0x50]
        mov  edx,DWORD PTR [esp+0x50]
        mov  DWORD PTR [esp+0x6c],edx
        fstp  st(0)
        fld  DWORD PTR [esp+0x64]
        fadd  DWORD PTR [esp+0x48]
        fstp  DWORD PTR [esp+0x54]
        mov  eax,DWORD PTR [esp+0x54]
        fld  DWORD PTR [esp+0x68]
        mov  DWORD PTR [esp+0x70],eax
        fadd  DWORD PTR [esp+0x4c]
        fstp  DWORD PTR [esp+0x58]
        mov  ecx,DWORD PTR [esp+0x58]
        mov  DWORD PTR [esp+0x74],ecx
        call FUN_0041c510
    loc_0041DD50:
        cmp  ebx,DWORD PTR [esp+0x30]
        jl loc_0041DC57
    loc_0041DD5A:
        mov  ecx,DWORD PTR [esp+0x34c]
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
