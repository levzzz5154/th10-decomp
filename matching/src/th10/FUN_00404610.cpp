// 00404610: FUN_00404610
// Original size: 912 bytes, actual code: 295 instructions
extern "C" void FUN_0044c350(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00404610(void) {
    __asm {
        sub  esp,0x44
        push  ebx
        push  esi
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x44]
        xor  ebx,ebx
        cmp  eax,ebx
        mov  DWORD PTR [esp+0xc],eax
        jle loc_004046F0
        mov  edx,DWORD PTR [esi+0x34]
        mov  ecx,DWORD PTR [esi+0x3c]
        mov  DWORD PTR [esi+0x30],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00404661
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00404661
        fld  DWORD PTR [esi+0x38]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x34],edx
        fstp  DWORD PTR [esi+0x38]
        jmp loc_00404671
    loc_00404661:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [esi+0x38]
        fst  DWORD PTR [esi+0x38]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x34],eax
    loc_00404671:
        mov  ecx,DWORD PTR [esi+0x44]
        cmp  DWORD PTR [esi+0x34],ecx
        mov  DWORD PTR [esp+0xc],ecx
        jl loc_004046F0
        mov  eax,DWORD PTR [esi+0x40]
        test  al,0x1
        mov  DWORD PTR [esp+0xc],ecx
        jne loc_004046A2
        or   eax,0x1
        mov  DWORD PTR [esi+0x34],ebx
        mov  DWORD PTR [esi+0x30],0xfff0bdc1
        mov  DWORD PTR [esi+0x38],ebx
        mov  DWORD PTR [esi+0x3c],0x476f78
        mov  DWORD PTR [esi+0x40],eax
    loc_004046A2:
        fild  DWORD PTR [esp+0xc]
        mov  DWORD PTR [esi+0x34],ecx
        dec  ecx
        mov  DWORD PTR [esi+0x30],ecx
        fstp  DWORD PTR [esi+0x38]
        mov  eax,DWORD PTR [esi+0x48]
        cmp  eax,0x7
        mov  DWORD PTR [esi+0x44],ebx
        je loc_004046D6
        add  esi,0xc
        mov  ecx,DWORD PTR [esi]
        mov  eax,edi
        mov  DWORD PTR [eax],ecx
        mov  edx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [eax+0x4],edx
        mov  ecx,DWORD PTR [esi+0x8]
        pop  esi
        mov  DWORD PTR [eax+0x8],ecx
        pop  ebx
        add  esp,0x44
        ret
    loc_004046D6:
        mov  eax,DWORD PTR [esi]
        mov  edx,edi
        mov  DWORD PTR [edx],eax
        mov  ecx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [edx+0x4],ecx
        mov  eax,DWORD PTR [esi+0x8]
        pop  esi
        mov  DWORD PTR [edx+0x8],eax
        mov  eax,edi
        pop  ebx
        add  esp,0x44
        ret
    loc_004046F0:
        mov  eax,DWORD PTR [esi+0x48]
        cmp  eax,0x7
        jne loc_00404755
        mov  ecx,esi
        mov  edx,DWORD PTR [ecx]
        mov  eax,DWORD PTR [ecx+0x4]
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esp+0x10],edx
        fld  DWORD PTR [esp+0x10]
        fadd  DWORD PTR [esi+0xc]
        mov  DWORD PTR [esp+0x14],eax
        mov  DWORD PTR [esp+0x18],ecx
        fstp  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esp+0x14]
        fadd  DWORD PTR [esi+0x10]
        fstp  DWORD PTR [esp+0x20]
        mov  ecx,DWORD PTR [esp+0x20]
        fld  DWORD PTR [esp+0x18]
        fadd  DWORD PTR [esi+0x14]
        mov  DWORD PTR [esi],eax
        mov  DWORD PTR [esi+0x4],ecx
        fstp  DWORD PTR [esp+0x24]
        mov  edx,DWORD PTR [esp+0x24]
        mov  DWORD PTR [esi+0x8],edx
        mov  esi,edi
        mov  DWORD PTR [esi],eax
        mov  DWORD PTR [esi+0x4],ecx
        mov  DWORD PTR [esi+0x8],edx
        pop  esi
        mov  eax,edi
        pop  ebx
        add  esp,0x44
        ret
    loc_00404755:
        cmp  eax,0x11
        jne loc_004047F2
        mov  edx,esi
        mov  eax,DWORD PTR [edx]
        mov  ecx,DWORD PTR [edx+0x4]
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [esp+0x1c],eax
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [esi+0x24]
        lea  eax,[esi+0x24]
        mov  DWORD PTR [esp+0x20],ecx
        push  ebp
        fstp  DWORD PTR [esp+0x14]
        mov  ecx,DWORD PTR [esp+0x14]
        fld  DWORD PTR [esp+0x24]
        mov  DWORD PTR [esp+0x28],edx
        fadd  DWORD PTR [eax+0x4]
        mov  ebp,esi
        fstp  DWORD PTR [esp+0x18]
        mov  edx,DWORD PTR [esp+0x18]
        fld  DWORD PTR [esp+0x28]
        fadd  DWORD PTR [eax+0x8]
        mov  DWORD PTR [ebp+0x0],ecx
        mov  DWORD PTR [ebp+0x4],edx
        fstp  DWORD PTR [esp+0x1c]
        mov  ebx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [ebp+0x8],ebx
        fld  DWORD PTR [eax]
        fadd  DWORD PTR [esi+0xc]
        pop  ebp
        fstp  DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esi+0x10]
        fadd  DWORD PTR [eax+0x4]
        fstp  DWORD PTR [esp+0x20]
        fld  DWORD PTR [esi+0x14]
        mov  esi,DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [eax+0x8]
        mov  DWORD PTR [eax],esi
        mov  esi,DWORD PTR [esp+0x20]
        mov  DWORD PTR [eax+0x4],esi
        fstp  DWORD PTR [esp+0x24]
        mov  esi,DWORD PTR [esp+0x24]
        mov  DWORD PTR [eax+0x8],esi
        mov  eax,edi
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [eax+0x4],edx
        pop  esi
        mov  DWORD PTR [eax+0x8],ebx
        pop  ebx
        add  esp,0x44
        ret
    loc_004047F2:
        cmp  eax,0x8
        fild  DWORD PTR [esp+0xc]
        jne loc_00404915
        fdivr DWORD PTR [esi+0x38]
        mov  ecx,edi
        fld  st(0)
        fadd  st,st(1)
        fld  st(1)
        fsub  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [esp+0x8]
        fld  DWORD PTR ds:0x470afc
        fadd  st,st(1)
        fmul  DWORD PTR [esp+0x8]
        fmul  DWORD PTR [esp+0x8]
        fstp  DWORD PTR [esp+0xc]
        fsubr DWORD PTR ds:0x470bd4
        fmul  st,st(1)
        fmul  st,st(1)
        fld  DWORD PTR ds:0x470afc
        fsub  st,st(2)
        fld  st(0)
        fmulp st(1),st
        fmul  st,st(2)
        fld  DWORD PTR [esp+0x8]
        fmul  st,st(3)
        fmul  st,st(3)
        fld  st(0)
        fmul  DWORD PTR [esi+0x24]
        fstp  DWORD PTR [esp+0x10]
        fld  st(0)
        fmul  DWORD PTR [esi+0x28]
        fstp  DWORD PTR [esp+0x14]
        fmul  DWORD PTR [esi+0x2c]
        fstp  DWORD PTR [esp+0x18]
        fld  st(0)
        fmul  DWORD PTR [esi+0x18]
        fstp  DWORD PTR [esp+0x1c]
        fld  st(0)
        fmul  DWORD PTR [esi+0x1c]
        fstp  DWORD PTR [esp+0x20]
        fmul  DWORD PTR [esi+0x20]
        fstp  DWORD PTR [esp+0x24]
        fld  st(0)
        fmul  DWORD PTR [esi+0xc]
        fstp  DWORD PTR [esp+0x28]
        fld  st(0)
        fmul  DWORD PTR [esi+0x10]
        fstp  DWORD PTR [esp+0x2c]
        fmul  DWORD PTR [esi+0x14]
        fstp  st(1)
        fld  DWORD PTR [esp+0xc]
        fmul  DWORD PTR [esi]
        fld  DWORD PTR [esp+0xc]
        fmul  DWORD PTR [esi+0x4]
        fld  DWORD PTR [esp+0xc]
        fmul  DWORD PTR [esi+0x8]
        fstp  DWORD PTR [esp+0x48]
        fxch  st(1)
        fadd  DWORD PTR [esp+0x28]
        fstp  DWORD PTR [esp+0x34]
        fadd  DWORD PTR [esp+0x2c]
        fld  DWORD PTR [esp+0x48]
        fadd  st,st(2)
        fstp  DWORD PTR [esp+0x3c]
        fld  DWORD PTR [esp+0x34]
        fadd  DWORD PTR [esp+0x1c]
        fstp  DWORD PTR [esp+0x40]
        fadd  DWORD PTR [esp+0x20]
        fstp  st(1)
        fld  DWORD PTR [esp+0x3c]
        fadd  DWORD PTR [esp+0x24]
        fld  DWORD PTR [esp+0x40]
        fadd  DWORD PTR [esp+0x10]
        fstp  DWORD PTR [esp+0x1c]
        mov  edx,DWORD PTR [esp+0x1c]
        fxch  st(1)
        mov  DWORD PTR [ecx],edx
        fadd  DWORD PTR [esp+0x14]
        fstp  DWORD PTR [esp+0x20]
        mov  eax,DWORD PTR [esp+0x20]
        fadd  DWORD PTR [esp+0x18]
        fstp  DWORD PTR [esp+0x24]
        mov  edx,DWORD PTR [esp+0x24]
        mov  DWORD PTR [ecx+0x4],eax
        pop  esi
        mov  DWORD PTR [ecx+0x8],edx
        mov  eax,edi
        pop  ebx
        add  esp,0x44
        ret
    loc_00404915:
        push  ecx
        mov  ecx,DWORD PTR [esi+0x38]
        fstp  DWORD PTR [esp]
        push  ecx
        call FUN_0044c350
        fld  DWORD PTR [esi+0xc]
        fsub  DWORD PTR [esi]
        mov  edx,edi
        fld  DWORD PTR [esi+0x10]
        fsub  DWORD PTR [esi+0x4]
        fld  DWORD PTR [esi+0x14]
        fsub  DWORD PTR [esi+0x8]
        fstp  DWORD PTR [esp+0x48]
        fxch  st(1)
        fmul  st,st(2)
        fstp  DWORD PTR [esp+0x34]
        fmul  st,st(1)
        fld  DWORD PTR [esp+0x48]
        fmul  st,st(2)
        fstp  DWORD PTR [esp+0x3c]
        fld  DWORD PTR [esp+0x34]
        fadd  DWORD PTR [esi]
        fstp  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [esi+0x4]
        fstp  DWORD PTR [esp+0x20]
        mov  ecx,DWORD PTR [esp+0x20]
        fstp  st(0)
        fld  DWORD PTR [esp+0x3c]
        fadd  DWORD PTR [esi+0x8]
        mov  DWORD PTR [edx],eax
        mov  DWORD PTR [edx+0x4],ecx
        pop  esi
        fstp  DWORD PTR [esp+0x20]
        mov  eax,DWORD PTR [esp+0x20]
        mov  DWORD PTR [edx+0x8],eax
        mov  eax,edi
        pop  ebx
        add  esp,0x44
        ret
    }
}
