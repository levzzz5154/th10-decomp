// 004267F0: FUN_004267f0
// Original size: 480 bytes, actual code: 132 instructions
extern "C" void FUN_00426cf0(void);

extern "C" __declspec(naked) void FUN_004267f0(void) {
    __asm {
        sub  esp,0x24
        fld  DWORD PTR [ecx+0x3c0]
        fsub  DWORD PTR [eax]
        fstp  DWORD PTR [esp+0xc]
        fld  DWORD PTR [ecx+0x3c4]
        fsub  DWORD PTR [eax+0x4]
        fstp  DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [esp+0x10]
        fld  DWORD PTR [ecx+0x3c8]
        mov  DWORD PTR [esp+0x4],edx
        fsub  DWORD PTR [eax+0x8]
        mov  eax,DWORD PTR [esp+0xc]
        mov  DWORD PTR [esp],eax
        fstp  DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x14]
        fld  DWORD PTR [esp+0x28]
        mov  DWORD PTR [esp+0x8],eax
        fchs
        fld  st(0)
        fsin
        fxch  st(1)
        fcos
        fld  DWORD PTR [esp]
        fmul  st,st(1)
        fld  st(2)
        fmul  DWORD PTR [esp+0x4]
        fsubp st(1),st
        fstp  DWORD PTR [esp+0xc]
        fmul  DWORD PTR [esp+0x4]
        fxch  st(1)
        fmul  DWORD PTR [esp]
        faddp st(1),st
        fld  DWORD PTR [esp+0xc]
        fsub  DWORD PTR [ecx+0x41c]
        fstp  DWORD PTR [esp+0x18]
        mov  edx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [esp],edx
        fld  st(0)
        fsub  DWORD PTR [ecx+0x420]
        fstp  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esp+0x14]
        mov  DWORD PTR [esp+0x4],eax
        fsub  DWORD PTR [ecx+0x424]
        fstp  DWORD PTR [esp+0x20]
        mov  edx,DWORD PTR [esp+0x20]
        fld  DWORD PTR [esp+0xc]
        mov  DWORD PTR [esp+0x8],edx
        fadd  DWORD PTR [ecx+0x41c]
        fstp  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [esp+0x18]
        mov  DWORD PTR [esp+0xc],eax
        fadd  DWORD PTR [ecx+0x420]
        fstp  DWORD PTR [esp+0x1c]
        mov  edx,DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esp+0x14]
        mov  DWORD PTR [esp+0x10],edx
        fadd  DWORD PTR [ecx+0x424]
        fstp  DWORD PTR [esp+0x20]
        mov  eax,DWORD PTR [esp+0x20]
        fld  DWORD PTR [esp]
        mov  DWORD PTR [esp+0x14],eax
        fcomp DWORD PTR [esp+0x30]
        fnstsw ax
        test  ah,0x41
        je loc_004269BF
        fld  DWORD PTR [esp+0x2c]
        fmul  DWORD PTR ds:0x470b0c
        fcomp DWORD PTR [esp+0x4]
        fnstsw ax
        test  ah,0x5
        jnp loc_0042696B
        fld  DWORD PTR [esp+0xc]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jnp loc_0042696B
        fld  DWORD PTR [esp+0x2c]
        fmul  DWORD PTR ds:0x470b78
        fcomp DWORD PTR [esp+0x10]
        fnstsw ax
        test  ah,0x41
        je loc_0042696B
        mov  eax,ds:0x47770c
        test  eax,eax
        je loc_0042693B
        mov  edx,DWORD PTR [eax+0x9eb8]
        test  edx,edx
        jne loc_004269BF
    loc_0042693B:
        mov  eax,DWORD PTR [ecx+0x458]
        cmp  eax,0x2
        je loc_004269BF
        cmp  eax,0x4
        je loc_004269BF
        cmp  eax,0x3
        je loc_004269BF
        mov  eax,DWORD PTR [ecx+0x4310]
        test  eax,eax
        jg loc_004269BF
        push  ecx
        call FUN_00426cf0
        mov  eax,0x1
        add  esp,0x24
        ret  0xc
    loc_0042696B:
        fld  DWORD PTR [esp]
        fcomp DWORD PTR [esp+0x30]
        fnstsw ax
        test  ah,0x41
        je loc_004269BF
        fld  DWORD PTR [esp+0xc]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jnp loc_004269BF
        fld  DWORD PTR [esp+0x2c]
        fmul  DWORD PTR ds:0x470ca8
        fcomp DWORD PTR [esp+0x4]
        fnstsw ax
        test  ah,0x5
        jnp loc_004269BF
        fld  DWORD PTR [esp+0x2c]
        fmul  DWORD PTR ds:0x470ca4
        fcomp DWORD PTR [esp+0x4]
        fnstsw ax
        test  ah,0x41
        je loc_004269BF
        mov  eax,0x2
        add  esp,0x24
        ret  0xc
    loc_004269BF:
        xor  eax,eax
        add  esp,0x24
        ret  0xc
    }
}
