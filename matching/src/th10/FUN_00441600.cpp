// 00441600: FUN_00441600
// Original size: 848 bytes, actual code: 285 instructions
extern "C" void FUN_00441e50(void);
extern "C" void FUN_0044c350(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00441600(void) {
    __asm {
        sub  esp,0x48
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x54]
        mov  ebx,eax
        mov  eax,DWORD PTR [ebx+0x44]
        push  esi
        xor  esi,esi
        cmp  eax,esi
        mov  DWORD PTR [esp+0x58],eax
        jle loc_004416EB
        mov  edx,DWORD PTR [ebx+0x34]
        mov  ecx,DWORD PTR [ebx+0x3c]
        mov  DWORD PTR [ebx+0x30],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00441656
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00441656
        fld  DWORD PTR [ebx+0x38]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [ebx+0x34],edx
        fstp  DWORD PTR [ebx+0x38]
        jmp loc_00441666
    loc_00441656:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [ebx+0x38]
        fst  DWORD PTR [ebx+0x38]
        call FUN_00463b2c
        mov  DWORD PTR [ebx+0x34],eax
    loc_00441666:
        mov  ecx,DWORD PTR [ebx+0x44]
        cmp  DWORD PTR [ebx+0x34],ecx
        mov  DWORD PTR [esp+0x58],ecx
        jl loc_004416EB
        mov  eax,DWORD PTR [ebx+0x40]
        test  al,0x1
        mov  DWORD PTR [esp+0x58],ecx
        jne loc_00441697
        or   eax,0x1
        mov  DWORD PTR [ebx+0x34],esi
        mov  DWORD PTR [ebx+0x30],0xfff0bdc1
        mov  DWORD PTR [ebx+0x38],esi
        mov  DWORD PTR [ebx+0x3c],0x476f78
        mov  DWORD PTR [ebx+0x40],eax
    loc_00441697:
        fild  DWORD PTR [esp+0x58]
        mov  DWORD PTR [ebx+0x34],ecx
        dec  ecx
        mov  DWORD PTR [ebx+0x30],ecx
        fstp  DWORD PTR [ebx+0x38]
        mov  eax,DWORD PTR [ebx+0x48]
        cmp  eax,0x7
        mov  DWORD PTR [ebx+0x44],esi
        je loc_004416CE
        add  ebx,0xc
        mov  ecx,DWORD PTR [ebx]
        mov  eax,ebp
        mov  DWORD PTR [eax],ecx
        mov  edx,DWORD PTR [ebx+0x4]
        pop  esi
        mov  DWORD PTR [eax+0x4],edx
        mov  ecx,DWORD PTR [ebx+0x8]
        pop  ebp
        mov  DWORD PTR [eax+0x8],ecx
        pop  ebx
        add  esp,0x48
        ret  0x4
    loc_004416CE:
        mov  eax,DWORD PTR [ebx]
        mov  edx,ebp
        mov  DWORD PTR [edx],eax
        mov  ecx,DWORD PTR [ebx+0x4]
        mov  DWORD PTR [edx+0x4],ecx
        mov  eax,DWORD PTR [ebx+0x8]
        pop  esi
        mov  DWORD PTR [edx+0x8],eax
        mov  eax,ebp
        pop  ebp
        pop  ebx
        add  esp,0x48
        ret  0x4
    loc_004416EB:
        mov  eax,DWORD PTR [ebx+0x48]
        cmp  eax,0x7
        jne loc_00441729
        mov  eax,ebx
        mov  ecx,DWORD PTR [eax]
        mov  edx,DWORD PTR [eax+0x4]
        mov  esi,DWORD PTR [eax+0x8]
        mov  eax,DWORD PTR [ebx+0xc]
        add  eax,ecx
        mov  ecx,DWORD PTR [ebx+0x10]
        add  ecx,edx
        mov  edx,DWORD PTR [ebx+0x14]
        mov  DWORD PTR [ebx],eax
        add  edx,esi
        mov  DWORD PTR [ebx+0x4],ecx
        mov  DWORD PTR [ebx+0x8],edx
        mov  esi,ebp
        mov  DWORD PTR [esi],eax
        mov  DWORD PTR [esi+0x4],ecx
        mov  DWORD PTR [esi+0x8],edx
        pop  esi
        mov  eax,ebp
        pop  ebp
        pop  ebx
        add  esp,0x48
        ret  0x4
    loc_00441729:
        cmp  eax,0x11
        push  edi
        jne loc_00441791
        lea  eax,[ebx+0x24]
        mov  ecx,ebx
        mov  edx,DWORD PTR [ecx]
        mov  esi,DWORD PTR [ecx+0x4]
        mov  edi,DWORD PTR [ecx+0x8]
        mov  ecx,DWORD PTR [eax]
        add  ecx,edx
        mov  edx,DWORD PTR [eax+0x4]
        add  edx,esi
        mov  esi,DWORD PTR [eax+0x8]
        add  esi,edi
        mov  edi,ebx
        mov  DWORD PTR [edi],ecx
        mov  DWORD PTR [edi+0x4],edx
        mov  DWORD PTR [edi+0x8],esi
        mov  edi,DWORD PTR [eax]
        add  edi,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0x28],edi
        mov  edi,DWORD PTR [ebx+0x10]
        add  edi,DWORD PTR [eax+0x4]
        mov  ebx,DWORD PTR [ebx+0x14]
        add  ebx,DWORD PTR [eax+0x8]
        mov  DWORD PTR [esp+0x30],ebx
        mov  ebx,DWORD PTR [esp+0x28]
        mov  DWORD PTR [eax],ebx
        mov  DWORD PTR [eax+0x4],edi
        mov  edi,DWORD PTR [esp+0x30]
        mov  DWORD PTR [eax+0x8],edi
        mov  eax,ebp
        mov  DWORD PTR [eax],ecx
        pop  edi
        mov  DWORD PTR [eax+0x4],edx
        mov  DWORD PTR [eax+0x8],esi
        pop  esi
        pop  ebp
        pop  ebx
        add  esp,0x48
        ret  0x4
    loc_00441791:
        cmp  eax,0x8
        fild  DWORD PTR [esp+0x5c]
        push  ecx
        jne loc_004418B4
        fdivr DWORD PTR [ebx+0x38]
        lea  edi,[ebx+0xc]
        lea  esi,[esp+0x38]
        fst  DWORD PTR [esp+0x60]
        fadd  st(0),st
        fstp  DWORD PTR [esp+0x18]
        fld  DWORD PTR ds:0x470bd4
        fsub  DWORD PTR [esp+0x18]
        fmul  DWORD PTR [esp+0x60]
        fmul  DWORD PTR [esp+0x60]
        fstp  DWORD PTR [esp]
        call FUN_00441e50
        fld  DWORD PTR [esp+0x5c]
        push  ecx
        fsub  DWORD PTR ds:0x470afc
        lea  esi,[esp+0x44]
        mov  edi,ebx
        mov  DWORD PTR [esp+0x1c],eax
        fstp  DWORD PTR [esp+0x14]
        fld  DWORD PTR [esp+0x18]
        fadd  DWORD PTR ds:0x470afc
        fmul  DWORD PTR [esp+0x14]
        fmul  DWORD PTR [esp+0x14]
        fstp  DWORD PTR [esp]
        call FUN_00441e50
        mov  edx,DWORD PTR [eax]
        fld  DWORD PTR ds:0x470afc
        mov  ecx,DWORD PTR [esp+0x18]
        fsub  DWORD PTR [esp+0x5c]
        add  edx,DWORD PTR [ecx]
        mov  DWORD PTR [esp+0x1c],edx
        fld  st(0)
        mov  edx,DWORD PTR [ecx+0x4]
        fmul  st,st(1)
        add  edx,DWORD PTR [eax+0x4]
        fmul  DWORD PTR [esp+0x5c]
        mov  DWORD PTR [esp+0x20],edx
        mov  ecx,DWORD PTR [ecx+0x8]
        add  ecx,DWORD PTR [eax+0x8]
        push  ecx
        fstp  DWORD PTR [esp]
        lea  edi,[ebx+0x18]
        lea  esi,[esp+0x50]
        mov  DWORD PTR [esp+0x28],ecx
        fstp  st(0)
        call FUN_00441e50
        fld  DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [eax]
        fmul  DWORD PTR [esp+0x5c]
        mov  esi,DWORD PTR [esp+0x1c]
        mov  edx,DWORD PTR [esp+0x20]
        fmul  DWORD PTR [esp+0x5c]
        add  ecx,esi
        mov  DWORD PTR [esp+0x28],ecx
        mov  ecx,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [eax+0x8]
        add  ecx,edx
        mov  DWORD PTR [esp+0x2c],ecx
        add  eax,DWORD PTR [esp+0x24]
        push  ecx
        lea  edi,[ebx+0x24]
        fstp  DWORD PTR [esp]
        lea  esi,[esp+0x20]
        mov  DWORD PTR [esp+0x34],eax
        call FUN_00441e50
        mov  ecx,DWORD PTR [eax]
        mov  edx,DWORD PTR [eax+0x4]
        mov  ebx,DWORD PTR [esp+0x28]
        mov  edi,DWORD PTR [esp+0x2c]
        mov  esi,DWORD PTR [esp+0x30]
        mov  eax,DWORD PTR [eax+0x8]
        add  ecx,ebx
        add  edx,edi
        add  eax,esi
        mov  esi,ebp
        mov  DWORD PTR [esi],ecx
        mov  DWORD PTR [esi+0x4],edx
        pop  edi
        mov  DWORD PTR [esi+0x8],eax
        pop  esi
        mov  eax,ebp
        pop  ebp
        pop  ebx
        add  esp,0x48
        ret  0x4
    loc_004418B4:
        mov  ecx,DWORD PTR [ebx+0x38]
        fstp  DWORD PTR [esp]
        push  ecx
        call FUN_0044c350
        mov  esi,DWORD PTR [ebx]
        mov  edx,DWORD PTR [ebx+0xc]
        mov  edi,DWORD PTR [ebx+0x4]
        mov  eax,DWORD PTR [ebx+0x10]
        mov  ecx,DWORD PTR [ebx+0x14]
        sub  edx,esi
        mov  DWORD PTR [esp+0x28],edx
        fild  DWORD PTR [esp+0x28]
        sub  eax,edi
        mov  DWORD PTR [esp+0x2c],eax
        mov  eax,DWORD PTR [ebx+0x8]
        fmul  st,st(1)
        sub  ecx,eax
        mov  DWORD PTR [esp+0x5c],eax
        mov  DWORD PTR [esp+0x30],ecx
        call FUN_00463b2c
        fild  DWORD PTR [esp+0x2c]
        mov  ebx,eax
        fmul  st,st(1)
        call FUN_00463b2c
        fild  DWORD PTR [esp+0x30]
        mov  DWORD PTR [esp+0x20],eax
        fmul  st,st(1)
        call FUN_00463b2c
        fstp  st(0)
        mov  edx,DWORD PTR [esp+0x20]
        mov  ecx,DWORD PTR [esp+0x5c]
        add  edi,edx
        add  esi,ebx
        mov  edx,ebp
        mov  DWORD PTR [edx],esi
        mov  DWORD PTR [edx+0x4],edi
        pop  edi
        add  eax,ecx
        pop  esi
        mov  DWORD PTR [edx+0x8],eax
        mov  eax,ebp
        pop  ebp
        pop  ebx
        add  esp,0x48
        ret  0x4
    }
}
