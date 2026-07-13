// 00407BE0: FUN_00407be0
// Original size: 448 bytes, actual code: 112 instructions
extern "C" void FUN_00408750(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_0044bc10(void);

extern "C" __declspec(naked) void FUN_00407be0(void) {
    __asm {
        fld  DWORD PTR [esi+0x3b4]
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x41
        jnp loc_00407C30
        fld  DWORD PTR [esi+0x3b4]
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        test  ah,0x1
        je loc_00407C30
        fld  DWORD PTR [esi+0x3b8]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x41
        jnp loc_00407C30
        fld  DWORD PTR [esi+0x3b8]
        fcomp DWORD PTR ds:0x470b38
        fnstsw ax
        test  ah,0x1
        jne loc_00407D9D
    loc_00407C30:
        push  ebx
        push  edi
        mov  edi,DWORD PTR [esi+0x458]
        xor  ebx,ebx
        test  edi,edi
        jl loc_00407C49
        push  ebx
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_00407C49:
        fld  DWORD PTR [esi+0x3b4]
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x5
        jnp loc_00407C6F
        fld  DWORD PTR [esi+0x3b4]
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        test  ah,0x1
        jne loc_00407CC0
    loc_00407C6F:
        fld  DWORD PTR [esi+0x3e4]
        push  0x0
        fchs
        push  ecx
        fsub  DWORD PTR ds:0x470b18
        fstp  DWORD PTR [esp]
        call FUN_0044bc10
        fstp  DWORD PTR [esi+0x3e4]
        mov  ebx,0x1
        fld  DWORD PTR [esi+0x3b4]
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x5
        jp loc_00407CAE
        fld  DWORD PTR ds:0x470b58
        jmp loc_00407CB4
    loc_00407CAE:
        fld  DWORD PTR ds:0x470b54
    loc_00407CB4:
        fsub  DWORD PTR [esi+0x3b4]
        fstp  DWORD PTR [esi+0x3b4]
    loc_00407CC0:
        mov  ecx,DWORD PTR [esi+0x43c]
        test  ecx,0x8000000
        jne loc_00407D41
        fld  DWORD PTR [esi+0x3b8]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jnp loc_00407CF9
        fld  DWORD PTR [esi+0x3b8]
        fcomp DWORD PTR ds:0x470b38
        fnstsw ax
        test  ah,0x1
        jne loc_00407D41
        test  ch,0x4
        je loc_00407D41
    loc_00407CF9:
        fld  DWORD PTR [esi+0x3e4]
        mov  ebx,0x1
        fchs
        fstp  DWORD PTR [esi+0x3e4]
        fld  DWORD PTR [esi+0x3b8]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jp loc_00407D29
        fld  DWORD PTR [esi+0x3b8]
        fchs
        jmp loc_00407D3B
    loc_00407D29:
        fld  DWORD PTR ds:0x470b38
        fsub  DWORD PTR [esi+0x3b8]
        fadd  DWORD PTR ds:0x470b38
    loc_00407D3B:
        fstp  DWORD PTR [esi+0x3b8]
    loc_00407D41:
        fld  DWORD PTR [esi+0x6f8]
        fcomp DWORD PTR ds:0x470b50
        fnstsw ax
        test  ah,0x41
        jne loc_00407D60
        mov  eax,DWORD PTR [esi+0x6f8]
        mov  DWORD PTR [esi+0x3d8],eax
    loc_00407D60:
        mov  ecx,DWORD PTR [esi+0x3d8]
        mov  edx,DWORD PTR [esi+0x3e4]
        push  ecx
        push  edx
        lea  ecx,[esi+0x3c0]
        call FUN_00408750
        pop  edi
        test  ebx,ebx
        pop  ebx
        je loc_00407D85
        inc  DWORD PTR [esi+0x70c]
    loc_00407D85:
        mov  eax,DWORD PTR [esi+0x70c]
        cmp  eax,DWORD PTR [esi+0x710]
        jl loc_00407D9D
        and  DWORD PTR [esi+0x43c],0xf7fff3ff
    loc_00407D9D:
        ret
    }
}
