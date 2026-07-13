// 00404ED0: FUN_00404ed0
// Original size: 96 bytes, actual code: 25 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00404ed0(void) {
    __asm {
        mov  edx,DWORD PTR [esi+0x4]
        mov  ecx,DWORD PTR [esi+0xc]
        mov  DWORD PTR [esi],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00404F07
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00404F07
        fld  DWORD PTR [esi+0x8]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x4],edx
        fstp  DWORD PTR [esi+0x8]
        ret
    loc_00404F07:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [esi+0x8]
        fst  DWORD PTR [esi+0x8]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x4],eax
        ret
    }
}
