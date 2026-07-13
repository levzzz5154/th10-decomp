// 0041EB00: FUN_0041eb00
// Original size: 1184 bytes, actual code: 316 instructions
extern "C" void FUN_0041bb00(void);
extern "C" void FUN_0041c510(void);
extern "C" void FUN_0041f7a0(void);
extern "C" void FUN_0041f800(void);
extern "C" void FUN_00448db0(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0041eb00(void) {
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
        mov  DWORD PTR [esp+0x24],eax
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
        mov  eax,DWORD PTR [esp+0x2c]
        mov  edi,DWORD PTR [esp+0x1c]
        xor  esi,esi
        fld  DWORD PTR [eax]
        push  0x40c00000
        fmul  DWORD PTR ds:0x470b0c
        mov  DWORD PTR [esp+0x34],esi
        mov  DWORD PTR [esp+0x10],0x40c00000
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
        mov  DWORD PTR [esp+0x50],ecx
        fsub  DWORD PTR [esp+0x3c]
        fstp  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [esp+0x18]
        fld  DWORD PTR [edx+0x8]
        mov  DWORD PTR [esp+0x54],eax
        fsub  DWORD PTR [esp+0x40]
        fstp  DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esp+0x38]
        mov  DWORD PTR [esp+0x58],ecx
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
        lea  ecx,[esp+0x18]
        mov  DWORD PTR [esp+0x20],esi
        call FUN_0041f800
        fld  DWORD PTR [esp+0x10]
        fadd  DWORD PTR [ebx]
        fstp  DWORD PTR [esp+0x40]
        mov  eax,DWORD PTR [esp+0x40]
        fld  DWORD PTR [esp+0x14]
        mov  DWORD PTR [esp+0x20],eax
        fadd  DWORD PTR [ebx+0x4]
        fstp  DWORD PTR [esp+0x44]
        mov  ecx,DWORD PTR [esp+0x44]
        fld  DWORD PTR [esp+0x18]
        mov  DWORD PTR [esp+0x24],ecx
        fadd  DWORD PTR [ebx+0x8]
        fstp  DWORD PTR [esp+0x48]
        mov  edx,DWORD PTR [esp+0x48]
        fld  DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0x28],edx
        fadd  st(0),st
        mov  DWORD PTR [esp+0x28],esi
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [esp+0x14]
        fadd  st(0),st
        fstp  DWORD PTR [esp+0x14]
        fld  DWORD PTR [esp+0x18]
        fadd  st(0),st
        fstp  DWORD PTR [esp+0x18]
        fld  DWORD PTR ds:0x470cd8
        fcomp DWORD PTR [edi+0x40]
        fnstsw ax
        test  ah,0x5
        jp loc_0041EF78
        mov  ebx,DWORD PTR [ebp+0x10]
    loc_0041ECA1:
        fld  DWORD PTR [esp+0x20]
        fcomp DWORD PTR [esp+0x4c]
        fnstsw ax
        test  ah,0x5
        jnp loc_0041ED57
        fld  DWORD PTR [esp+0x20]
        fcomp DWORD PTR [esp+0x34]
        fnstsw ax
        test  ah,0x41
        je loc_0041ED57
        fld  DWORD PTR [esp+0x24]
        fcomp DWORD PTR [esp+0x50]
        fnstsw ax
        test  ah,0x5
        jnp loc_0041ED57
        fld  DWORD PTR [esp+0x24]
        fcomp DWORD PTR [esp+0x38]
        fnstsw ax
        test  ah,0x41
        je loc_0041ED57
        mov  ecx,DWORD PTR [esp+0x30]
        inc  ecx
        test  ebx,ebx
        mov  BYTE PTR [esp+esi*1+0x248],0x1
        mov  DWORD PTR [esp+0x30],ecx
        je loc_0041ED2D
        push  0x42000000
        push  0x42000000
        lea  ecx,[esp+0x28]
        call FUN_0041f7a0
        test  eax,eax
        jne loc_0041ED2D
        mov  eax,ds:0x477818
        push  0x3f19999a
        push  0xbfc90fdb
        push  0xffffffff
        push  0x8
        call FUN_0041bb00
    loc_0041ED2D:
        movsx eax,WORD PTR [edi+0x466]
        lea  ecx,[eax+eax*1+0x11]
        mov  eax,ds:0x47781c
        push  ecx
        mov  ecx,DWORD PTR [eax+0x458]
        lea  edx,[esp+0x5c]
        push  edx
        push  ecx
        lea  edi,[esp+0x2c]
        call FUN_00448db0
        mov  edi,DWORD PTR [esp+0x1c]
    loc_0041ED57:
        fld  DWORD PTR [esp+0x10]
        inc  esi
        fadd  DWORD PTR [esp+0x20]
        fstp  DWORD PTR [esp+0x20]
        fld  DWORD PTR [esp+0x14]
        fadd  DWORD PTR [esp+0x24]
        fstp  DWORD PTR [esp+0x24]
        fld  DWORD PTR [esp+0x28]
        fadd  DWORD PTR [esp+0x18]
        fstp  DWORD PTR [esp+0x28]
        fld  DWORD PTR [esp+0xc]
        fadd  DWORD PTR ds:0x470cd8
        fstp  DWORD PTR [esp+0xc]
        fld  DWORD PTR [esp+0xc]
        fadd  DWORD PTR ds:0x470d1c
        fcomp DWORD PTR [edi+0x40]
        fnstsw ax
        test  ah,0x5
        jnp loc_0041ECA1
        mov  eax,DWORD PTR [esp+0x30]
        test  eax,eax
        mov  DWORD PTR [esp+0x2c],esi
        je loc_0041EF78
        xor  eax,eax
        xor  ebx,ebx
        cmp  esi,eax
        jle loc_0041EDDD
        lea  ebx,[ebx+0x0]
    loc_0041EDC0:
        mov  cl,BYTE PTR [esp+ebx*1+0x248]
        test  cl,cl
        je loc_0041EDD0
        inc  ebx
        cmp  ebx,esi
        jl loc_0041EDC0
    loc_0041EDD0:
        cmp  ebx,eax
        je loc_0041EDDD
        mov  edx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [edx+0x40],eax
        jmp loc_0041EE27
    loc_0041EDDD:
        cmp  esi,eax
        mov  DWORD PTR [esp+0xc],eax
        jle loc_0041EF78
        nop
    loc_0041EDF0:
        mov  cl,BYTE PTR [esp+ebx*1+0x248]
        test  cl,cl
        jne loc_0041EE0A
        inc  ebx
        inc  eax
        cmp  ebx,esi
        jl loc_0041EDF0
        mov  DWORD PTR [esp+0xc],eax
        jmp loc_0041EF78
    loc_0041EE0A:
        cmp  ebx,esi
        mov  DWORD PTR [esp+0xc],eax
        jge loc_0041EF78
        fild  DWORD PTR [esp+0xc]
        mov  edx,DWORD PTR [esp+0x1c]
        fmul  DWORD PTR ds:0x470cd8
        fstp  DWORD PTR [edx+0x40]
    loc_0041EE27:
        cmp  ebx,esi
        jge loc_0041EF78
        jmp loc_0041EE40
    loc_0041EE31:
        mov  esi,DWORD PTR [esp+0x2c]
        mov  edx,DWORD PTR [esp+0x1c]
        nop
    loc_0041EE40:
        cmp  ebx,esi
        jge loc_0041EF78
        jmp loc_0041EE50
        lea  ebx,[ebx+0x0]
    loc_0041EE50:
        mov  al,BYTE PTR [esp+ebx*1+0x248]
        test  al,al
        je loc_0041EE65
        inc  ebx
        cmp  ebx,esi
        jl loc_0041EE50
        jmp loc_0041EF78
    loc_0041EE65:
        cmp  ebx,esi
        jge loc_0041EF78
        xor  eax,eax
        mov  DWORD PTR [esp+0xc],eax
        mov  DWORD PTR [esp+0x58],ebx
        jmp loc_0041EE80
        nop
    loc_0041EE80:
        mov  cl,BYTE PTR [esp+ebx*1+0x248]
        test  cl,cl
        jne loc_0041EE91
        inc  ebx
        inc  eax
        cmp  ebx,esi
        jl loc_0041EE80
    loc_0041EE91:
        mov  DWORD PTR [esp+0xc],eax
        fild  DWORD PTR [esp+0xc]
        xor  eax,eax
        mov  ecx,0x77
        lea  edi,[esp+0x68]
        fmul  DWORD PTR ds:0x470cd8
        rep stosd
        fst  DWORD PTR [esp+0x7c]
        fstp  DWORD PTR [esp+0x78]
        mov  esi,DWORD PTR ds:0x47781c
        fild  DWORD PTR [esp+0x58]
        push  0x0
        lea  edi,[esp+0x6c]
        mov  DWORD PTR [esp+0x8c],0x41000000
        fld  st(0)
        fld  DWORD PTR [esp+0x14]
        fmul  st,st(1)
        fld  DWORD PTR [esp+0x18]
        fmul  st,st(2)
        fstp  DWORD PTR [esp+0x54]
        fxch  st(1)
        fmul  DWORD PTR [esp+0x1c]
        fstp  DWORD PTR [esp+0x58]
        fld  DWORD PTR [esp+0x60]
        fadd  st,st(1)
        fstp  DWORD PTR [esp+0x44]
        mov  eax,DWORD PTR [esp+0x44]
        mov  DWORD PTR [esp+0x6c],eax
        fstp  st(0)
        fld  DWORD PTR [esp+0x64]
        fadd  DWORD PTR [esp+0x54]
        fstp  DWORD PTR [esp+0x48]
        mov  ecx,DWORD PTR [esp+0x48]
        fld  DWORD PTR [esp+0x68]
        mov  DWORD PTR [esp+0x70],ecx
        fadd  DWORD PTR [esp+0x58]
        mov  ecx,DWORD PTR [edx+0x3c]
        mov  DWORD PTR [esp+0x78],ecx
        mov  cx,WORD PTR [edx+0x464]
        fstp  DWORD PTR [esp+0x4c]
        mov  eax,DWORD PTR [esp+0x4c]
        mov  DWORD PTR [esp+0x74],eax
        fmul  DWORD PTR ds:0x470cd8
        mov  eax,DWORD PTR [edx+0x44]
        mov  DWORD PTR [esp+0x88],eax
        mov  ax,WORD PTR [edx+0x466]
        fsubr DWORD PTR [edx+0x444]
        mov  WORD PTR [esp+0x90],cx
        mov  WORD PTR [esp+0x92],ax
        fstp  DWORD PTR [esp+0x84]
        call FUN_0041c510
        cmp  ebx,DWORD PTR [esp+0x2c]
        jl loc_0041EE31
    loc_0041EF78:
        mov  ecx,DWORD PTR [esp+0x34c]
        mov  eax,DWORD PTR [esp+0x30]
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
