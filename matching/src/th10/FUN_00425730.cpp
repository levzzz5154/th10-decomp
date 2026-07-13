// 00425730: FUN_00425730
// Original size: 3120 bytes, actual code: 772 instructions
extern "C" void FUN_00405410(void);
extern "C" void FUN_004054b0(void);
extern "C" void FUN_00405860(void);
extern "C" void FUN_00408030(void);
extern "C" void FUN_00408100(void);
extern "C" void FUN_0040ac90(void);
extern "C" void FUN_00412e70(void);
extern "C" void FUN_0041bb00(void);
extern "C" void FUN_0041c800(void);
extern "C" void FUN_0041c850(void);
extern "C" void FUN_004231d0(void);
extern "C" void FUN_004250b0(void);
extern "C" void FUN_00426610(void);
extern "C" void FUN_004269d0(void);
extern "C" void FUN_00426f70(void);
extern "C" void FUN_00427b50(void);
extern "C" void FUN_004281d0(void);
extern "C" void FUN_00428280(void);
extern "C" void FUN_0043ee30(void);
extern "C" void FUN_0044bc70(void);
extern "C" void FUN_0044c2a0(void);
extern "C" void FUN_0044c5d0(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00425730(void) {
    __asm {
        sub  esp,0x1c
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x28]
        mov  eax,DWORD PTR [ebp+0x458]
        cmp  eax,0x4
        push  esi
        push  edi
        ja loc_00425D72
        jmp  DWORD PTR [eax*4+0x426344]
        mov  ecx,DWORD PTR [ebp+0x478]
        imul  ecx,ecx,0x1f40
        mov  eax,0x88888889
        imul  ecx
        add  edx,ecx
        sar  edx,0x5
        mov  ecx,edx
        shr  ecx,0x1f
        add  ecx,edx
        mov  eax,0xbb80
        sub  eax,ecx
        mov  DWORD PTR [esp+0x30],eax
        mov  DWORD PTR [ebp+0x3d0],eax
        mov  ebx,0x1
        fild  DWORD PTR [esp+0x30]
        mov  eax,0x20
        fmul  DWORD PTR ds:0x470b00
        fstp  DWORD PTR [ebp+0x3c4]
        mov  DWORD PTR [ebp+0x332c],ebx
        mov  DWORD PTR [ebp+0x33c4],ebx
        mov  DWORD PTR [ebp+0x345c],ebx
        mov  DWORD PTR [ebp+0x34f4],ebx
        mov  edx,DWORD PTR [ebp+0x3500]
        shl  edx,0x3
        cmp  edx,eax
        jge loc_00425804
        lea  ecx,[ebp+0x446c]
        jmp loc_004257D0
        nop
        nop
    loc_004257D0:
        mov  edx,DWORD PTR [ebp+0x3500]
        shl  edx,0x6
        mov  esi,DWORD PTR [edx+ebp*1+0x436c]
        lea  edx,[edx+ebp*1+0x436c]
        mov  DWORD PTR [ecx],esi
        mov  edx,DWORD PTR [edx+0x4]
        mov  DWORD PTR [ecx+0x4],edx
        mov  edx,DWORD PTR [ebp+0x3500]
        dec  eax
        shl  edx,0x3
        sub  ecx,0x8
        cmp  eax,edx
        jg loc_004257D0
        test  eax,eax
        jle loc_00425821
    loc_00425804:
        lea  ecx,[ebp+eax*8+0x4370]
        jmp loc_00425810
        nop
    loc_00425810:
        mov  edx,DWORD PTR [ecx-0xc]
        mov  DWORD PTR [ecx-0x4],edx
        mov  edx,DWORD PTR [ecx-0x8]
        mov  DWORD PTR [ecx],edx
        add  ecx,0xfffffff8
        dec  eax
        jne loc_00425810
    loc_00425821:
        mov  eax,DWORD PTR [ebp+0x3cc]
        mov  DWORD PTR [ebp+0x436c],eax
        mov  ecx,DWORD PTR [ebp+0x3d0]
        mov  DWORD PTR [ebp+0x4370],ecx
        mov  eax,DWORD PTR [ebp+0x478]
        cmp  eax,0x1e
        mov  DWORD PTR [esp+0x30],eax
        jl loc_004258AB
        mov  esi,DWORD PTR ds:0x4776f0
        add  esi,0x60
        mov  edi,0x7d0
        jmp loc_00425860
        nop
        nop
    loc_00425860:
        mov  ax,WORD PTR [esi+0x446]
        test  ax,ax
        je loc_0042587E
        cmp  ax,0x3
        je loc_0042587E
        mov  eax,DWORD PTR [esi+0x4]
        test  eax,eax
        jne loc_0042587E
        call FUN_00408030
    loc_0042587E:
        add  esi,0x7f0
        dec  edi
        jne loc_00425860
        mov  edx,DWORD PTR ds:0x47781c
        mov  ecx,DWORD PTR [edx+0x18]
        test  ecx,ecx
        je loc_00425902
    loc_00425894:
        cmp  DWORD PTR [ecx+0xc],ebx
        mov  esi,DWORD PTR [ecx+0x8]
        je loc_004258A3
        mov  eax,DWORD PTR [ecx]
        push  0x0
        call  DWORD PTR [eax+0x14]
    loc_004258A3:
        test  esi,esi
        mov  ecx,esi
        jne loc_00425894
        jmp loc_00425902
    loc_004258AB:
        fild  DWORD PTR [esp+0x30]
        mov  eax,ds:0x4776f0
        push  ebx
        push  0x0
        fmul  DWORD PTR ds:0x470d44
        lea  esi,[ebp+0x440]
        mov  ebx,esi
        fadd  DWORD PTR ds:0x470bc8
        fstp  DWORD PTR [esp+0x38]
        mov  edi,DWORD PTR [esp+0x38]
        push  edi
        call FUN_00408100
        fld  DWORD PTR [esp+0x30]
        fmul  DWORD PTR ds:0x470d40
        mov  eax,ds:0x4776f0
        push  0x0
        push  0x0
        push  ecx
        fstp  DWORD PTR [esp]
        call FUN_00408100
        mov  eax,ds:0x47781c
        push  0x0
        push  edi
        call FUN_0041c800
    loc_00425902:
        cmp  DWORD PTR [ebp+0x478],0x3c
        jl loc_00425D72
        mov  DWORD PTR [ebp+0x458],0x1
        mov  eax,DWORD PTR [ebp+0x484]
        xor  ecx,ecx
        test  al,0x1
        jne loc_0042594E
        or   eax,0x1
        mov  DWORD PTR [ebp+0x478],ecx
        mov  DWORD PTR [ebp+0x474],0xfff0bdc1
        mov  DWORD PTR [ebp+0x47c],ecx
        mov  DWORD PTR [ebp+0x480],0x476f78
        mov  DWORD PTR [ebp+0x484],eax
    loc_0042594E:
        mov  DWORD PTR [ebp+0x478],ecx
        mov  DWORD PTR [ebp+0x47c],ecx
        mov  DWORD PTR [ebp+0x474],0xffffffff
        mov  eax,ds:0x47770c
        test  eax,eax
        je loc_00425A24
        mov  ecx,DWORD PTR [eax+0x9eb8]
        test  ecx,ecx
        jne loc_00425A24
        mov  esi,DWORD PTR ds:0x4776ec
        test  esi,esi
        je loc_00425A24
        mov  eax,DWORD PTR [esi+0x28]
        test  eax,eax
        jne loc_00425A24
        movsx ecx,WORD PTR ds:0x474c48
        mov  eax,0x66666667
        imul  ecx
        sar  edx,0x3
        mov  ecx,edx
        shr  ecx,0x1f
        add  ecx,edx
        test  cx,cx
        je loc_00425A24
        test  BYTE PTR ds:0x474e5c,0x2
        je loc_00425A24
        push  0x10e
        lea  eax,[ebp+0x430c]
        call FUN_00405410
        push  esi
        call FUN_00405860
        add  WORD PTR ds:0x474c48,0xffec
        push  ebp
        call FUN_00426f70
        movsx eax,WORD PTR ds:0x474c48
        cdq
        mov  ecx,0x14
        idiv  ecx
        mov  esi,DWORD PTR ds:0x47770c
        imul  edx,edx,0x64
        mov  ecx,eax
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x3
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        push  eax
        mov  edx,ecx
        call FUN_004054b0
        push  0xbb8
        mov  ecx,0x474c40
        call FUN_00412e70
    loc_00425A24:
        cmp  DWORD PTR [ebp+0x478],0x1e
        jge loc_00425A8A
        mov  esi,DWORD PTR ds:0x4776f0
        add  esi,0x60
        mov  edi,0x7d0
        jmp loc_00425A40
        nop
    loc_00425A40:
        mov  ax,WORD PTR [esi+0x446]
        test  ax,ax
        je loc_00425A5E
        cmp  ax,0x3
        je loc_00425A5E
        mov  eax,DWORD PTR [esi+0x4]
        test  eax,eax
        jne loc_00425A5E
        call FUN_00408030
    loc_00425A5E:
        add  esi,0x7f0
        dec  edi
        jne loc_00425A40
        mov  ecx,DWORD PTR ds:0x47781c
        mov  ecx,DWORD PTR [ecx+0x18]
        test  ecx,ecx
        je loc_00425A8A
    loc_00425A74:
        cmp  DWORD PTR [ecx+0xc],0x1
        mov  esi,DWORD PTR [ecx+0x8]
        je loc_00425A84
        mov  edx,DWORD PTR [ecx]
        push  0x0
        call  DWORD PTR [edx+0x14]
    loc_00425A84:
        test  esi,esi
        mov  ecx,esi
        jne loc_00425A74
    loc_00425A8A:
        mov  edi,ebp
        call FUN_004250b0
        jmp loc_00425D72
        cmp  DWORD PTR [ebp+0x478],0x8
        jl loc_00425BD9
        push  ebp
        call FUN_004269d0
        cmp  DWORD PTR [ebp+0x478],0x3
        jne loc_00425B9D
        add  WORD PTR ds:0x474c48,0xffc0
        jns loc_00425AC9
        mov  WORD PTR ds:0x474c48,0x0
    loc_00425AC9:
        movsx eax,WORD PTR ds:0x474c48
        cdq
        mov  ecx,0x14
        idiv  ecx
        mov  esi,DWORD PTR ds:0x47770c
        imul  edx,edx,0x64
        mov  ecx,eax
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x3
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        push  eax
        mov  edx,ecx
        call FUN_004054b0
        lea  eax,[esp+0x14]
        fld  DWORD PTR [ebp+0x3c4]
        mov  ecx,ebp
        fsub  DWORD PTR ds:0x470b4c
        mov  DWORD PTR [esp+0x14],0x0
        mov  DWORD PTR [esp+0x1c],0x0
        fstp  DWORD PTR [esp+0x18]
        call FUN_00426610
        xor  esi,esi
        fstp  DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0x30],esi
        lea  edi,[ebp+0x3c0]
        jmp loc_00425B40
        nop
    loc_00425B40:
        cmp  esi,0x1
        fild  DWORD PTR [esp+0x30]
        fmul  DWORD PTR ds:0x470d3c
        fadd  DWORD PTR [esp+0x10]
        fsub  DWORD PTR ds:0x470d38
        fstp  DWORD PTR [esp+0x30]
        je loc_00425B6C
        cmp  esi,0x3
        je loc_00425B6C
        cmp  esi,0x5
        mov  eax,0x1
        jne loc_00425B71
    loc_00425B6C:
        mov  eax,0x4
    loc_00425B71:
        mov  ecx,DWORD PTR [esp+0x30]
        push  0x40400000
        push  ecx
        push  0xffffff
        push  eax
        mov  eax,ds:0x477818
        mov  ecx,edi
        call FUN_0041bb00
        inc  esi
        cmp  esi,0x7
        mov  DWORD PTR [esp+0x30],esi
        jl loc_00425B40
        push  ebp
        call FUN_00426f70
    loc_00425B9D:
        cmp  DWORD PTR [ebp+0x478],0x1e
        jl loc_00425D72
        mov  eax,ds:0x474c70
        xor  edi,edi
        cmp  eax,edi
        jge loc_00425CA4
        mov  edx,DWORD PTR ds:0x477838
        cmp  DWORD PTR [edx+0x10],0x1
        je loc_00425C93
        mov  edi,DWORD PTR ds:0x477830
        call FUN_004231d0
        jmp loc_00425D72
    loc_00425BD9:
        mov  esi,DWORD PTR ds:0x4776ec
        test  esi,esi
        je loc_00425D72
        mov  eax,DWORD PTR [esi+0x28]
        test  eax,eax
        jne loc_00425D72
        movsx ecx,WORD PTR ds:0x474c48
        mov  eax,0x66666667
        imul  ecx
        sar  edx,0x3
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        test  ax,ax
        je loc_00425D72
        test  BYTE PTR ds:0x474e5c,0x2
        je loc_00425D72
        push  0x3c
        lea  eax,[ebp+0x474]
        call FUN_00405410
        push  0xc8
        lea  eax,[ebp+0x430c]
        call FUN_00405410
        push  esi
        call FUN_00405860
        add  WORD PTR ds:0x474c48,0xffec
        push  ebp
        call FUN_00426f70
        movsx eax,WORD PTR ds:0x474c48
        cdq
        mov  ecx,0x14
        idiv  ecx
        mov  esi,DWORD PTR ds:0x47770c
        imul  edx,edx,0x64
        mov  ecx,eax
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x3
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        push  eax
        mov  edx,ecx
        call FUN_004054b0
        mov  DWORD PTR [ebp+0x458],0x1
        jmp loc_00425D72
    loc_00425C93:
        push  0x4
        mov  eax,0x491c28
        call FUN_0040ac90
        jmp loc_00425D72
    loc_00425CA4:
        push  0x96
        push  0x1e
        push  0x41800000
        push  0x42000000
        lea  esi,[ebp+0x3c0]
        mov  DWORD PTR [ebp+0x458],edi
        push  esi
        mov  edx,ebp
        mov  DWORD PTR ds:0x476f78,0x3f800000
        call FUN_00427b50
        mov  ecx,esi
        mov  edx,DWORD PTR [ecx]
        lea  eax,[ebp+0x440]
        mov  DWORD PTR [eax],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [eax+0x4],edx
        mov  DWORD PTR [eax+0x8],ecx
        push  0x118
        lea  eax,[ebp+0x430c]
        mov  DWORD PTR [ebp+0x3cc],edi
        mov  DWORD PTR [ebp+0x3d0],0xbb80
        mov  DWORD PTR [esi],edi
        mov  DWORD PTR [ebp+0x3c4],0x43f00000
        call FUN_00405410
        push  edi
        lea  eax,[ebp+0x474]
        call FUN_00405410
        jmp loc_00425D72
        mov  eax,DWORD PTR [ebp+0x478]
        cmp  eax,0x4
        je loc_00425D72
        cmp  eax,0xf
        jne loc_00425D72
        mov  esi,DWORD PTR ds:0x4776f0
        add  esi,0x60
        mov  edi,0x7d0
    loc_00425D43:
        mov  ax,WORD PTR [esi+0x446]
        test  ax,ax
        je loc_00425D5A
        cmp  ax,0x3
        je loc_00425D5A
        call FUN_00408030
    loc_00425D5A:
        add  esi,0x7f0
        dec  edi
        jne loc_00425D43
        mov  eax,ds:0x47781c
        mov  ebx,0x1
        call FUN_0041c850
    loc_00425D72:
        lea  ebx,[ebp+0x350c]
        lea  edi,[ebx+0x24]
        mov  DWORD PTR [esp+0x30],0x20
    loc_00425D83:
        test  BYTE PTR [edi+0x44],0x1
        je loc_00425E31
        test  BYTE PTR [edi+0x1c],0x1
        jne loc_00425DAB
        mov  edx,DWORD PTR [edi+0xc]
        mov  eax,DWORD PTR [edi+0x10]
        push  edx
        push  eax
        mov  ecx,edi
        call FUN_0044c5d0
        mov  DWORD PTR [edi+0x8],0x0
        jmp loc_00425DC6
    loc_00425DAB:
        fld  DWORD PTR [edi+0x18]
        push  ecx
        fadd  DWORD PTR [edi+0x14]
        fstp  DWORD PTR [edi+0x14]
        fld  DWORD PTR [edi+0xc]
        fadd  DWORD PTR [edi+0x10]
        fstp  DWORD PTR [esp]
        call FUN_0044bc70
        fstp  DWORD PTR [edi+0x10]
    loc_00425DC6:
        lea  esi,[edi-0xc]
        call FUN_0044c2a0
        fld  DWORD PTR [edi-0x20]
        fadd  DWORD PTR [ebx]
        fstp  DWORD PTR [ebx]
        fld  DWORD PTR [edi-0x18]
        fadd  DWORD PTR [edi-0x1c]
        fstp  DWORD PTR [edi-0x1c]
        mov  ecx,DWORD PTR [edi+0x24]
        mov  DWORD PTR [edi+0x20],ecx
        mov  ecx,DWORD PTR [edi+0x2c]
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00425E10
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00425E10
        fld  DWORD PTR [edi+0x28]
        fsub  DWORD PTR ds:0x470afc
        jmp loc_00425E1B
    loc_00425E10:
        fld  DWORD PTR [ecx]
        fmul  DWORD PTR ds:0x470afc
        fsubr DWORD PTR [edi+0x28]
    loc_00425E1B:
        fstp  DWORD PTR [edi+0x28]
        fld  DWORD PTR [edi+0x28]
        call FUN_00463b2c
        test  eax,eax
        mov  DWORD PTR [edi+0x24],eax
        jg loc_00425E31
        and  DWORD PTR [edi+0x44],0xfffffffe
    loc_00425E31:
        mov  eax,DWORD PTR [esp+0x30]
        add  ebx,0x6c
        add  edi,0x6c
        dec  eax
        mov  DWORD PTR [esp+0x30],eax
        jne loc_00425D83
        mov  eax,DWORD PTR [ebp+0x4310]
        xor  edi,edi
        cmp  eax,edi
        jle loc_00425EE6
        mov  ecx,DWORD PTR [ebp+0x4318]
        mov  edx,eax
        mov  DWORD PTR [ebp+0x430c],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00425E90
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00425E90
        fld  DWORD PTR [ebp+0x4314]
        fsub  DWORD PTR ds:0x470afc
        jmp loc_00425E9E
    loc_00425E90:
        fld  DWORD PTR [ecx]
        fmul  DWORD PTR ds:0x470afc
        fsubr DWORD PTR [ebp+0x4314]
    loc_00425E9E:
        fstp  DWORD PTR [ebp+0x4314]
        fld  DWORD PTR [ebp+0x4314]
        call FUN_00463b2c
        mov  DWORD PTR [ebp+0x4310],eax
        mov  eax,DWORD PTR [ebp+0x478]
        cmp  eax,DWORD PTR [ebp+0x474]
        je loc_00425EE6
        cdq
        mov  ecx,0x3
        idiv  ecx
        test  edx,edx
        jne loc_00425EE6
        mov  eax,DWORD PTR [ebp+0x370]
        mov  DWORD PTR [ebp+0x314],0xff0000ff
        or   eax,0x8000
        jmp loc_00425EF1
    loc_00425EE6:
        mov  eax,DWORD PTR [ebp+0x370]
        and  eax,0xffff7fff
    loc_00425EF1:
        lea  edx,[ebp+0x14]
        push  edx
        mov  DWORD PTR [ebp+0x370],eax
        call FUN_0043ee30
        fld  DWORD PTR [ebp+0x3c0]
        fsub  DWORD PTR [ebp+0x41c]
        lea  eax,[ebp+0x404]
        fstp  DWORD PTR [esp+0x14]
        mov  ecx,DWORD PTR [esp+0x14]
        fld  DWORD PTR [ebp+0x3c4]
        fsub  DWORD PTR [ebp+0x420]
        fstp  DWORD PTR [esp+0x18]
        mov  edx,DWORD PTR [esp+0x18]
        fld  DWORD PTR [ebp+0x3c8]
        fsub  DWORD PTR [ebp+0x424]
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [eax+0x4],edx
        lea  edx,[ebp+0x410]
        fstp  DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [eax+0x8],ecx
        fld  DWORD PTR [ebp+0x41c]
        fadd  DWORD PTR [ebp+0x3c0]
        fstp  DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x14]
        fld  DWORD PTR [ebp+0x420]
        fadd  DWORD PTR [ebp+0x3c4]
        fstp  DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [esp+0x18]
        fld  DWORD PTR [ebp+0x424]
        fadd  DWORD PTR [ebp+0x3c8]
        mov  DWORD PTR [edx],eax
        mov  DWORD PTR [edx+0x4],ecx
        lea  ecx,[ebp+0x4324]
        fstp  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [edx+0x8],eax
        fld  DWORD PTR [ebp+0x428]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [ebp+0x42c]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [ebp+0x430]
        fmul  DWORD PTR ds:0x470b0c
        fstp  DWORD PTR [esp+0x28]
        fld  DWORD PTR [ebp+0x3c0]
        fsub  st,st(2)
        fstp  DWORD PTR [esp+0x14]
        mov  edx,DWORD PTR [esp+0x14]
        fld  DWORD PTR [ebp+0x3c4]
        fsub  st,st(1)
        fstp  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [esp+0x18]
        fstp  st(0)
        fstp  st(0)
        fld  DWORD PTR [ebp+0x3c8]
        mov  DWORD PTR [ecx],edx
        fsub  DWORD PTR [esp+0x28]
        mov  DWORD PTR [ecx+0x4],eax
        lea  eax,[ebp+0x4330]
        fstp  DWORD PTR [esp+0x1c]
        mov  edx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [ecx+0x8],edx
        fld  DWORD PTR [ebp+0x428]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [ebp+0x42c]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [ebp+0x430]
        fmul  DWORD PTR ds:0x470b0c
        fstp  DWORD PTR [esp+0x28]
        fxch  st(1)
        fadd  DWORD PTR [ebp+0x3c0]
        fstp  DWORD PTR [esp+0x14]
        mov  ecx,DWORD PTR [esp+0x14]
        fadd  DWORD PTR [ebp+0x3c4]
        fstp  DWORD PTR [esp+0x18]
        mov  edx,DWORD PTR [esp+0x18]
        fld  DWORD PTR [esp+0x28]
        fadd  DWORD PTR [ebp+0x3c8]
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [eax+0x4],edx
        fstp  DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [eax+0x8],ecx
        fld  DWORD PTR [ebp+0x3c0]
        fsub  DWORD PTR [ebp+0x434]
        lea  edx,[ebp+0x433c]
        fstp  DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x14]
        fld  DWORD PTR [ebp+0x3c4]
        fsub  DWORD PTR [ebp+0x438]
        fstp  DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [esp+0x18]
        fld  DWORD PTR [ebp+0x3c8]
        fsub  DWORD PTR [ebp+0x43c]
        mov  DWORD PTR [edx],eax
        mov  DWORD PTR [edx+0x4],ecx
        lea  ecx,[ebp+0x4348]
        fstp  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [edx+0x8],eax
        fld  DWORD PTR [ebp+0x434]
        fadd  DWORD PTR [ebp+0x3c0]
        fstp  DWORD PTR [esp+0x14]
        mov  edx,DWORD PTR [esp+0x14]
        fld  DWORD PTR [ebp+0x438]
        fadd  DWORD PTR [ebp+0x3c4]
        fstp  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [esp+0x18]
        fld  DWORD PTR [ebp+0x43c]
        fadd  DWORD PTR [ebp+0x3c8]
        mov  DWORD PTR [ecx],edx
        mov  DWORD PTR [ecx+0x4],eax
        lea  eax,[ebp+0x4354]
        fstp  DWORD PTR [esp+0x1c]
        mov  edx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [ecx+0x8],edx
        fld  DWORD PTR [ebp+0x3c0]
        fsub  DWORD PTR [ebp+0x428]
        fstp  DWORD PTR [esp+0x14]
        mov  ecx,DWORD PTR [esp+0x14]
        fld  DWORD PTR [ebp+0x3c4]
        fsub  DWORD PTR [ebp+0x42c]
        fstp  DWORD PTR [esp+0x18]
        mov  edx,DWORD PTR [esp+0x18]
        fld  DWORD PTR [ebp+0x3c8]
        fsub  DWORD PTR [ebp+0x430]
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [eax+0x4],edx
        lea  edx,[ebp+0x4360]
        fstp  DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [eax+0x8],ecx
        fld  DWORD PTR [ebp+0x428]
        fadd  DWORD PTR [ebp+0x3c0]
        fstp  DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x14]
        fld  DWORD PTR [ebp+0x42c]
        fadd  DWORD PTR [ebp+0x3c4]
        fstp  DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [esp+0x18]
        fld  DWORD PTR [ebp+0x430]
        fadd  DWORD PTR [ebp+0x3c8]
        mov  DWORD PTR [edx],eax
        mov  DWORD PTR [edx+0x4],ecx
        fstp  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [edx+0x8],eax
        mov  edx,DWORD PTR [ebp+0x478]
        mov  ecx,DWORD PTR [ebp+0x480]
        mov  DWORD PTR [ebp+0x474],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_004261D9
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_004261D9
        fld  DWORD PTR [ebp+0x47c]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [ebp+0x478],edx
        fstp  DWORD PTR [ebp+0x47c]
        jmp loc_004261F2
    loc_004261D9:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [ebp+0x47c]
        fst  DWORD PTR [ebp+0x47c]
        call FUN_00463b2c
        mov  DWORD PTR [ebp+0x478],eax
    loc_004261F2:
        mov  edx,DWORD PTR [ebp+0x48c]
        mov  ecx,DWORD PTR [ebp+0x494]
        mov  DWORD PTR [ebp+0x488],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_0042623D
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0042623D
        fld  DWORD PTR [ebp+0x490]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [ebp+0x48c],edx
        fstp  DWORD PTR [ebp+0x490]
        jmp loc_00426256
    loc_0042623D:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [ebp+0x490]
        fst  DWORD PTR [ebp+0x490]
        call FUN_00463b2c
        mov  DWORD PTR [ebp+0x48c],eax
    loc_00426256:
        mov  esi,DWORD PTR ds:0x47770c
        cmp  DWORD PTR [esi+0x9eb8],edi
        mov  ecx,DWORD PTR ds:0x477704
        jne loc_004262CE
        cmp  ecx,edi
        je loc_004262B4
        cmp  DWORD PTR [ecx+0x60],edi
        je loc_004262B4
        mov  eax,DWORD PTR [ebp+0x478]
        cdq
        mov  ebx,0x3c
        idiv  ebx
        test  edx,edx
        jne loc_004262B4
        mov  eax,ds:0x474c98
        inc  eax
        cmp  eax,0x400
        mov  ds:0x474c98,eax
        jle loc_004262A3
        mov  DWORD PTR ds:0x474c98,0x400
        jmp loc_004262B4
    loc_004262A3:
        cmp  eax,0xfffffc00
        jge loc_004262B4
        mov  DWORD PTR ds:0x474c98,0xfffffc00
    loc_004262B4:
        cmp  DWORD PTR [esi+0x9eb8],edi
        jne loc_004262CE
        cmp  ecx,edi
        je loc_004262CE
        cmp  DWORD PTR [ecx+0x60],edi
        je loc_004262CE
        mov  eax,ebp
        call FUN_004281d0
        jmp loc_0042632C
    loc_004262CE:
        mov  eax,DWORD PTR [ebp+0x470]
        test  al,0x1
        jne loc_00426301
        or   eax,0x1
        mov  DWORD PTR [ebp+0x464],edi
        mov  DWORD PTR [ebp+0x460],0xfff0bdc1
        mov  DWORD PTR [ebp+0x468],edi
        mov  DWORD PTR [ebp+0x46c],0x476f78
        mov  DWORD PTR [ebp+0x470],eax
    loc_00426301:
        mov  DWORD PTR [ebp+0x464],0xffffffff
        mov  DWORD PTR [ebp+0x468],0xbf800000
        mov  DWORD PTR [ebp+0x460],0xfffffffe
        mov  DWORD PTR [ebp+0x3504],edi
        mov  BYTE PTR [ebp+0x3508],0x0
    loc_0042632C:
        push  ebp
        call FUN_00428280
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        add  esp,0x1c
        ret  0x4
        nop
        push  ecx
        push  edi
        inc  edx
        add  BYTE PTR [ecx+ebx*2+0x42],ah
        add  BYTE PTR [ecx+0x2500425a],ch
        pop  ebp
        inc  edx
        add  BYTE PTR [esi-0x33ffbda6],dl
    }
}
