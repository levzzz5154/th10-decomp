// 004074B0: FUN_004074b0
// Original size: 176 bytes, actual code: 39 instructions
extern "C" void FUN_00408750(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_004074b0(void) {
    __asm {
        cmp  DWORD PTR [esi+0x618],0x10
        jg loc_004074E9
        fld  DWORD PTR [esi+0x61c]
        mov  eax,DWORD PTR [esi+0x3e4]
        fmul  DWORD PTR ds:0x470c6c
        push  ecx
        lea  ecx,[esi+0x3c0]
        fsubr DWORD PTR ds:0x470c68
        fadd  DWORD PTR [esi+0x3d8]
        fstp  DWORD PTR [esp]
        push  eax
        call FUN_00408750
        jmp loc_004074F0
    loc_004074E9:
        xor  DWORD PTR [esi+0x43c],0x1
    loc_004074F0:
        mov  edx,DWORD PTR [esi+0x618]
        mov  ecx,DWORD PTR [esi+0x620]
        mov  DWORD PTR [esi+0x614],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_0040753A
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0040753A
        fld  DWORD PTR [esi+0x61c]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x618],edx
        fstp  DWORD PTR [esi+0x61c]
        ret
    loc_0040753A:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [esi+0x61c]
        fst  DWORD PTR [esi+0x61c]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x618],eax
        ret
    }
}
