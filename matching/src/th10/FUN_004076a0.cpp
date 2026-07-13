// 004076A0: FUN_004076a0
// Original size: 224 bytes, actual code: 52 instructions
extern "C" void FUN_00408750(void);
extern "C" void FUN_0044bc10(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_004076a0(void) {
    __asm {
        push  ecx
        mov  eax,DWORD PTR [esi+0x680]
        cmp  eax,DWORD PTR [esi+0x6a4]
        jl loc_004076B8
        and  DWORD PTR [esi+0x43c],0xffffffdf
        jmp loc_0040770B
    loc_004076B8:
        fld  DWORD PTR ds:0x476f78
        push  ecx
        fmul  DWORD PTR [esi+0x694]
        mov  ecx,DWORD PTR [esi+0x3e4]
        fstp  DWORD PTR [esp]
        push  ecx
        call FUN_0044bc10
        fstp  DWORD PTR [esi+0x3e4]
        fld  DWORD PTR ds:0x476f78
        mov  eax,DWORD PTR [esi+0x3e4]
        fmul  DWORD PTR [esi+0x690]
        lea  ecx,[esi+0x3c0]
        fadd  DWORD PTR [esi+0x3d8]
        fst  DWORD PTR [esp]
        mov  edx,DWORD PTR [esp]
        fstp  DWORD PTR [esi+0x3d8]
        push  edx
        push  eax
        call FUN_00408750
    loc_0040770B:
        mov  edx,DWORD PTR [esi+0x680]
        mov  ecx,DWORD PTR [esi+0x688]
        mov  DWORD PTR [esi+0x67c],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00407756
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00407756
        fld  DWORD PTR [esi+0x684]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x680],edx
        fstp  DWORD PTR [esi+0x684]
        pop  ecx
        ret
    loc_00407756:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [esi+0x684]
        fst  DWORD PTR [esi+0x684]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x680],eax
        pop  ecx
        ret
    }
}
