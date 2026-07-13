// 004078E0: FUN_004078e0
// Original size: 336 bytes, actual code: 82 instructions
extern "C" void FUN_00408750(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_004078e0(void) {
    __asm {
        push  ecx
        mov  eax,DWORD PTR [esi+0x6d8]
        cmp  DWORD PTR [esi+0x6b4],eax
        mov  DWORD PTR [esp],eax
        jl loc_0040799B
        push  ebx
        push  edi
        mov  edi,DWORD PTR [esi+0x458]
        xor  ebx,ebx
        cmp  edi,ebx
        jl loc_0040790F
        push  ebx
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_0040790F:
        mov  edx,DWORD PTR [esi+0x6e0]
        mov  ecx,DWORD PTR [esi+0x6dc]
        inc  edx
        mov  eax,edx
        cmp  eax,ecx
        mov  DWORD PTR [esi+0x6e0],edx
        jl loc_00407932
        and  DWORD PTR [esi+0x43c],0xfffffeff
    loc_00407932:
        mov  eax,DWORD PTR [esi+0x6c8]
        fld  DWORD PTR [esi+0x6c4]
        fst  DWORD PTR [esi+0x3d8]
        mov  DWORD PTR [esi+0x3e4],eax
        mov  eax,DWORD PTR [esi+0x6c0]
        fstp  DWORD PTR [esp+0x8]
        test  al,0x1
        jne loc_00407981
        or   eax,0x1
        mov  DWORD PTR [esi+0x6b4],ebx
        mov  DWORD PTR [esi+0x6b0],0xfff0bdc1
        mov  DWORD PTR [esi+0x6b8],ebx
        mov  DWORD PTR [esi+0x6bc],0x476f78
        mov  DWORD PTR [esi+0x6c0],eax
    loc_00407981:
        pop  edi
        mov  DWORD PTR [esi+0x6b4],ebx
        mov  DWORD PTR [esi+0x6b8],ebx
        mov  DWORD PTR [esi+0x6b0],0xffffffff
        pop  ebx
        jmp loc_004079B3
    loc_0040799B:
        fld  DWORD PTR [esi+0x3d8]
        fld  st(0)
        fmul  DWORD PTR [esi+0x6b8]
        fidiv DWORD PTR [esp]
        fsubr st,st(1)
        fstp  DWORD PTR [esp]
        fstp  st(0)
    loc_004079B3:
        mov  ecx,DWORD PTR [esp]
        mov  edx,DWORD PTR [esi+0x3e4]
        push  ecx
        push  edx
        lea  ecx,[esi+0x3c0]
        call FUN_00408750
        mov  edx,DWORD PTR [esi+0x6b4]
        mov  ecx,DWORD PTR [esi+0x6bc]
        mov  DWORD PTR [esi+0x6b0],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00407A14
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00407A14
        fld  DWORD PTR [esi+0x6b8]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x6b4],edx
        fstp  DWORD PTR [esi+0x6b8]
        pop  ecx
        ret
    loc_00407A14:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [esi+0x6b8]
        fst  DWORD PTR [esi+0x6b8]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x6b4],eax
        pop  ecx
        ret
    }
}
