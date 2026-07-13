// 004266B0: FUN_004266b0
// Original size: 320 bytes, actual code: 92 instructions
extern "C" void FUN_00426cf0(void);

extern "C" __declspec(naked) void FUN_004266b0(void) {
    __asm {
        sub  esp,0x10
        fld  DWORD PTR [eax]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [ecx]
        fsub  st,st(1)
        fstp  DWORD PTR [esp]
        fld  DWORD PTR [eax+0x4]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [ecx+0x4]
        fsub  st,st(1)
        fstp  DWORD PTR [esp+0x4]
        fxch  st(1)
        fadd  DWORD PTR [ecx]
        fstp  DWORD PTR [esp+0x8]
        fadd  DWORD PTR [ecx+0x4]
        fld  DWORD PTR [edx+0x404]
        fcomp DWORD PTR [esp+0x8]
        fnstsw ax
        test  ah,0x41
        je loc_0042676F
        fcomp DWORD PTR [edx+0x408]
        fnstsw ax
        test  ah,0x5
        jnp loc_00426771
        fld  DWORD PTR [edx+0x410]
        fcomp DWORD PTR [esp]
        fnstsw ax
        test  ah,0x5
        jnp loc_00426771
        fld  DWORD PTR [edx+0x414]
        fcomp DWORD PTR [esp+0x4]
        fnstsw ax
        test  ah,0x5
        jnp loc_00426771
        mov  eax,ds:0x47770c
        test  eax,eax
        je loc_00426735
        mov  ecx,DWORD PTR [eax+0x9eb8]
        test  ecx,ecx
        jne loc_004267E6
    loc_00426735:
        mov  eax,DWORD PTR [edx+0x458]
        cmp  eax,0x2
        je loc_004267E6
        cmp  eax,0x4
        je loc_004267E6
        cmp  eax,0x3
        je loc_004267E6
        mov  eax,DWORD PTR [edx+0x4310]
        test  eax,eax
        jg loc_00426766
        push  edx
        call FUN_00426cf0
    loc_00426766:
        mov  eax,0x1
        add  esp,0x10
        ret
    loc_0042676F:
        fstp  st(0)
    loc_00426771:
        fld  DWORD PTR [ecx]
        fsub  DWORD PTR ds:0x470be8
        fstp  DWORD PTR [esp]
        fld  DWORD PTR [ecx+0x4]
        fsub  DWORD PTR ds:0x470be8
        fstp  DWORD PTR [esp+0x4]
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR ds:0x470be8
        fld  DWORD PTR [ecx+0x4]
        fadd  DWORD PTR ds:0x470be8
        fstp  DWORD PTR [esp+0xc]
        fcomp DWORD PTR [edx+0x404]
        fnstsw ax
        test  ah,0x5
        jnp loc_004267E6
        fld  DWORD PTR [edx+0x408]
        fcomp DWORD PTR [esp+0xc]
        fnstsw ax
        test  ah,0x41
        je loc_004267E6
        fld  DWORD PTR [edx+0x410]
        fcomp DWORD PTR [esp]
        fnstsw ax
        test  ah,0x5
        jnp loc_004267E6
        fld  DWORD PTR [edx+0x414]
        fcomp DWORD PTR [esp+0x4]
        fnstsw ax
        test  ah,0x5
        jnp loc_004267E6
        mov  eax,0x2
        add  esp,0x10
        ret
    loc_004267E6:
        xor  eax,eax
        add  esp,0x10
        ret
    }
}
