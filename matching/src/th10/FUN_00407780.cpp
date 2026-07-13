// 00407780: FUN_00407780
// Original size: 352 bytes, actual code: 83 instructions
extern "C" void FUN_00408750(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00407780(void) {
    __asm {
        push  ecx
        mov  eax,DWORD PTR [esi+0x6d8]
        cmp  DWORD PTR [esi+0x6b4],eax
        mov  DWORD PTR [esp],eax
        jl loc_0040783E
        push  ebx
        push  edi
        mov  edi,DWORD PTR [esi+0x458]
        xor  ebx,ebx
        cmp  edi,ebx
        jl loc_004077AF
        push  ebx
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_004077AF:
        mov  edx,DWORD PTR [esi+0x6e0]
        mov  ecx,DWORD PTR [esi+0x6dc]
        inc  edx
        mov  eax,edx
        cmp  eax,ecx
        mov  DWORD PTR [esi+0x6e0],edx
        jl loc_004077CF
        and  DWORD PTR [esi+0x43c],0xffffffbf
    loc_004077CF:
        fld  DWORD PTR [esi+0x6c8]
        fadd  DWORD PTR [esi+0x3e4]
        fstp  DWORD PTR [esi+0x3e4]
        fld  DWORD PTR [esi+0x6c4]
        fst  DWORD PTR [esi+0x3d8]
        mov  eax,DWORD PTR [esi+0x6c0]
        test  al,0x1
        fstp  DWORD PTR [esp+0x8]
        jne loc_00407824
        or   eax,0x1
        mov  DWORD PTR [esi+0x6b4],ebx
        mov  DWORD PTR [esi+0x6b0],0xfff0bdc1
        mov  DWORD PTR [esi+0x6b8],ebx
        mov  DWORD PTR [esi+0x6bc],0x476f78
        mov  DWORD PTR [esi+0x6c0],eax
    loc_00407824:
        pop  edi
        mov  DWORD PTR [esi+0x6b4],ebx
        mov  DWORD PTR [esi+0x6b8],ebx
        mov  DWORD PTR [esi+0x6b0],0xffffffff
        pop  ebx
        jmp loc_00407856
    loc_0040783E:
        fld  DWORD PTR [esi+0x3d8]
        fld  st(0)
        fmul  DWORD PTR [esi+0x6b8]
        fidiv DWORD PTR [esp]
        fsubr st,st(1)
        fstp  DWORD PTR [esp]
        fstp  st(0)
    loc_00407856:
        mov  eax,DWORD PTR [esp]
        mov  ecx,DWORD PTR [esi+0x3e4]
        push  eax
        push  ecx
        lea  ecx,[esi+0x3c0]
        call FUN_00408750
        mov  edx,DWORD PTR [esi+0x6b4]
        mov  ecx,DWORD PTR [esi+0x6bc]
        mov  DWORD PTR [esi+0x6b0],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_004078B7
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_004078B7
        fld  DWORD PTR [esi+0x6b8]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x6b4],edx
        fstp  DWORD PTR [esi+0x6b8]
        pop  ecx
        ret
    loc_004078B7:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [esi+0x6b8]
        fst  DWORD PTR [esi+0x6b8]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x6b4],eax
        pop  ecx
        ret
    }
}
