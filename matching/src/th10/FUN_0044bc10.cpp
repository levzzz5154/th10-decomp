// 0044BC10: FUN_0044bc10
// Original size: 96 bytes, actual code: 31 instructions

extern "C" __declspec(naked) void FUN_0044bc10(void) {
    __asm {
        fld  DWORD PTR [esp+0x4]
        xor  ecx,ecx
        fadd  DWORD PTR [esp+0x8]
        fcom  DWORD PTR ds:0x470b18
        fnstsw ax
        test  ah,0x41
        jne loc_0044BC42
    loc_0044BC27:
        fsub  DWORD PTR ds:0x470b14
        mov  eax,ecx
        inc  ecx
        cmp  eax,0x20
        jg loc_0044BC42
        fcom  DWORD PTR ds:0x470b18
        fnstsw ax
        test  ah,0x41
        je loc_0044BC27
    loc_0044BC42:
        fcom  DWORD PTR ds:0x470b10
        fnstsw ax
        test  ah,0x5
        jp loc_0044BC6B
        nop
    loc_0044BC50:
        fadd  DWORD PTR ds:0x470b14
        mov  edx,ecx
        inc  ecx
        cmp  edx,0x20
        jg loc_0044BC6B
        fcom  DWORD PTR ds:0x470b10
        fnstsw ax
        test  ah,0x5
        jnp loc_0044BC50
    loc_0044BC6B:
        ret  0x8
    }
}
