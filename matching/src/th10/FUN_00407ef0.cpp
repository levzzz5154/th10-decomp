// 00407EF0: FUN_00407ef0
// Original size: 320 bytes, actual code: 82 instructions
extern "C" void FUN_00408660(void);
extern "C" void FUN_00408750(void);
extern "C" void FUN_0044bc10(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00407ef0(void) {
    __asm {
        push  ecx
        mov  eax,DWORD PTR [esi+0x7b8]
        cmp  eax,DWORD PTR [esi+0x7dc]
        jl loc_00407F0E
        and  DWORD PTR [esi+0x43c],0xfbffffff
        jmp loc_00407FBC
    loc_00407F0E:
        mov  eax,ds:0x477834
        fld  DWORD PTR [eax+0x3c0]
        fsub  DWORD PTR [esi+0x3b4]
        fld  DWORD PTR [eax+0x3c4]
        fsub  DWORD PTR [esi+0x3b8]
        fld  DWORD PTR ds:0x470b04
        fld  st(1)
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_00407F5A
        fld  DWORD PTR ds:0x470b04
        fld  st(2)
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_00407F5A
        fstp  st(0)
        mov  DWORD PTR [esp],0x3fc90fdb
        fstp  st(0)
        jmp loc_00407F61
    loc_00407F5A:
        fxch  st(1)
        fpatan
        fstp  DWORD PTR [esp]
    loc_00407F61:
        mov  ecx,DWORD PTR [esi+0x3e4]
        mov  edx,DWORD PTR [esp]
        mov  eax,DWORD PTR [esi+0x7cc]
        push  ecx
        push  edx
        push  eax
        call FUN_0044bc10
        push  ecx
        fstp  DWORD PTR [esp]
        call FUN_00408660
        fmul  DWORD PTR [esi+0x7c8]
        push  ecx
        mov  ecx,DWORD PTR [esi+0x3e4]
        fmul  DWORD PTR ds:0x476f78
        fstp  DWORD PTR [esp]
        push  ecx
        call FUN_0044bc10
        fst  DWORD PTR [esp]
        mov  edx,DWORD PTR [esi+0x3d8]
        fstp  DWORD PTR [esi+0x3e4]
        mov  eax,DWORD PTR [esp]
        push  edx
        push  eax
        lea  ecx,[esi+0x3c0]
        call FUN_00408750
    loc_00407FBC:
        mov  edx,DWORD PTR [esi+0x7b8]
        mov  ecx,DWORD PTR [esi+0x7c0]
        mov  DWORD PTR [esi+0x7b4],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00408007
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00408007
        fld  DWORD PTR [esi+0x7bc]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x7b8],edx
        fstp  DWORD PTR [esi+0x7bc]
        pop  ecx
        ret
    loc_00408007:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [esi+0x7bc]
        fst  DWORD PTR [esi+0x7bc]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x7b8],eax
        pop  ecx
        ret
    }
}
