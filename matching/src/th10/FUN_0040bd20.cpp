// 0040BD20: FUN_0040bd20
// Original size: 96 bytes, actual code: 33 instructions
extern "C" void FUN_0040bd80(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0040bd20(void) {
    __asm {
        push  esi
        call FUN_0040bd80
        test  eax,eax
        je loc_0040BD30
        mov  eax,0x1
        ret
    loc_0040BD30:
        mov  edx,DWORD PTR [esi+0x8]
        mov  ecx,DWORD PTR [esi+0x10]
        mov  DWORD PTR [esi+0x4],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_0040BD6A
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0040BD6A
        fld  DWORD PTR [esi+0xc]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x8],edx
        xor  eax,eax
        fstp  DWORD PTR [esi+0xc]
        ret
    loc_0040BD6A:
        fld  DWORD PTR [esi+0xc]
        fadd  DWORD PTR [ecx]
        fst  DWORD PTR [esi+0xc]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x8],eax
        xor  eax,eax
        ret
    }
}
