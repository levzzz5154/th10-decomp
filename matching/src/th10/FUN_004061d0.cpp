// 004061D0: FUN_004061d0
// Original size: 112 bytes, actual code: 35 instructions

extern "C" __declspec(naked) void FUN_004061d0(void) {
    __asm {
        fld  DWORD PTR [esp+0x4]
        fmul  DWORD PTR ds:0x470b0c
        fld  st(0)
        fadd  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x41
        jnp loc_00406233
        fld  DWORD PTR [ecx]
        fsub  st,st(1)
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        fstp  st(0)
        test  ah,0x1
        je loc_00406235
        fld  DWORD PTR [esp+0x8]
        fmul  DWORD PTR ds:0x470b0c
        fld  st(0)
        fadd  DWORD PTR [ecx+0x4]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x41
        jnp loc_00406233
        fld  DWORD PTR [ecx+0x4]
        fsub  st,st(1)
        fcomp DWORD PTR ds:0x470b38
        fnstsw ax
        fstp  st(0)
        test  ah,0x1
        je loc_00406235
        xor  eax,eax
        ret  0x8
    loc_00406233:
        fstp  st(0)
    loc_00406235:
        mov  eax,0x1
        ret  0x8
    }
}
