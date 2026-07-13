// 0041E4D0: FUN_0041e4d0
// Original size: 560 bytes, actual code: 71 instructions

extern "C" __declspec(naked) void FUN_0041e4d0(void) {
    __asm {
        sub  esp,0x18
        mov  eax,DWORD PTR [esp+0x1c]
        fld  DWORD PTR [eax]
        fsub  DWORD PTR [ecx+0x24]
        fstp  DWORD PTR [esp+0xc]
        fld  DWORD PTR [eax+0x4]
        fsub  DWORD PTR [ecx+0x28]
        fstp  DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [esp+0x10]
        fld  DWORD PTR [eax+0x8]
        mov  eax,DWORD PTR [esp+0xc]
        fsub  DWORD PTR [ecx+0x2c]
        mov  DWORD PTR [esp],eax
        mov  DWORD PTR [esp+0x4],edx
        fstp  DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x14]
        fld  DWORD PTR [ecx+0x3c]
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
        fsub  DWORD PTR [esp+0x20]
        fld  st(1)
        fsub  DWORD PTR [esp+0x20]
        fstp  DWORD PTR [esp+0x4]
        fld  DWORD PTR [esp+0xc]
        fadd  DWORD PTR [esp+0x20]
        fstp  DWORD PTR [esp+0xc]
        fxch  st(1)
        fadd  DWORD PTR [esp+0x20]
        fstp  DWORD PTR [esp+0x10]
        fcomp DWORD PTR [ecx+0x40]
        fnstsw ax
        test  ah,0x41
        je loc_0041E5AA
        fld  DWORD PTR [ecx+0x44]
        fmul  DWORD PTR ds:0x470b0c
        fcomp DWORD PTR [esp+0x4]
        fnstsw ax
        test  ah,0x5
        jnp loc_0041E5AA
        fld  DWORD PTR [esp+0xc]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jnp loc_0041E5AA
        fld  DWORD PTR [ecx+0x44]
        fmul  DWORD PTR ds:0x470b78
        fcomp DWORD PTR [esp+0x10]
        fnstsw ax
        test  ah,0x41
        je loc_0041E5AA
        mov  eax,0x2
        add  esp,0x18
        ret  0x8
    loc_0041E5AA:
        xor  eax,eax
        add  esp,0x18
        ret  0x8
    }
}
