// 00428D70: FUN_00428d70
// Original size: 96 bytes, actual code: 28 instructions

extern "C" __declspec(naked) void FUN_00428d70(void) {
    __asm {
        fld  DWORD PTR [esp+0x4]
        fadd  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x41
        jnp loc_00428DC3
        fld  DWORD PTR [ecx]
        fsub  DWORD PTR [esp+0x4]
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        test  ah,0x1
        je loc_00428DC3
        fld  DWORD PTR [esp+0x8]
        fadd  DWORD PTR [ecx+0x4]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x41
        jnp loc_00428DC3
        fld  DWORD PTR [ecx+0x4]
        fsub  DWORD PTR [esp+0x8]
        fcomp DWORD PTR ds:0x470b38
        fnstsw ax
        test  ah,0x1
        je loc_00428DC3
        xor  eax,eax
        ret  0x8
    loc_00428DC3:
        mov  eax,0x1
        ret  0x8
    }
}
