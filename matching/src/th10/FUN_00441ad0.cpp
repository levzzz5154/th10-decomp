// 00441AD0: FUN_00441ad0
// Original size: 896 bytes, actual code: 211 instructions
extern "C" void FUN_0044c350(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00441ad0(void) {
    __asm {
        sub  esp,0x20
        mov  eax,DWORD PTR [esi+0x34]
        test  eax,eax
        mov  DWORD PTR [esp],eax
        jle loc_00441BA0
        mov  edx,DWORD PTR [esi+0x24]
        mov  ecx,DWORD PTR [esi+0x2c]
        mov  DWORD PTR [esi+0x20],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00441B1A
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00441B1A
        fld  DWORD PTR [esi+0x28]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x24],edx
        fstp  DWORD PTR [esi+0x28]
        jmp loc_00441B2A
    loc_00441B1A:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [esi+0x28]
        fst  DWORD PTR [esi+0x28]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x24],eax
    loc_00441B2A:
        mov  ecx,DWORD PTR [esi+0x34]
        cmp  DWORD PTR [esi+0x24],ecx
        mov  DWORD PTR [esp],ecx
        jl loc_00441BA0
        mov  eax,DWORD PTR [esi+0x30]
        test  al,0x1
        mov  DWORD PTR [esp+0x8],ecx
        jne loc_00441B62
        or   eax,0x1
        mov  DWORD PTR [esi+0x24],0x0
        mov  DWORD PTR [esi+0x20],0xfff0bdc1
        mov  DWORD PTR [esi+0x28],0x0
        mov  DWORD PTR [esi+0x2c],0x476f78
        mov  DWORD PTR [esi+0x30],eax
    loc_00441B62:
        fild  DWORD PTR [esp+0x8]
        mov  DWORD PTR [esi+0x24],ecx
        dec  ecx
        mov  DWORD PTR [esi+0x20],ecx
        fstp  DWORD PTR [esi+0x28]
        mov  eax,DWORD PTR [esi+0x38]
        cmp  eax,0x7
        mov  DWORD PTR [esi+0x34],0x0
        je loc_00441B90
        mov  eax,DWORD PTR [esi+0x8]
        mov  DWORD PTR [edi],eax
        mov  ecx,DWORD PTR [esi+0xc]
        mov  DWORD PTR [edi+0x4],ecx
        mov  eax,edi
        add  esp,0x20
        ret
    loc_00441B90:
        mov  edx,DWORD PTR [esi]
        mov  DWORD PTR [edi],edx
        mov  eax,DWORD PTR [esi+0x4]
        mov  DWORD PTR [edi+0x4],eax
        mov  eax,edi
        add  esp,0x20
        ret
    loc_00441BA0:
        mov  eax,DWORD PTR [esi+0x38]
        cmp  eax,0x7
        jne loc_00441BE1
        mov  ecx,DWORD PTR [esi]
        mov  edx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [esp+0x8],ecx
        fld  DWORD PTR [esp+0x8]
        fadd  DWORD PTR [esi+0x8]
        mov  DWORD PTR [esp+0xc],edx
        fstp  DWORD PTR [esp]
        mov  eax,DWORD PTR [esp]
        fld  DWORD PTR [esp+0xc]
        fadd  DWORD PTR [esi+0xc]
        mov  DWORD PTR [esi],eax
        fstp  DWORD PTR [esp+0x4]
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR [esi+0x4],ecx
        mov  DWORD PTR [edi],eax
        mov  DWORD PTR [edi+0x4],ecx
        mov  eax,edi
        add  esp,0x20
        ret
    loc_00441BE1:
        cmp  eax,0x11
        jne loc_00441C41
        mov  eax,DWORD PTR [esi]
        mov  ecx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [esp+0x8],eax
        fld  DWORD PTR [esp+0x8]
        fadd  DWORD PTR [esi+0x18]
        mov  DWORD PTR [esp+0xc],ecx
        fstp  DWORD PTR [esp]
        mov  eax,DWORD PTR [esp]
        fld  DWORD PTR [esp+0xc]
        fadd  DWORD PTR [esi+0x1c]
        mov  DWORD PTR [esi],eax
        fstp  DWORD PTR [esp+0x4]
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR [esi+0x4],ecx
        fld  DWORD PTR [esi+0x18]
        fadd  DWORD PTR [esi+0x8]
        fstp  DWORD PTR [esp+0x8]
        mov  edx,DWORD PTR [esp+0x8]
        fld  DWORD PTR [esi+0xc]
        fadd  DWORD PTR [esi+0x1c]
        mov  DWORD PTR [esi+0x18],edx
        fstp  DWORD PTR [esp+0xc]
        mov  edx,DWORD PTR [esp+0xc]
        mov  DWORD PTR [esi+0x1c],edx
        mov  DWORD PTR [edi],eax
        mov  DWORD PTR [edi+0x4],ecx
        mov  eax,edi
        add  esp,0x20
        ret
    loc_00441C41:
        cmp  eax,0x8
        fild  DWORD PTR [esp]
        jne loc_00441D0E
        fdivr DWORD PTR [esi+0x28]
        fld  st(0)
        fadd  st,st(1)
        fld  st(1)
        fsub  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [esp]
        fld  DWORD PTR ds:0x470afc
        fadd  st,st(1)
        fmul  DWORD PTR [esp]
        fmul  DWORD PTR [esp]
        fstp  DWORD PTR [esp+0x8]
        fsubr DWORD PTR ds:0x470bd4
        fmul  st,st(1)
        fmul  st,st(1)
        fld  DWORD PTR ds:0x470afc
        fsub  st,st(2)
        fld  st(0)
        fmulp st(1),st
        fmul  st,st(2)
        fld  DWORD PTR [esp]
        fmul  st,st(3)
        fmul  st,st(3)
        fld  st(0)
        fmul  DWORD PTR [esi+0x18]
        fstp  DWORD PTR [esp+0x10]
        fmul  DWORD PTR [esi+0x1c]
        fstp  DWORD PTR [esp+0x14]
        fld  st(0)
        fmul  DWORD PTR [esi+0x10]
        fstp  DWORD PTR [esp]
        fmul  DWORD PTR [esi+0x14]
        fstp  DWORD PTR [esp+0x4]
        fld  st(0)
        fmul  DWORD PTR [esi+0x8]
        fstp  DWORD PTR [esp+0x18]
        fmul  DWORD PTR [esi+0xc]
        fstp  st(1)
        fld  DWORD PTR [esp+0x8]
        fmul  DWORD PTR [esi]
        fld  DWORD PTR [esp+0x8]
        fmul  DWORD PTR [esi+0x4]
        fstp  DWORD PTR [esp+0xc]
        fadd  DWORD PTR [esp+0x18]
        fld  DWORD PTR [esp+0xc]
        fadd  st,st(2)
        fstp  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [esp]
        fstp  st(1)
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [esp+0x4]
        fxch  st(1)
        fadd  DWORD PTR [esp+0x10]
        fstp  DWORD PTR [esp+0x8]
        mov  eax,DWORD PTR [esp+0x8]
        mov  DWORD PTR [edi],eax
        fadd  DWORD PTR [esp+0x14]
        mov  eax,edi
        fstp  DWORD PTR [esp+0xc]
        mov  ecx,DWORD PTR [esp+0xc]
        mov  DWORD PTR [edi+0x4],ecx
        add  esp,0x20
        ret
    loc_00441D0E:
        mov  edx,DWORD PTR [esi+0x28]
        push  ecx
        fstp  DWORD PTR [esp]
        push  edx
        call FUN_0044c350
        fld  DWORD PTR [esi+0x8]
        fsub  DWORD PTR [esi]
        fld  DWORD PTR [esi+0xc]
        fsub  DWORD PTR [esi+0x4]
        fstp  DWORD PTR [esp+0x1c]
        fmul  st,st(1)
        fld  DWORD PTR [esp+0x1c]
        fmul  st,st(2)
        fstp  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [esi]
        fstp  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [esp+0x10]
        fstp  st(0)
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [esi+0x4]
        mov  DWORD PTR [edi],eax
        mov  eax,edi
        fstp  DWORD PTR [esp+0x14]
        mov  ecx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [edi+0x4],ecx
        add  esp,0x20
        ret
    }
}
