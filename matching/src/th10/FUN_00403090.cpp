// 00403090: FUN_00403090
// Original size: 1984 bytes, actual code: 518 instructions
extern "C" void D3DXMatrixTranslation(void);
extern "C" void D3DXVec3ProjectArray(void);

extern "C" __declspec(naked) void FUN_00403090(void) {
    __asm {
        sub  esp,0x128
        fld  DWORD PTR [ecx+0x4]
        push  esi
        fadd  DWORD PTR [edx]
        mov  esi,eax
        fstp  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [esp+0x10]
        fld  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esp+0x8c],eax
        fadd  DWORD PTR [edx+0x4]
        fstp  DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x14]
        fld  DWORD PTR [ecx+0xc]
        mov  DWORD PTR [esp+0x90],eax
        fadd  DWORD PTR [edx+0x8]
        fstp  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [esp+0x18]
        fld  DWORD PTR [esi+0x3c]
        mov  DWORD PTR [esp+0x94],eax
        fadd  DWORD PTR [esi]
        fld  DWORD PTR [esi+0x40]
        fadd  DWORD PTR [esi+0x4]
        fld  DWORD PTR [esi+0x44]
        fadd  DWORD PTR [esi+0x8]
        fstp  DWORD PTR [esp+0x84]
        fld  DWORD PTR [esp+0x8c]
        fsub  st,st(2)
        fstp  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [esp+0x10]
        fld  DWORD PTR [esp+0x90]
        mov  DWORD PTR [esp+0x8c],eax
        fsub  st,st(1)
        fstp  DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x14]
        mov  DWORD PTR [esp+0x90],eax
        fstp  st(0)
        fstp  st(0)
        fld  DWORD PTR [esp+0x94]
        fsub  DWORD PTR [esp+0x84]
        fstp  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [esp+0x18]
        mov  DWORD PTR [esp+0x94],eax
        fld  DWORD PTR [esp+0x94]
        fmul  DWORD PTR [esp+0x94]
        fld  DWORD PTR [esp+0x90]
        fmul  DWORD PTR [esp+0x90]
        faddp st(1),st
        fld  DWORD PTR [esp+0x8c]
        fmul  DWORD PTR [esp+0x8c]
        faddp st(1),st
        fcomp DWORD PTR [esp+0x130]
        fnstsw ax
        test  ah,0x41
        je loc_00403841
        fld  DWORD PTR [ecx+0x10]
        mov  DWORD PTR [esp+0x124],0x0
        fmul  DWORD PTR ds:0x470b0c
        mov  DWORD PTR [esp+0x120],0x0
        mov  DWORD PTR [esp+0x11c],0x0
        mov  DWORD PTR [esp+0x118],0x0
        fstp  DWORD PTR [esp+0x7c]
        mov  eax,DWORD PTR [esp+0x7c]
        fld  DWORD PTR [ecx+0x14]
        mov  DWORD PTR [esp+0x10],eax
        fmul  DWORD PTR ds:0x470b0c
        mov  DWORD PTR [esp+0x110],0x0
        mov  DWORD PTR [esp+0x10c],0x0
        mov  DWORD PTR [esp+0x108],0x0
        fstp  DWORD PTR [esp+0x80]
        mov  eax,DWORD PTR [esp+0x80]
        fld  DWORD PTR [ecx+0x18]
        mov  DWORD PTR [esp+0x14],eax
        fmul  DWORD PTR ds:0x470b0c
        mov  DWORD PTR [esp+0x104],0x0
        mov  DWORD PTR [esp+0xfc],0x0
        fstp  DWORD PTR [esp+0x84]
        mov  eax,DWORD PTR [esp+0x84]
        fld  DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0x18],eax
        fadd  DWORD PTR [ecx+0x4]
        fst  DWORD PTR [esp+0x8c]
        fld  DWORD PTR [esp+0x14]
        fadd  DWORD PTR [ecx+0x8]
        fst  DWORD PTR [esp+0x90]
        fld  DWORD PTR [esp+0x18]
        fadd  DWORD PTR [ecx+0xc]
        fst  DWORD PTR [esp+0x88]
        fst  DWORD PTR [esp+0x94]
        fld  st(2)
        fstp  DWORD PTR [esp+0x98]
        fld  st(1)
        fstp  DWORD PTR [esp+0x9c]
        fld  DWORD PTR [ecx+0xc]
        fsub  DWORD PTR [esp+0x18]
        fst  DWORD PTR [esp+0x8]
        fst  DWORD PTR [esp+0xa0]
        fld  st(3)
        fstp  DWORD PTR [esp+0xa4]
        fld  DWORD PTR [ecx+0x8]
        fsub  DWORD PTR [esp+0x14]
        fst  DWORD PTR [esp+0x4]
        fst  DWORD PTR [esp+0xa8]
        fld  st(2)
        fstp  DWORD PTR [esp+0xac]
        fxch  st(4)
        fstp  DWORD PTR [esp+0xb0]
        fxch  st(3)
        fstp  DWORD PTR [esp+0xb4]
        fxch  st(2)
        fstp  DWORD PTR [esp+0xb8]
        fld  DWORD PTR [ecx+0x4]
        mov  ecx,DWORD PTR [esp+0x8]
        fsub  DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0xd0],ecx
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR [esp+0xd8],ecx
        fst  DWORD PTR [esp+0xc]
        mov  eax,DWORD PTR [esp+0xc]
        fst  DWORD PTR [esp+0xbc]
        mov  ecx,DWORD PTR [esp+0xc]
        fld  st(1)
        fstp  DWORD PTR [esp+0xc0]
        mov  DWORD PTR [esp+0xd4],eax
        mov  eax,DWORD PTR [esp+0x88]
        fxch  st(2)
        fstp  DWORD PTR [esp+0xc4]
        mov  DWORD PTR [esp+0xdc],eax
        mov  eax,DWORD PTR [esp+0x4]
        fxch  st(1)
        fstp  DWORD PTR [esp+0xc8]
        mov  DWORD PTR [esp+0xe0],ecx
        mov  ecx,DWORD PTR [esp+0x8]
        fstp  DWORD PTR [esp+0xcc]
        mov  DWORD PTR [esp+0xe4],eax
        mov  DWORD PTR [esp+0xe8],ecx
        mov  eax,DWORD PTR [edx+0x8]
        mov  ecx,DWORD PTR [edx+0x4]
        mov  edx,DWORD PTR [edx]
        push  eax
        push  ecx
        push  edx
        lea  eax,[esp+0xf8]
        push  eax
        mov  DWORD PTR [esp+0x108],0x0
        mov  DWORD PTR [esp+0x104],0x0
        mov  DWORD PTR [esp+0x100],0x0
        mov  DWORD PTR [esp+0x138],0x3f800000
        mov  DWORD PTR [esp+0x124],0x3f800000
        mov  DWORD PTR [esp+0x110],0x3f800000
        mov  DWORD PTR [esp+0xfc],0x3f800000
        call D3DXMatrixTranslation
        push  0x8
        lea  ecx,[esp+0xf0]
        push  ecx
        lea  edx,[esi+0x4c]
        push  edx
        lea  eax,[esi+0x8c]
        push  eax
        add  esi,0xcc
        push  esi
        push  0xc
        lea  ecx,[esp+0xa4]
        push  ecx
        push  0xc
        lea  edx,[esp+0x3c]
        push  edx
        call D3DXVec3ProjectArray
        fld  DWORD PTR ds:0x470be8
        fld  DWORD PTR [esp+0x24]
        mov  DWORD PTR [esp+0x8],0x43d40000
        fcomp DWORD PTR ds:0x470b04
        mov  DWORD PTR [esp+0xc],0x43ec0000
        mov  DWORD PTR [esp+0x4],0x41000000
        fnstsw ax
        test  ah,0x1
        jne loc_00403483
        fld  DWORD PTR [esp+0x24]
        fcomp DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x41
        jp loc_00403483
        fld  DWORD PTR [esp+0x1c]
        fcomp DWORD PTR ds:0x470be4
        fnstsw ax
        test  ah,0x5
        jp loc_00403438
        mov  eax,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esp+0x8],eax
        jmp loc_0040344F
    loc_00403438:
        fld  DWORD PTR [esp+0x1c]
        fcomp DWORD PTR ds:0x470be8
        fnstsw ax
        test  ah,0x41
        jne loc_0040344F
        fstp  st(0)
        fld  DWORD PTR [esp+0x1c]
    loc_0040344F:
        fld  DWORD PTR [esp+0x20]
        fcomp DWORD PTR ds:0x470be0
        fnstsw ax
        test  ah,0x5
        jp loc_0040346A
        mov  ecx,DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0xc],ecx
        jmp loc_00403483
    loc_0040346A:
        fld  DWORD PTR [esp+0x20]
        fcomp DWORD PTR ds:0x470bd0
        fnstsw ax
        test  ah,0x41
        jne loc_00403483
        mov  edx,DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x4],edx
    loc_00403483:
        fld  DWORD PTR [esp+0x30]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x1
        jne loc_00403501
        fld  DWORD PTR [esp+0x30]
        fcomp DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x41
        jp loc_00403501
        fld  DWORD PTR [esp+0x28]
        fcomp DWORD PTR [esp+0x8]
        fnstsw ax
        test  ah,0x5
        jp loc_004034BE
        mov  eax,DWORD PTR [esp+0x28]
        mov  DWORD PTR [esp+0x8],eax
        jmp loc_004034D1
    loc_004034BE:
        fld  DWORD PTR [esp+0x28]
        fcomp st(1)
        fnstsw ax
        test  ah,0x41
        jne loc_004034D1
        fstp  st(0)
        fld  DWORD PTR [esp+0x28]
    loc_004034D1:
        fld  DWORD PTR [esp+0x2c]
        fcomp DWORD PTR [esp+0xc]
        fnstsw ax
        test  ah,0x5
        jp loc_004034EA
        mov  ecx,DWORD PTR [esp+0x2c]
        mov  DWORD PTR [esp+0xc],ecx
        jmp loc_00403501
    loc_004034EA:
        fld  DWORD PTR [esp+0x2c]
        fcomp DWORD PTR [esp+0x4]
        fnstsw ax
        test  ah,0x41
        jne loc_00403501
        mov  edx,DWORD PTR [esp+0x2c]
        mov  DWORD PTR [esp+0x4],edx
    loc_00403501:
        fld  DWORD PTR [esp+0x3c]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x1
        jne loc_0040357F
        fld  DWORD PTR [esp+0x3c]
        fcomp DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x41
        jp loc_0040357F
        fld  DWORD PTR [esp+0x34]
        fcomp DWORD PTR [esp+0x8]
        fnstsw ax
        test  ah,0x5
        jp loc_0040353C
        mov  eax,DWORD PTR [esp+0x34]
        mov  DWORD PTR [esp+0x8],eax
        jmp loc_0040354F
    loc_0040353C:
        fld  DWORD PTR [esp+0x34]
        fcomp st(1)
        fnstsw ax
        test  ah,0x41
        jne loc_0040354F
        fstp  st(0)
        fld  DWORD PTR [esp+0x34]
    loc_0040354F:
        fld  DWORD PTR [esp+0x38]
        fcomp DWORD PTR [esp+0xc]
        fnstsw ax
        test  ah,0x5
        jp loc_00403568
        mov  ecx,DWORD PTR [esp+0x38]
        mov  DWORD PTR [esp+0xc],ecx
        jmp loc_0040357F
    loc_00403568:
        fld  DWORD PTR [esp+0x38]
        fcomp DWORD PTR [esp+0x4]
        fnstsw ax
        test  ah,0x41
        jne loc_0040357F
        mov  edx,DWORD PTR [esp+0x38]
        mov  DWORD PTR [esp+0x4],edx
    loc_0040357F:
        fld  DWORD PTR [esp+0x48]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x1
        jne loc_004035FD
        fld  DWORD PTR [esp+0x48]
        fcomp DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x41
        jp loc_004035FD
        fld  DWORD PTR [esp+0x40]
        fcomp DWORD PTR [esp+0x8]
        fnstsw ax
        test  ah,0x5
        jp loc_004035BA
        mov  eax,DWORD PTR [esp+0x40]
        mov  DWORD PTR [esp+0x8],eax
        jmp loc_004035CD
    loc_004035BA:
        fld  DWORD PTR [esp+0x40]
        fcomp st(1)
        fnstsw ax
        test  ah,0x41
        jne loc_004035CD
        fstp  st(0)
        fld  DWORD PTR [esp+0x40]
    loc_004035CD:
        fld  DWORD PTR [esp+0x44]
        fcomp DWORD PTR [esp+0xc]
        fnstsw ax
        test  ah,0x5
        jp loc_004035E6
        mov  ecx,DWORD PTR [esp+0x44]
        mov  DWORD PTR [esp+0xc],ecx
        jmp loc_004035FD
    loc_004035E6:
        fld  DWORD PTR [esp+0x44]
        fcomp DWORD PTR [esp+0x4]
        fnstsw ax
        test  ah,0x41
        jne loc_004035FD
        mov  edx,DWORD PTR [esp+0x44]
        mov  DWORD PTR [esp+0x4],edx
    loc_004035FD:
        fld  DWORD PTR [esp+0x54]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x1
        jne loc_0040367B
        fld  DWORD PTR [esp+0x54]
        fcomp DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x41
        jp loc_0040367B
        fld  DWORD PTR [esp+0x4c]
        fcomp DWORD PTR [esp+0x8]
        fnstsw ax
        test  ah,0x5
        jp loc_00403638
        mov  eax,DWORD PTR [esp+0x4c]
        mov  DWORD PTR [esp+0x8],eax
        jmp loc_0040364B
    loc_00403638:
        fld  DWORD PTR [esp+0x4c]
        fcomp st(1)
        fnstsw ax
        test  ah,0x41
        jne loc_0040364B
        fstp  st(0)
        fld  DWORD PTR [esp+0x4c]
    loc_0040364B:
        fld  DWORD PTR [esp+0x50]
        fcomp DWORD PTR [esp+0xc]
        fnstsw ax
        test  ah,0x5
        jp loc_00403664
        mov  ecx,DWORD PTR [esp+0x50]
        mov  DWORD PTR [esp+0xc],ecx
        jmp loc_0040367B
    loc_00403664:
        fld  DWORD PTR [esp+0x50]
        fcomp DWORD PTR [esp+0x4]
        fnstsw ax
        test  ah,0x41
        jne loc_0040367B
        mov  edx,DWORD PTR [esp+0x50]
        mov  DWORD PTR [esp+0x4],edx
    loc_0040367B:
        fld  DWORD PTR [esp+0x60]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x1
        jne loc_004036F9
        fld  DWORD PTR [esp+0x60]
        fcomp DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x41
        jp loc_004036F9
        fld  DWORD PTR [esp+0x58]
        fcomp DWORD PTR [esp+0x8]
        fnstsw ax
        test  ah,0x5
        jp loc_004036B6
        mov  eax,DWORD PTR [esp+0x58]
        mov  DWORD PTR [esp+0x8],eax
        jmp loc_004036C9
    loc_004036B6:
        fld  DWORD PTR [esp+0x58]
        fcomp st(1)
        fnstsw ax
        test  ah,0x41
        jne loc_004036C9
        fstp  st(0)
        fld  DWORD PTR [esp+0x58]
    loc_004036C9:
        fld  DWORD PTR [esp+0x5c]
        fcomp DWORD PTR [esp+0xc]
        fnstsw ax
        test  ah,0x5
        jp loc_004036E2
        mov  ecx,DWORD PTR [esp+0x5c]
        mov  DWORD PTR [esp+0xc],ecx
        jmp loc_004036F9
    loc_004036E2:
        fld  DWORD PTR [esp+0x5c]
        fcomp DWORD PTR [esp+0x4]
        fnstsw ax
        test  ah,0x41
        jne loc_004036F9
        mov  edx,DWORD PTR [esp+0x5c]
        mov  DWORD PTR [esp+0x4],edx
    loc_004036F9:
        fld  DWORD PTR [esp+0x6c]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x1
        jne loc_00403777
        fld  DWORD PTR [esp+0x6c]
        fcomp DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x41
        jp loc_00403777
        fld  DWORD PTR [esp+0x64]
        fcomp DWORD PTR [esp+0x8]
        fnstsw ax
        test  ah,0x5
        jp loc_00403734
        mov  eax,DWORD PTR [esp+0x64]
        mov  DWORD PTR [esp+0x8],eax
        jmp loc_00403747
    loc_00403734:
        fld  DWORD PTR [esp+0x64]
        fcomp st(1)
        fnstsw ax
        test  ah,0x41
        jne loc_00403747
        fstp  st(0)
        fld  DWORD PTR [esp+0x64]
    loc_00403747:
        fld  DWORD PTR [esp+0x68]
        fcomp DWORD PTR [esp+0xc]
        fnstsw ax
        test  ah,0x5
        jp loc_00403760
        mov  ecx,DWORD PTR [esp+0x68]
        mov  DWORD PTR [esp+0xc],ecx
        jmp loc_00403777
    loc_00403760:
        fld  DWORD PTR [esp+0x68]
        fcomp DWORD PTR [esp+0x4]
        fnstsw ax
        test  ah,0x41
        jne loc_00403777
        mov  edx,DWORD PTR [esp+0x68]
        mov  DWORD PTR [esp+0x4],edx
    loc_00403777:
        fld  DWORD PTR [esp+0x78]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x1
        jne loc_004037F5
        fld  DWORD PTR [esp+0x78]
        fcomp DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x41
        jp loc_004037F5
        fld  DWORD PTR [esp+0x70]
        fcomp DWORD PTR [esp+0x8]
        fnstsw ax
        test  ah,0x5
        jp loc_004037B2
        mov  eax,DWORD PTR [esp+0x70]
        mov  DWORD PTR [esp+0x8],eax
        jmp loc_004037C5
    loc_004037B2:
        fld  DWORD PTR [esp+0x70]
        fcomp st(1)
        fnstsw ax
        test  ah,0x41
        jne loc_004037C5
        fstp  st(0)
        fld  DWORD PTR [esp+0x70]
    loc_004037C5:
        fld  DWORD PTR [esp+0x74]
        fcomp DWORD PTR [esp+0xc]
        fnstsw ax
        test  ah,0x5
        jp loc_004037DE
        mov  ecx,DWORD PTR [esp+0x74]
        mov  DWORD PTR [esp+0xc],ecx
        jmp loc_004037F5
    loc_004037DE:
        fld  DWORD PTR [esp+0x74]
        fcomp DWORD PTR [esp+0x4]
        fnstsw ax
        test  ah,0x41
        jne loc_004037F5
        mov  edx,DWORD PTR [esp+0x74]
        mov  DWORD PTR [esp+0x4],edx
    loc_004037F5:
        fcomp DWORD PTR ds:0x470bcc
        fnstsw ax
        test  ah,0x1
        jne loc_00403841
        fld  DWORD PTR [esp+0x8]
        fcomp DWORD PTR ds:0x470bdc
        fnstsw ax
        test  ah,0x41
        jp loc_00403841
        fld  DWORD PTR [esp+0x4]
        fcomp DWORD PTR ds:0x470b48
        fnstsw ax
        test  ah,0x1
        jne loc_00403841
        fld  DWORD PTR [esp+0xc]
        fcomp DWORD PTR ds:0x470bd8
        fnstsw ax
        test  ah,0x41
        jp loc_00403841
        xor  eax,eax
        pop  esi
        add  esp,0x128
        ret  0x4
    loc_00403841:
        mov  eax,0x1
        pop  esi
        add  esp,0x128
        ret  0x4
    }
}
