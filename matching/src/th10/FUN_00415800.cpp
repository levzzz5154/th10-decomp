// 00415800: FUN_00415800
// Original size: 768 bytes, actual code: 173 instructions
extern "C" void FUN_0043bda0(void);
extern "C" void FUN_004451c0(void);

extern "C" __declspec(naked) void FUN_00415800(void) {
    __asm {
        sub  esp,0x10
        push  ebp
        mov  ebp,DWORD PTR [esp+0x18]
        push  esi
        push  edi
        lea  esi,[ebp+0x24c8]
        mov  edi,0xa
        jmp loc_00415820
        nop
        mov  edi,edi
    loc_00415820:
        mov  ecx,DWORD PTR ds:0x491c10
        lea  eax,[esi-0x24b8]
        call FUN_004451c0
        mov  ecx,DWORD PTR ds:0x491c10
        mov  eax,esi
        call FUN_004451c0
        add  esi,0x3ac
        dec  edi
        jne loc_00415820
        lea  esi,[ebp+0x4980]
        mov  edi,0x9
    loc_00415852:
        mov  ecx,DWORD PTR ds:0x491c10
        mov  eax,esi
        call FUN_004451c0
        add  esi,0x3ac
        dec  edi
        jne loc_00415852
        lea  esi,[ebp+0x6a8c]
        mov  edi,0x4
    loc_00415873:
        mov  ecx,DWORD PTR ds:0x491c10
        mov  eax,esi
        call FUN_004451c0
        add  esi,0x3ac
        dec  edi
        jne loc_00415873
        lea  esi,[ebp+0x8094]
        mov  edi,0x7
        jmp loc_004158A0
        nop
        nop
    loc_004158A0:
        mov  ecx,DWORD PTR ds:0x491c10
        mov  eax,esi
        call FUN_004451c0
        add  esi,0x3ac
        dec  edi
        jne loc_004158A0
        mov  eax,ds:0x474c58
        test  eax,eax
        push  ebx
        je loc_0041593C
        fild  DWORD PTR ds:0x474c58
        movzx ebx,BYTE PTR [ebp+0x8393]
        shl  ebx,0x18
        fmul  DWORD PTR ds:0x470cb8
        lea  edi,[esp+0x10]
        mov  DWORD PTR [esp+0x10],0x424c0000
        mov  DWORD PTR [esp+0x14],0x43e68000
        fadd  DWORD PTR ds:0x470d2c
        mov  DWORD PTR [esp+0x1c],0x43e78000
        fstp  DWORD PTR [esp+0x18]
        call FUN_0043bda0
        movzx ebx,BYTE PTR [ebp+0x8393]
        fld  DWORD PTR [esp+0x18]
        fsub  DWORD PTR ds:0x470afc
        shl  ebx,0x18
        or   ebx,0xffffff
        mov  DWORD PTR [esp+0x10],0x42480000
        fstp  DWORD PTR [esp+0x18]
        mov  DWORD PTR [esp+0x14],0x43e60000
        mov  DWORD PTR [esp+0x1c],0x43e70000
        call FUN_0043bda0
    loc_0041593C:
        fld  DWORD PTR [ebp+0x9e84]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x41
        jne loc_00415A3C
        fld  DWORD PTR [ebp+0x9e84]
        mov  ebx,0xff000000
        fmul  DWORD PTR ds:0x470d28
        lea  edi,[esp+0x10]
        mov  DWORD PTR [esp+0x10],0x42240000
        mov  DWORD PTR [esp+0x14],0x41b80000
        fadd  DWORD PTR ds:0x470d24
        mov  DWORD PTR [esp+0x1c],0x41c80000
        fstp  DWORD PTR [esp+0x18]
        call FUN_0043bda0
        fld  DWORD PTR [esp+0x18]
        or   ebx,0xffffffff
        fsub  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esp+0x10],0x42200000
        mov  DWORD PTR [esp+0x14],0x41b00000
        mov  DWORD PTR [esp+0x1c],0x41c00000
        fstp  DWORD PTR [esp+0x18]
        call FUN_0043bda0
        lea  esi,[ebp+0x9e94]
        mov  DWORD PTR [esp+0x24],0x4
        jmp loc_004159D0
        nop
    loc_004159D0:
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [esi]
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_00415A2E
        fld  DWORD PTR [esi]
        fcomp DWORD PTR [ebp+0x9e84]
        fnstsw ax
        test  ah,0x5
        jp loc_004159F4
        fld  DWORD PTR [esi]
        jmp loc_004159FA
    loc_004159F4:
        fld  DWORD PTR [ebp+0x9e84]
    loc_004159FA:
        fmul  DWORD PTR ds:0x470d28
        mov  ebx,DWORD PTR [esi+0x4]
        lea  edi,[esp+0x10]
        mov  DWORD PTR [esp+0x10],0x42200000
        fadd  DWORD PTR ds:0x470c64
        mov  DWORD PTR [esp+0x14],0x41b00000
        mov  DWORD PTR [esp+0x1c],0x41c00000
        fstp  DWORD PTR [esp+0x18]
        call FUN_0043bda0
    loc_00415A2E:
        mov  eax,DWORD PTR [esp+0x24]
        add  esi,0x8
        dec  eax
        mov  DWORD PTR [esp+0x24],eax
        jne loc_004159D0
    loc_00415A3C:
        mov  ecx,DWORD PTR ds:0x477704
        test  ecx,ecx
        pop  ebx
        je loc_00415AC6
        mov  eax,DWORD PTR [ecx+0x10]
        test  eax,eax
        je loc_00415A81
        mov  eax,DWORD PTR [eax+0x2480]
        mov  edx,eax
        shr  edx,0x4
        not  edx
        test  dl,0x1
        je loc_00415A81
        not  eax
        test  al,0x1
        je loc_00415A81
        mov  ecx,DWORD PTR ds:0x491c10
        lea  eax,[ebp+0x9a48]
        call FUN_004451c0
        mov  ecx,DWORD PTR ds:0x477704
    loc_00415A81:
        test  ecx,ecx
        je loc_00415AC6
        mov  eax,DWORD PTR [ebp+0x9ec0]
        test  eax,eax
        jl loc_00415AC6
        mov  eax,DWORD PTR [ecx+0x10]
        test  eax,eax
        je loc_00415AC6
        mov  eax,DWORD PTR [ebp+0x9eb8]
        test  eax,eax
        jne loc_00415AC6
        lea  esi,[ebp+0x793c]
        mov  edi,0x2
        jmp loc_00415AB0
        nop
    loc_00415AB0:
        mov  ecx,DWORD PTR ds:0x491c10
        mov  eax,esi
        call FUN_004451c0
        add  esi,0x3ac
        dec  edi
        jne loc_00415AB0
    loc_00415AC6:
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        add  esp,0x10
        ret  0x4
    }
}
