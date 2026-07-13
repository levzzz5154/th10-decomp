// 004049A0: FUN_004049a0
// Original size: 928 bytes, actual code: 212 instructions
extern "C" void FUN_00404d40(void);
extern "C" void FUN_00404da0(void);
extern "C" void FUN_00404e10(void);
extern "C" void FUN_0044c350(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_004049a0(void) {
    __asm {
        sub  esp,0xd4
        mov  eax,DWORD PTR [ebx+0x84]
        push  ebp
        mov  ebp,DWORD PTR [esp+0xdc]
        push  esi
        xor  esi,esi
        cmp  eax,esi
        push  edi
        mov  DWORD PTR [esp+0xc],eax
        jle loc_00404A8F
        mov  edx,DWORD PTR [ebx+0x74]
        mov  ecx,DWORD PTR [ebx+0x7c]
        mov  DWORD PTR [ebx+0x70],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_004049FD
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_004049FD
        fld  DWORD PTR [ebx+0x78]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [ebx+0x74],edx
        fstp  DWORD PTR [ebx+0x78]
        jmp loc_00404A0D
    loc_004049FD:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [ebx+0x78]
        fst  DWORD PTR [ebx+0x78]
        call FUN_00463b2c
        mov  DWORD PTR [ebx+0x74],eax
    loc_00404A0D:
        mov  ecx,DWORD PTR [ebx+0x84]
        cmp  DWORD PTR [ebx+0x74],ecx
        mov  DWORD PTR [esp+0xc],ecx
        jl loc_00404A8F
        mov  eax,DWORD PTR [ebx+0x80]
        test  al,0x1
        mov  DWORD PTR [esp+0xc],ecx
        jne loc_00404A47
        or   eax,0x1
        mov  DWORD PTR [ebx+0x74],esi
        mov  DWORD PTR [ebx+0x70],0xfff0bdc1
        mov  DWORD PTR [ebx+0x78],esi
        mov  DWORD PTR [ebx+0x7c],0x476f78
        mov  DWORD PTR [ebx+0x80],eax
    loc_00404A47:
        fild  DWORD PTR [esp+0xc]
        mov  DWORD PTR [ebx+0x74],ecx
        dec  ecx
        mov  DWORD PTR [ebx+0x70],ecx
        fstp  DWORD PTR [ebx+0x78]
        mov  eax,DWORD PTR [ebx+0x88]
        mov  ecx,0x7
        cmp  eax,ecx
        mov  DWORD PTR [ebx+0x84],esi
        mov  edi,ebp
        mov  eax,ebp
        je loc_00404A7F
        lea  esi,[ebx+0x1c]
        rep movsd
        pop  edi
        pop  esi
        pop  ebp
        add  esp,0xd4
        ret  0x4
    loc_00404A7F:
        mov  esi,ebx
        rep movsd
        pop  edi
        pop  esi
        pop  ebp
        add  esp,0xd4
        ret  0x4
    loc_00404A8F:
        mov  eax,DWORD PTR [ebx+0x88]
        cmp  eax,0x7
        jne loc_00404AC6
        mov  ecx,eax
        mov  esi,ebx
        lea  edi,[esp+0x1c]
        rep movsd
        lea  eax,[ebx+0x1c]
        lea  esi,[esp+0x38]
        lea  ecx,[esp+0x1c]
        call FUN_00404e10
        mov  ecx,0x7
        mov  esi,eax
        mov  edi,ebx
        rep movsd
        mov  esi,ebx
        jmp loc_00404C39
    loc_00404AC6:
        cmp  eax,0x11
        jne loc_00404B14
        mov  ecx,0x7
        mov  esi,ebx
        lea  edi,[esp+0x1c]
        rep movsd
        lea  eax,[ebx+0x54]
        lea  esi,[esp+0x38]
        lea  ecx,[esp+0x1c]
        call FUN_00404e10
        mov  esi,eax
        mov  ecx,0x7
        mov  edi,ebx
        rep movsd
        lea  edi,[ebx+0x54]
        lea  eax,[ebx+0x1c]
        lea  esi,[esp+0x38]
        mov  ecx,edi
        call FUN_00404e10
        mov  ecx,0x7
        mov  esi,eax
        rep movsd
        mov  esi,ebx
        jmp loc_00404C39
    loc_00404B14:
        cmp  eax,0x8
        fild  DWORD PTR [esp+0xc]
        jne loc_00404BFA
        fdivr DWORD PTR [ebx+0x78]
        lea  esi,[esp+0x38]
        fld  st(0)
        fadd  st,st(1)
        fld  st(1)
        fsub  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [esp+0xc]
        fld  DWORD PTR ds:0x470afc
        fadd  st,st(1)
        fmul  DWORD PTR [esp+0xc]
        fmul  DWORD PTR [esp+0xc]
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR ds:0x470bd4
        fsub  st,st(1)
        fmul  st,st(2)
        fmul  st,st(2)
        fstp  DWORD PTR [esp+0x14]
        fstp  st(0)
        fld  DWORD PTR ds:0x470afc
        fsub  st,st(1)
        fld  st(0)
        fmul  st,st(1)
        fmul  st,st(2)
        fstp  DWORD PTR [esp+0x18]
        fstp  st(0)
        fld  DWORD PTR [esp+0xc]
        fmul  st,st(1)
        fmul  st,st(1)
        fstp  DWORD PTR [esp+0xc]
        mov  eax,DWORD PTR [esp+0xc]
        push  eax
        fstp  st(0)
        lea  eax,[ebx+0x54]
        call FUN_00404da0
        mov  ecx,DWORD PTR [esp+0x18]
        mov  edi,eax
        push  ecx
        lea  eax,[ebx+0x38]
        lea  esi,[esp+0x20]
        call FUN_00404da0
        mov  edx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [esp+0x14],eax
        push  edx
        lea  eax,[ebx+0x1c]
        lea  esi,[esp+0xac]
        call FUN_00404da0
        mov  ecx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0x10],eax
        push  ecx
        lea  esi,[esp+0xc8]
        mov  eax,ebx
        call FUN_00404da0
        mov  ecx,eax
        mov  eax,DWORD PTR [esp+0x10]
        lea  esi,[esp+0x54]
        call FUN_00404e10
        mov  ecx,eax
        mov  eax,DWORD PTR [esp+0x14]
        lea  esi,[esp+0x8c]
        call FUN_00404e10
        mov  ecx,eax
        mov  eax,edi
        lea  esi,[esp+0x70]
        jmp loc_00404C32
    loc_00404BFA:
        mov  edx,DWORD PTR [ebx+0x78]
        push  ecx
        fstp  DWORD PTR [esp]
        push  edx
        call FUN_0044c350
        fstp  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [esp+0x10]
        push  eax
        lea  ecx,[ebx+0x1c]
        mov  eax,ebx
        lea  esi,[esp+0x74]
        call FUN_00404d40
        lea  esi,[esp+0x90]
        call FUN_00404da0
        mov  ecx,eax
        mov  eax,ebx
        lea  esi,[esp+0x54]
    loc_00404C32:
        call FUN_00404e10
        mov  esi,eax
    loc_00404C39:
        mov  edi,ebp
        mov  ecx,0x7
        rep movsd
        pop  edi
        pop  esi
        mov  eax,ebp
        pop  ebp
        add  esp,0xd4
        ret  0x4
        mov  DWORD PTR [ecx+0x88],eax
        ret
    }
}
