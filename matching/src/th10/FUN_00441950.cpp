// 00441950: FUN_00441950
// Original size: 384 bytes, actual code: 127 instructions
extern "C" void FUN_0044c350(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00441950(void) {
    __asm {
        sub  esp,0x8
        mov  eax,DWORD PTR [esi+0x24]
        test  eax,eax
        mov  DWORD PTR [esp],eax
        jle loc_00441A04
        mov  edx,DWORD PTR [esi+0x14]
        mov  ecx,DWORD PTR [esi+0x1c]
        mov  DWORD PTR [esi+0x10],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_0044199A
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0044199A
        fld  DWORD PTR [esi+0x18]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x14],edx
        fstp  DWORD PTR [esi+0x18]
        jmp loc_004419AA
    loc_0044199A:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [esi+0x18]
        fst  DWORD PTR [esi+0x18]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x14],eax
    loc_004419AA:
        mov  ecx,DWORD PTR [esi+0x24]
        cmp  DWORD PTR [esi+0x14],ecx
        mov  DWORD PTR [esp],ecx
        jl loc_00441A04
        mov  eax,DWORD PTR [esi+0x20]
        test  al,0x1
        mov  DWORD PTR [esp],ecx
        jne loc_004419E1
        or   eax,0x1
        mov  DWORD PTR [esi+0x14],0x0
        mov  DWORD PTR [esi+0x10],0xfff0bdc1
        mov  DWORD PTR [esi+0x18],0x0
        mov  DWORD PTR [esi+0x1c],0x476f78
        mov  DWORD PTR [esi+0x20],eax
    loc_004419E1:
        fild  DWORD PTR [esp]
        mov  DWORD PTR [esi+0x14],ecx
        dec  ecx
        mov  DWORD PTR [esi+0x10],ecx
        fstp  DWORD PTR [esi+0x18]
        mov  eax,DWORD PTR [esi+0x28]
        cmp  eax,0x7
        mov  DWORD PTR [esi+0x24],0x0
        je loc_00441A15
        mov  eax,DWORD PTR [esi+0x4]
        add  esp,0x8
        ret
    loc_00441A04:
        mov  eax,DWORD PTR [esi+0x28]
        cmp  eax,0x7
        jne loc_00441A1B
        mov  ecx,DWORD PTR [esi]
        mov  eax,DWORD PTR [esi+0x4]
        add  ecx,eax
        mov  DWORD PTR [esi],ecx
    loc_00441A15:
        mov  eax,DWORD PTR [esi]
        add  esp,0x8
        ret
    loc_00441A1B:
        cmp  eax,0x11
        jne loc_00441A33
        mov  eax,DWORD PTR [esi+0xc]
        add  DWORD PTR [esi],eax
        mov  ecx,DWORD PTR [esi+0x4]
        add  ecx,eax
        mov  eax,DWORD PTR [esi]
        mov  DWORD PTR [esi+0xc],ecx
        add  esp,0x8
        ret
    loc_00441A33:
        cmp  eax,0x8
        fild  DWORD PTR [esp]
        jne loc_00441A98
        fdivr DWORD PTR [esi+0x18]
        fld  st(0)
        fadd  st,st(1)
        fld  st(1)
        fsub  DWORD PTR ds:0x470afc
        fld  DWORD PTR ds:0x470afc
        fsub  st,st(3)
        fld  DWORD PTR ds:0x470bd4
        fsub  st,st(3)
        fmul  st,st(4)
        fmul  st,st(4)
        fimul DWORD PTR [esi+0x4]
        fld  st(2)
        fmul  st,st(5)
        fmul  st,st(5)
        fimul DWORD PTR [esi+0xc]
        faddp st(1),st
        fld  st(1)
        fmul  st,st(2)
        fmul  st,st(5)
        fimul DWORD PTR [esi+0x8]
        faddp st(1),st
        fxch  st(3)
        fadd  DWORD PTR ds:0x470afc
        fmul  st,st(2)
        fmul  st,st(2)
        fimul DWORD PTR [esi]
        faddp st(3),st
        fxch  st(2)
        call FUN_00463b2c
        fstp  st(1)
        fstp  st(0)
        fstp  st(0)
        add  esp,0x8
        ret
    loc_00441A98:
        mov  ecx,DWORD PTR [esi]
        mov  edx,DWORD PTR [esi+0x18]
        push  ecx
        fstp  DWORD PTR [esp]
        push  edx
        mov  DWORD PTR [esp+0xc],ecx
        call FUN_0044c350
        mov  eax,DWORD PTR [esi+0x4]
        sub  eax,ecx
        mov  DWORD PTR [esp],eax
        fimul DWORD PTR [esp]
        fiadd DWORD PTR [esp+0x4]
        add  esp,0x8
        jmp FUN_00463b2c
    }
}
