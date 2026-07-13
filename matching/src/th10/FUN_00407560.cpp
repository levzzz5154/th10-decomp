// 00407560: FUN_00407560
// Original size: 320 bytes, actual code: 69 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00407560(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x64c]
        mov  ecx,DWORD PTR [esi+0x670]
        sub  esp,0xc
        cmp  eax,ecx
        jl loc_0040757F
        and  DWORD PTR [esi+0x43c],0xffffffef
        jmp loc_00407627
    loc_0040757F:
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [esi+0x65c]
        fadd  DWORD PTR [esi+0x3d8]
        fstp  DWORD PTR [esi+0x3d8]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [esi+0x664]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [esi+0x668]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [esi+0x66c]
        fstp  DWORD PTR [esp+0x8]
        fxch  st(1)
        fadd  DWORD PTR [esi+0x3c0]
        fstp  DWORD PTR [esi+0x3c0]
        fadd  DWORD PTR [esi+0x3c4]
        fstp  DWORD PTR [esi+0x3c4]
        fld  DWORD PTR [esp+0x8]
        fadd  DWORD PTR [esi+0x3c8]
        fstp  DWORD PTR [esi+0x3c8]
        fld  DWORD PTR [esi+0x3c0]
        fabs
        fcomp DWORD PTR ds:0x470c58
        fnstsw ax
        test  ah,0x41
        je loc_00407613
        fld  DWORD PTR [esi+0x3c4]
        fabs
        fcomp DWORD PTR ds:0x470c58
        fnstsw ax
        test  ah,0x41
        jne loc_00407627
    loc_00407613:
        fld  DWORD PTR [esi+0x3c4]
        fld  DWORD PTR [esi+0x3c0]
        fpatan
        fstp  DWORD PTR [esi+0x3e4]
    loc_00407627:
        mov  edx,DWORD PTR [esi+0x64c]
        mov  ecx,DWORD PTR [esi+0x654]
        mov  DWORD PTR [esi+0x648],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00407674
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00407674
        fld  DWORD PTR [esi+0x650]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x64c],edx
        fstp  DWORD PTR [esi+0x650]
        add  esp,0xc
        ret
    loc_00407674:
        fld  DWORD PTR [esi+0x650]
        fadd  DWORD PTR [ecx]
        fst  DWORD PTR [esi+0x650]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x64c],eax
        add  esp,0xc
        ret
    }
}
