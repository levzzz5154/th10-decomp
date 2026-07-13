// 00442670: FUN_00442670
// Original size: 2272 bytes, actual code: 272 instructions
extern "C" void FUN_004423c0(void);
extern "C" void FUN_004425a0(void);
extern "C" void FUN_00442f50(void);
extern "C" void FUN_00442fe0(void);

extern "C" __declspec(naked) void FUN_00442670(void) {
    __asm {
        fld  DWORD PTR ds:0x4978c0
        sub  esp,0xc
        push  ebx
        push  ebp
        push  esi
        mov  esi,ecx
        fadd  DWORD PTR [esi+0x5c]
        mov  bl,BYTE PTR [esp+0x1c]
        test  bl,0x1
        push  edi
        fstp  DWORD PTR ds:0x4978c0
        mov  edi,eax
        fld  DWORD PTR ds:0x4978c4
        fadd  DWORD PTR [esi+0x60]
        fstp  DWORD PTR ds:0x4978c4
        fld  DWORD PTR ds:0x4978dc
        fadd  DWORD PTR [esi+0x5c]
        fstp  DWORD PTR ds:0x4978dc
        fld  DWORD PTR ds:0x4978e0
        fadd  DWORD PTR [esi+0x60]
        fstp  DWORD PTR ds:0x4978e0
        fld  DWORD PTR ds:0x4978f8
        fadd  DWORD PTR [esi+0x5c]
        fstp  DWORD PTR ds:0x4978f8
        fld  DWORD PTR ds:0x4978fc
        fadd  DWORD PTR [esi+0x60]
        fstp  DWORD PTR ds:0x4978fc
        fld  DWORD PTR ds:0x497914
        fadd  DWORD PTR [esi+0x5c]
        fstp  DWORD PTR ds:0x497914
        fld  DWORD PTR ds:0x497918
        fadd  DWORD PTR [esi+0x60]
        fstp  DWORD PTR ds:0x497918
        je loc_00442764
        fld  DWORD PTR ds:0x4978c0
        frndint
        fsub  DWORD PTR ds:0x4700ec
        fld  DWORD PTR ds:0x4978dc
        frndint
        fsub  DWORD PTR ds:0x4700ec
        fld  DWORD PTR ds:0x4978c4
        frndint
        fsub  DWORD PTR ds:0x4700ec
        fld  DWORD PTR ds:0x4978fc
        frndint
        fsub  DWORD PTR ds:0x4700ec
        fst  DWORD PTR ds:0x4978fc
        fstp  DWORD PTR ds:0x497918
        fst  DWORD PTR ds:0x4978c4
        fstp  DWORD PTR ds:0x4978e0
        fst  DWORD PTR ds:0x4978dc
        fstp  DWORD PTR ds:0x497914
        fst  DWORD PTR ds:0x4978c0
        fstp  DWORD PTR ds:0x4978f8
    loc_00442764:
        mov  eax,DWORD PTR [edi+0x394]
        fld  DWORD PTR [eax+0x20]
        fadd  DWORD PTR [edi+0x54]
        fst  DWORD PTR ds:0x49790c
        fstp  DWORD PTR ds:0x4978d4
        mov  ecx,DWORD PTR [edi+0x394]
        fld  DWORD PTR [ecx+0x28]
        fadd  DWORD PTR [edi+0x54]
        fst  DWORD PTR ds:0x497928
        fstp  DWORD PTR ds:0x4978f0
        mov  edx,DWORD PTR [edi+0x394]
        fld  DWORD PTR [edx+0x24]
        fadd  DWORD PTR [edi+0x58]
        fst  DWORD PTR ds:0x4978f4
        fstp  DWORD PTR ds:0x4978d8
        mov  eax,DWORD PTR [edi+0x394]
        fld  DWORD PTR [eax+0x2c]
        fadd  DWORD PTR [edi+0x58]
        fst  DWORD PTR ds:0x49792c
        fstp  DWORD PTR ds:0x497910
        fld  DWORD PTR ds:0x4978c0
        fcomp DWORD PTR ds:0x4978dc
        fnstsw ax
        test  ah,0x41
        jne loc_004427DF
        fld  DWORD PTR ds:0x4978c0
        jmp loc_004427E5
    loc_004427DF:
        fld  DWORD PTR ds:0x4978dc
    loc_004427E5:
        fld  DWORD PTR ds:0x4978f8
        fcomp st(1)
        fnstsw ax
        test  ah,0x41
        jne loc_004427FC
        fstp  st(0)
        fld  DWORD PTR ds:0x4978f8
    loc_004427FC:
        fld  DWORD PTR ds:0x497914
        fcomp st(1)
        fnstsw ax
        test  ah,0x41
        jne loc_00442813
        fstp  st(0)
        fld  DWORD PTR ds:0x497914
    loc_00442813:
        fld  DWORD PTR ds:0x4978c4
        fcomp DWORD PTR ds:0x4978e0
        fnstsw ax
        test  ah,0x41
        jne loc_00442832
        mov  ecx,DWORD PTR ds:0x4978c4
        mov  DWORD PTR [esp+0x20],ecx
        jmp loc_0044283C
    loc_00442832:
        mov  edx,DWORD PTR ds:0x4978e0
        mov  DWORD PTR [esp+0x20],edx
    loc_0044283C:
        fld  DWORD PTR ds:0x4978fc
        fcomp DWORD PTR [esp+0x20]
        fnstsw ax
        test  ah,0x41
        jne loc_00442856
        mov  eax,ds:0x4978fc
        mov  DWORD PTR [esp+0x20],eax
    loc_00442856:
        fld  DWORD PTR ds:0x497918
        fcomp DWORD PTR [esp+0x20]
        fnstsw ax
        test  ah,0x41
        jne loc_00442871
        mov  ecx,DWORD PTR ds:0x497918
        mov  DWORD PTR [esp+0x20],ecx
    loc_00442871:
        fld  DWORD PTR ds:0x4978c0
        fcomp DWORD PTR ds:0x4978dc
        fnstsw ax
        test  ah,0x5
        jp loc_00442890
        mov  edx,DWORD PTR ds:0x4978c0
        mov  DWORD PTR [esp+0x10],edx
        jmp loc_00442899
    loc_00442890:
        mov  eax,ds:0x4978dc
        mov  DWORD PTR [esp+0x10],eax
    loc_00442899:
        fld  DWORD PTR ds:0x4978f8
        fcomp DWORD PTR [esp+0x10]
        fnstsw ax
        test  ah,0x5
        jp loc_004428B4
        mov  ecx,DWORD PTR ds:0x4978f8
        mov  DWORD PTR [esp+0x10],ecx
    loc_004428B4:
        fld  DWORD PTR ds:0x497914
        fcomp DWORD PTR [esp+0x10]
        fnstsw ax
        test  ah,0x5
        jp loc_004428CF
        mov  edx,DWORD PTR ds:0x497914
        mov  DWORD PTR [esp+0x10],edx
    loc_004428CF:
        fld  DWORD PTR ds:0x4978c4
        fcomp DWORD PTR ds:0x4978e0
        fnstsw ax
        test  ah,0x5
        jp loc_004428ED
        mov  eax,ds:0x4978c4
        mov  DWORD PTR [esp+0x14],eax
        jmp loc_004428F7
    loc_004428ED:
        mov  ecx,DWORD PTR ds:0x4978e0
        mov  DWORD PTR [esp+0x14],ecx
    loc_004428F7:
        fld  DWORD PTR ds:0x4978fc
        fcomp DWORD PTR [esp+0x14]
        fnstsw ax
        test  ah,0x5
        jp loc_00442912
        mov  edx,DWORD PTR ds:0x4978fc
        mov  DWORD PTR [esp+0x14],edx
    loc_00442912:
        fld  DWORD PTR ds:0x497918
        fcomp DWORD PTR [esp+0x14]
        fnstsw ax
        test  ah,0x5
        jp loc_0044292C
        mov  eax,ds:0x497918
        mov  DWORD PTR [esp+0x14],eax
    loc_0044292C:
        mov  ecx,DWORD PTR ds:0x491fac
        mov  ebp,DWORD PTR [ecx+0xcc]
        fild  DWORD PTR [ecx+0xcc]
        test  ebp,ebp
        jge loc_00442948
        fadd  DWORD PTR ds:0x470b98
    loc_00442948:
        fxch  st(1)
        fcompp
        fnstsw ax
        test  ah,0x5
        jnp loc_00442ABB
        mov  edx,DWORD PTR [ecx+0xd0]
        fild  DWORD PTR [ecx+0xd0]
        test  edx,edx
        jge loc_0044296D
        fadd  DWORD PTR ds:0x470b98
    loc_0044296D:
        fcomp DWORD PTR [esp+0x20]
        fnstsw ax
        test  ah,0x41
        je loc_00442ABB
        mov  eax,DWORD PTR [ecx+0xd4]
        add  eax,ebp
        test  eax,eax
        mov  DWORD PTR [esp+0x20],eax
        fild  DWORD PTR [esp+0x20]
        jge loc_00442996
        fadd  DWORD PTR ds:0x470b98
    loc_00442996:
        fcomp DWORD PTR [esp+0x10]
        fnstsw ax
        test  ah,0x5
        jnp loc_00442ABB
        mov  ecx,DWORD PTR [ecx+0xd8]
        add  ecx,edx
        test  ecx,ecx
        mov  DWORD PTR [esp+0x20],ecx
        fild  DWORD PTR [esp+0x20]
        jge loc_004429BF
        fadd  DWORD PTR ds:0x470b98
    loc_004429BF:
        fcomp DWORD PTR [esp+0x14]
        fnstsw ax
        test  ah,0x5
        jnp loc_00442ABB
        mov  edx,DWORD PTR [edi+0x394]
        mov  eax,DWORD PTR [edx+0x4]
        cmp  DWORD PTR [esi+0x3ada64],eax
        je loc_00442A01
        mov  DWORD PTR [esi+0x3ada64],eax
        call FUN_00442f50
        mov  edx,DWORD PTR [esi+0x3ada64]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  edx
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x104]
    loc_00442A01:
        cmp  BYTE PTR [esi+0x3ada6a],0x1
        je loc_00442A16
        call FUN_00442f50
        mov  BYTE PTR [esi+0x3ada6a],0x1
    loc_00442A16:
        test  bl,0x2
        jne loc_00442AA8
        mov  eax,DWORD PTR [edi+0x35c]
        test  ah,ah
        jns loc_00442A31
        mov  eax,DWORD PTR [edi+0x300]
        jmp loc_00442A37
    loc_00442A31:
        mov  eax,DWORD PTR [edi+0x2fc]
    loc_00442A37:
        mov  ecx,DWORD PTR [esi+0x73245c]
        test  ecx,ecx
        mov  DWORD PTR [esp+0x20],eax
        je loc_00442A94
        mov  cl,BYTE PTR [esi+0x73245a]
        shr  eax,0x10
        call FUN_004423c0
        mov  cl,BYTE PTR [esi+0x732459]
        mov  BYTE PTR [esp+0x22],al
        mov  al,BYTE PTR [esp+0x21]
        call FUN_004423c0
        mov  cl,BYTE PTR [esi+0x732458]
        mov  BYTE PTR [esp+0x21],al
        mov  al,BYTE PTR [esp+0x20]
        call FUN_004423c0
        mov  cl,BYTE PTR [esi+0x73245b]
        mov  BYTE PTR [esp+0x20],al
        mov  al,BYTE PTR [esp+0x23]
        call FUN_004423c0
        mov  BYTE PTR [esp+0x23],al
        mov  eax,DWORD PTR [esp+0x20]
    loc_00442A94:
        mov  ds:0x4978d0,eax
        mov  ds:0x4978ec,eax
        mov  ds:0x497908,eax
        mov  ds:0x497924,eax
    loc_00442AA8:
        mov  eax,esi
        call FUN_004425a0
        mov  edx,0x4978c0
        mov  eax,esi
        call FUN_00442fe0
    loc_00442ABB:
        pop  edi
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0xc
        ret  0x4
    }
}
