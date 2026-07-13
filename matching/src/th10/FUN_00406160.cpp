// 00406160: FUN_00406160
// Original size: 112 bytes, actual code: 35 instructions

extern "C" __declspec(naked) void FUN_00406160(void) {
    __asm {
        fld  DWORD PTR [esp+0x4]
        fmul  DWORD PTR ds:0x470b0c
        fld  st(0)
        fadd  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x41
        jnp loc_004061C3
        fld  DWORD PTR [ecx]
        fsub  st,st(1)
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        fstp  st(0)
        test  ah,0x1
        je loc_004061C5
        fld  DWORD PTR [esp+0x8]
        fmul  DWORD PTR ds:0x470b0c
        fld  st(0)
        fadd  DWORD PTR [ecx+0x4]
        fcomp DWORD PTR ds:0x470b5c
        fnstsw ax
        test  ah,0x41
        jnp loc_004061C3
        fld  DWORD PTR [ecx+0x4]
        fsub  st,st(1)
        fcomp DWORD PTR ds:0x470b38
        fnstsw ax
        fstp  st(0)
        test  ah,0x1
        je loc_004061C5
        xor  eax,eax
        ret  0x8
    loc_004061C3:
        fstp  st(0)
    loc_004061C5:
        mov  eax,0x1
        ret  0x8
    }
}
