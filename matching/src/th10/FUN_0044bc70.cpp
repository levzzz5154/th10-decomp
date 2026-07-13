// 0044BC70: FUN_0044bc70
// Original size: 160 bytes, actual code: 49 instructions

extern "C" __declspec(naked) void FUN_0044bc70(void) {
    __asm {
        fld  DWORD PTR [esp+0x4]
        xor  ecx,ecx
        fcom  DWORD PTR ds:0x470b18
        fnstsw ax
        test  ah,0x41
        jne loc_0044BC9E
    loc_0044BC83:
        fsub  DWORD PTR ds:0x470b14
        mov  eax,ecx
        inc  ecx
        cmp  eax,0x20
        jg loc_0044BC9E
        fcom  DWORD PTR ds:0x470b18
        fnstsw ax
        test  ah,0x41
        je loc_0044BC83
    loc_0044BC9E:
        fcom  DWORD PTR ds:0x470b10
        fnstsw ax
        test  ah,0x5
        jp loc_0044BCCB
        jmp loc_0044BCB0
        nop
    loc_0044BCB0:
        fadd  DWORD PTR ds:0x470b14
        mov  edx,ecx
        inc  ecx
        cmp  edx,0x20
        jg loc_0044BCCB
        fcom  DWORD PTR ds:0x470b10
        fnstsw ax
        test  ah,0x5
        jnp loc_0044BCB0
    loc_0044BCCB:
        ret  0x4
    }
}
