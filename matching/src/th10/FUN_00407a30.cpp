// 00407A30: FUN_00407a30
// Original size: 432 bytes, actual code: 110 instructions
extern "C" void FUN_00408750(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_0044bc10(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00407a30(void) {
    __asm {
        push  ecx
        mov  eax,DWORD PTR [esi+0x6d8]
        cmp  DWORD PTR [esi+0x6b4],eax
        mov  DWORD PTR [esp],eax
        jl loc_00407B4B
        push  ebx
        push  edi
        mov  edi,DWORD PTR [esi+0x458]
        xor  ebx,ebx
        cmp  edi,ebx
        jl loc_00407A5F
        push  ebx
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_00407A5F:
        mov  edx,DWORD PTR [esi+0x6e0]
        mov  ecx,DWORD PTR [esi+0x6dc]
        inc  edx
        mov  eax,edx
        cmp  eax,ecx
        mov  DWORD PTR [esi+0x6e0],edx
        jl loc_00407A82
        and  DWORD PTR [esi+0x43c],0xffffff7f
    loc_00407A82:
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
        jp loc_00407ACF
        fld  DWORD PTR ds:0x470b04
        fld  st(2)
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_00407ACF
        fstp  st(0)
        mov  DWORD PTR [esp+0x8],0x3fc90fdb
        fstp  st(0)
        jmp loc_00407AD7
    loc_00407ACF:
        fxch  st(1)
        fpatan
        fstp  DWORD PTR [esp+0x8]
    loc_00407AD7:
        mov  eax,DWORD PTR [esi+0x6c8]
        mov  ecx,DWORD PTR [esp+0x8]
        push  eax
        push  ecx
        call FUN_0044bc10
        fstp  DWORD PTR [esi+0x3e4]
        fld  DWORD PTR [esi+0x6c4]
        fst  DWORD PTR [esi+0x3d8]
        mov  eax,DWORD PTR [esi+0x6c0]
        test  al,0x1
        fstp  DWORD PTR [esp+0x8]
        jne loc_00407B31
        or   eax,0x1
        mov  DWORD PTR [esi+0x6b4],ebx
        mov  DWORD PTR [esi+0x6b0],0xfff0bdc1
        mov  DWORD PTR [esi+0x6b8],ebx
        mov  DWORD PTR [esi+0x6bc],0x476f78
        mov  DWORD PTR [esi+0x6c0],eax
    loc_00407B31:
        pop  edi
        mov  DWORD PTR [esi+0x6b4],ebx
        mov  DWORD PTR [esi+0x6b8],ebx
        mov  DWORD PTR [esi+0x6b0],0xffffffff
        pop  ebx
        jmp loc_00407B63
    loc_00407B4B:
        fld  DWORD PTR [esi+0x3d8]
        fld  st(0)
        fmul  DWORD PTR [esi+0x6b8]
        fidiv DWORD PTR [esp]
        fsubr st,st(1)
        fstp  DWORD PTR [esp]
        fstp  st(0)
    loc_00407B63:
        mov  edx,DWORD PTR [esp]
        mov  eax,DWORD PTR [esi+0x3e4]
        push  edx
        push  eax
        lea  ecx,[esi+0x3c0]
        call FUN_00408750
        mov  edx,DWORD PTR [esi+0x6b4]
        mov  ecx,DWORD PTR [esi+0x6bc]
        mov  DWORD PTR [esi+0x6b0],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00407BC4
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00407BC4
        fld  DWORD PTR [esi+0x6b8]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x6b4],edx
        fstp  DWORD PTR [esi+0x6b8]
        pop  ecx
        ret
    loc_00407BC4:
        fld  DWORD PTR [esi+0x6b8]
        fadd  DWORD PTR [ecx]
        fst  DWORD PTR [esi+0x6b8]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x6b4],eax
        pop  ecx
        ret
    }
}
