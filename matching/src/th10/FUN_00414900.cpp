// 00414900: FUN_00414900
// Original size: 3840 bytes, actual code: 1104 instructions
extern "C" void FUN_00415e90(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_0043e5a0(void);
extern "C" void FUN_0043ee30(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);
extern "C" void _free(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00414900(void) {
    __asm {
        push  ecx
        push  edi
        mov  edi,DWORD PTR [esp+0xc]
        test  BYTE PTR [edi+0x9eb4],0x10
        je loc_0041493C
        mov  ecx,DWORD PTR [edi+0x9ecc]
        inc  ecx
        mov  eax,ecx
        cmp  eax,0x78
        mov  DWORD PTR [edi+0x9ecc],ecx
        jl loc_0041493C
        mov  eax,ds:0x491ff4
        and  eax,0x1000
        neg  eax
        sbb  eax,eax
        and  eax,0xfffffff4
        add  eax,0xe
        mov  ds:0x491fb8,eax
    loc_0041493C:
        push  ebx
        push  ebp
        push  esi
        lea  esi,[edi+0x4980]
        mov  ebx,0x9
        lea  ebx,[ebx+0x0]
    loc_00414950:
        push  esi
        call FUN_0043ee30
        add  esi,0x3ac
        dec  ebx
        jne loc_00414950
        lea  esi,[edi+0x6a8c]
        mov  ebx,0x4
        lea  ebx,[ebx+0x0]
    loc_00414970:
        push  esi
        call FUN_0043ee30
        add  esi,0x3ac
        dec  ebx
        jne loc_00414970
        lea  esi,[edi+0x793c]
        mov  ebx,0x2
        lea  ebx,[ebx+0x0]
    loc_00414990:
        push  esi
        call FUN_0043ee30
        add  esi,0x3ac
        dec  ebx
        jne loc_00414990
        test  BYTE PTR [edi+0x9eb4],0x1
        mov  ecx,DWORD PTR ds:0x477834
        jne loc_00414A08
        test  ecx,ecx
        je loc_00414A5C
        fld  DWORD PTR [ecx+0x3c4]
        fcomp DWORD PTR ds:0x470bdc
        fnstsw ax
        test  ah,0x41
        jne loc_00414A5C
        fld  DWORD PTR [ecx+0x3c0]
        fcomp QWORD PTR ds:0x470d10
        fnstsw ax
        test  ah,0x5
        jp loc_00414A5C
        lea  eax,[edi+0x8398]
        mov  ecx,0x7
        jmp loc_004149F0
        nop
    loc_004149F0:
        mov  WORD PTR [eax],0x3
        add  eax,0x3ac
        dec  ecx
        jne loc_004149F0
        mov  eax,DWORD PTR [edi+0x9eb4]
        or   eax,0x1
        jmp loc_00414A56
    loc_00414A08:
        test  ecx,ecx
        je loc_00414A5C
        fld  DWORD PTR [ecx+0x3c4]
        fcomp DWORD PTR ds:0x470d08
        fnstsw ax
        test  ah,0x5
        jnp loc_00414A32
        fld  DWORD PTR [ecx+0x3c0]
        fcomp QWORD PTR ds:0x470d00
        fnstsw ax
        test  ah,0x41
        jne loc_00414A5C
    loc_00414A32:
        lea  eax,[edi+0x8398]
        mov  ecx,0x7
        nop
    loc_00414A40:
        mov  WORD PTR [eax],0x2
        add  eax,0x3ac
        dec  ecx
        jne loc_00414A40
        mov  eax,DWORD PTR [edi+0x9eb4]
        and  eax,0xfffffffe
    loc_00414A56:
        mov  DWORD PTR [edi+0x9eb4],eax
    loc_00414A5C:
        mov  edi,DWORD PTR [esp+0x18]
        mov  ebp,DWORD PTR ds:0x474c4c
        lea  ecx,[edi+0x8094]
        push  ecx
        mov  esi,0x2710
        call FUN_0043ee30
        add  edi,0x8440
        mov  ebx,0x5
    loc_00414A82:
        mov  eax,ebp
        cdq
        idiv  esi
        mov  ecx,DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [ecx+0x9ec8]
        mov  ebp,edx
        lea  edx,[eax+0x1e]
        mov  eax,edi
        call FUN_0043e5a0
        mov  eax,0x66666667
        imul  esi
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        push  edi
        mov  esi,eax
        call FUN_0043ee30
        add  edi,0x3ac
        dec  ebx
        jne loc_00414A82
        mov  edi,DWORD PTR [esp+0x18]
        lea  ecx,[edi+0x969c]
        push  ecx
        call FUN_0043ee30
        mov  eax,ds:0x477704
        test  eax,eax
        je loc_0041508C
        mov  eax,DWORD PTR [eax+0x10]
        test  eax,eax
        je loc_0041508C
        mov  ecx,DWORD PTR [edi+0x9eb8]
        test  ecx,ecx
        jne loc_0041508C
        mov  ecx,DWORD PTR [eax+0x23fc]
        mov  DWORD PTR [esp+0x10],ecx
        fild  DWORD PTR [esp+0x10]
        mov  DWORD PTR [edi+0x9e8c],ecx
        fidiv DWORD PTR [eax+0x2400]
        fst  DWORD PTR [edi+0x9e88]
        fcomp DWORD PTR [edi+0x9e84]
        fnstsw ax
        test  ah,0x41
        jne loc_00414B34
        fld  DWORD PTR [edi+0x9e84]
        fadd  DWORD PTR ds:0x470cf8
        fstp  DWORD PTR [edi+0x9e84]
    loc_00414B34:
        fld  DWORD PTR [edi+0x9e84]
        fcomp DWORD PTR [edi+0x9e88]
        fnstsw ax
        test  ah,0x41
        jne loc_00414B53
        mov  edx,DWORD PTR [edi+0x9e88]
        mov  DWORD PTR [edi+0x9e84],edx
    loc_00414B53:
        test  BYTE PTR [edi+0x9eb4],0x8
        mov  ecx,DWORD PTR ds:0x477834
        mov  esi,DWORD PTR ds:0x491c10
        fld  DWORD PTR [ecx+0x3c4]
        je loc_00414CAE
        fcomp DWORD PTR ds:0x470c28
        fnstsw ax
        test  ah,0x1
        je loc_00414B96
        fld  DWORD PTR [ecx+0x3c0]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x41
        jne loc_00414DEF
    loc_00414B96:
        mov  eax,DWORD PTR [edi+0x9e90]
        xor  ebx,ebx
        test  eax,eax
        jle loc_00414C1E
        lea  edx,[edi+0x9e28]
    loc_00414BA8:
        mov  ecx,DWORD PTR [edx]
        test  ecx,ecx
        je loc_00414C10
        mov  eax,DWORD PTR [esi+0x72dad4]
        test  eax,eax
        je loc_00414BC6
    loc_00414BB8:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_00414BE0
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00414BB8
    loc_00414BC6:
        mov  eax,DWORD PTR [esi+0x72dadc]
        test  eax,eax
        je loc_00414C10
    loc_00414BD0:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_00414BE0
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00414BD0
        jmp loc_00414C10
    loc_00414BE0:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_00414C10
        mov  ebp,DWORD PTR [eax+0x18]
        test  ebp,ebp
        mov  ecx,0x2
        mov  WORD PTR [eax+0x304],cx
        jne loc_00414C10
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00414C10
    loc_00414C00:
        mov  ebp,DWORD PTR [eax]
        mov  WORD PTR [ebp+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00414C00
    loc_00414C10:
        mov  eax,DWORD PTR [edi+0x9e90]
        inc  ebx
        add  edx,0x4
        cmp  ebx,eax
        jl loc_00414BA8
    loc_00414C1E:
        mov  ecx,DWORD PTR [edi+0x9e24]
        test  ecx,ecx
        je loc_00414CA0
        mov  eax,DWORD PTR [esi+0x72dad4]
        test  eax,eax
        je loc_00414C3F
    loc_00414C32:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_00414C6B
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00414C32
    loc_00414C3F:
        mov  eax,DWORD PTR [esi+0x72dadc]
        test  eax,eax
        je loc_00414CA0
        nop
    loc_00414C50:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_00414C6B
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00414C50
        mov  eax,DWORD PTR [edi+0x9eb4]
        and  eax,0xfffffff7
        jmp loc_00414DE9
    loc_00414C6B:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_00414CA0
        mov  edx,DWORD PTR [eax+0x18]
        test  edx,edx
        mov  ecx,0x2
        mov  WORD PTR [eax+0x304],cx
        jne loc_00414CA0
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00414CA0
        jmp loc_00414C90
        nop
    loc_00414C90:
        mov  edx,DWORD PTR [eax]
        mov  WORD PTR [edx+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00414C90
    loc_00414CA0:
        mov  eax,DWORD PTR [edi+0x9eb4]
        and  eax,0xfffffff7
        jmp loc_00414DE9
    loc_00414CAE:
        fcomp DWORD PTR ds:0x470bc8
        fnstsw ax
        test  ah,0x41
        jp loc_00414DEF
        fld  DWORD PTR [ecx+0x3c0]
        fcomp DWORD PTR ds:0x470b5c
        fnstsw ax
        test  ah,0x5
        jp loc_00414DEF
        mov  eax,DWORD PTR [edi+0x9e90]
        xor  ebx,ebx
        test  eax,eax
        jle loc_00414D6E
        lea  edx,[edi+0x9e28]
        nop
    loc_00414CF0:
        mov  ecx,DWORD PTR [edx]
        test  ecx,ecx
        je loc_00414D60
        mov  eax,DWORD PTR [esi+0x72dad4]
        test  eax,eax
        je loc_00414D0E
    loc_00414D00:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_00414D28
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00414D00
    loc_00414D0E:
        mov  eax,DWORD PTR [esi+0x72dadc]
        test  eax,eax
        je loc_00414D60
    loc_00414D18:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_00414D28
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00414D18
        jmp loc_00414D60
    loc_00414D28:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_00414D60
        mov  ebp,DWORD PTR [eax+0x18]
        test  ebp,ebp
        mov  ecx,0x3
        mov  WORD PTR [eax+0x304],cx
        jne loc_00414D60
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00414D60
        jmp loc_00414D50
        lea  ebx,[ebx+0x0]
    loc_00414D50:
        mov  ebp,DWORD PTR [eax]
        mov  WORD PTR [ebp+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00414D50
    loc_00414D60:
        mov  eax,DWORD PTR [edi+0x9e90]
        inc  ebx
        add  edx,0x4
        cmp  ebx,eax
        jl loc_00414CF0
    loc_00414D6E:
        mov  ecx,DWORD PTR [edi+0x9e24]
        test  ecx,ecx
        je loc_00414DE0
        mov  eax,DWORD PTR [esi+0x72dad4]
        test  eax,eax
        je loc_00414D8F
    loc_00414D82:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_00414DAF
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00414D82
    loc_00414D8F:
        mov  eax,DWORD PTR [esi+0x72dadc]
        test  eax,eax
        je loc_00414DE0
        nop
    loc_00414DA0:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_00414DAF
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00414DA0
        jmp loc_00414DE0
    loc_00414DAF:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_00414DE0
        mov  edx,DWORD PTR [eax+0x18]
        test  edx,edx
        mov  ecx,0x3
        mov  WORD PTR [eax+0x304],cx
        jne loc_00414DE0
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00414DE0
        nop
    loc_00414DD0:
        mov  edx,DWORD PTR [eax]
        mov  WORD PTR [edx+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00414DD0
    loc_00414DE0:
        mov  eax,DWORD PTR [edi+0x9eb4]
        or   eax,0x8
    loc_00414DE9:
        mov  DWORD PTR [edi+0x9eb4],eax
    loc_00414DEF:
        mov  eax,DWORD PTR [edi+0x9e24]
        test  eax,eax
        jne loc_00414F33
        mov  eax,ds:0x474c7c
        dec  eax
        cmp  eax,0x6
        mov  ebp,0x85
        ja loc_00414E87
        jmp  DWORD PTR [eax*4+0x4157e0]
        cmp  DWORD PTR ds:0x474c84,0x18
        jl loc_00414E87
        mov  ebp,0x86
        jmp loc_00414E87
        cmp  DWORD PTR ds:0x474c84,0x18
        jl loc_00414F33
        mov  ebp,0x87
        jmp loc_00414E87
        cmp  DWORD PTR ds:0x474c84,0x18
        jl loc_00414F33
        mov  ebp,0x88
        jmp loc_00414E87
        mov  edx,DWORD PTR ds:0x474c84
        xor  eax,eax
        cmp  edx,0x18
        setge al
        add  eax,0x89
        mov  ebp,eax
        jmp loc_00414E87
        mov  ebp,0x8b
        jmp loc_00414E87
        mov  ebp,0x8c
        jmp loc_00414E87
        mov  edx,DWORD PTR ds:0x474c84
        xor  ecx,ecx
        cmp  edx,0x18
        setge cl
        add  ecx,0x8c
        mov  ebp,ecx
    loc_00414E87:
        mov  edx,DWORD PTR [esp+0x18]
        mov  ebx,DWORD PTR [edx+0x9ec8]
        call FUN_00449950
        mov  edi,eax
        mov  ecx,DWORD PTR [edi+0x35c]
        or   ecx,0x40000000
        push  ebp
        mov  DWORD PTR [edi+0x35c],ecx
        push  edi
        mov  ecx,ebx
        mov  DWORD PTR [edi+0x20],0xf
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[edi+0x4]
        xor  ecx,ecx
        mov  DWORD PTR [eax],edi
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x8],ecx
        cmp  DWORD PTR [esi+0x72dad4],ecx
        jne loc_00414EDD
        mov  DWORD PTR [esi+0x72dad4],eax
        jmp loc_00414EF9
    loc_00414EDD:
        mov  ecx,DWORD PTR [esi+0x72dad8]
        mov  edx,DWORD PTR [ecx+0x4]
        test  edx,edx
        je loc_00414EF3
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x8],eax
    loc_00414EF3:
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [eax+0x8],ecx
    loc_00414EF9:
        mov  DWORD PTR [esi+0x72dad8],eax
        mov  ecx,DWORD PTR [esi+0x732454]
        inc  ecx
        mov  eax,ecx
        test  eax,eax
        mov  DWORD PTR [esi+0x732454],ecx
        jne loc_00414F19
        inc  eax
        mov  DWORD PTR [esi+0x732454],eax
    loc_00414F19:
        mov  eax,DWORD PTR [esi+0x732454]
        mov  edx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [edi],eax
        mov  ecx,DWORD PTR [esi+0x732454]
        mov  DWORD PTR [edx+0x9e24],ecx
        mov  edi,edx
    loc_00414F33:
        lea  edx,[edi+0x9e28]
        xor  ebx,ebx
        mov  DWORD PTR [esp+0x10],edx
        nop
    loc_00414F40:
        cmp  ebx,DWORD PTR [edi+0x9e90]
        jge loc_00414FFC
        cmp  DWORD PTR [edx],0x0
        jne loc_00415076
        mov  eax,DWORD PTR [esp+0x18]
        mov  ebp,DWORD PTR [eax+0x9ec8]
        call FUN_00449950
        mov  edi,eax
        or   DWORD PTR [edi+0x35c],0x40000000
        lea  ecx,[ebx+0x5b]
        push  ecx
        push  edi
        mov  ecx,ebp
        mov  DWORD PTR [edi+0x20],0xf
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[edi+0x4]
        xor  ecx,ecx
        mov  DWORD PTR [eax],edi
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x8],ecx
        cmp  DWORD PTR [esi+0x72dad4],ecx
        jne loc_00414FA6
        mov  DWORD PTR [esi+0x72dad4],eax
        jmp loc_00414FC2
    loc_00414FA6:
        mov  ecx,DWORD PTR [esi+0x72dad8]
        mov  edx,DWORD PTR [ecx+0x4]
        test  edx,edx
        je loc_00414FBC
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x8],eax
    loc_00414FBC:
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [eax+0x8],ecx
    loc_00414FC2:
        mov  DWORD PTR [esi+0x72dad8],eax
        mov  ecx,DWORD PTR [esi+0x732454]
        inc  ecx
        mov  eax,ecx
        test  eax,eax
        mov  DWORD PTR [esi+0x732454],ecx
        jne loc_00414FE2
        inc  eax
        mov  DWORD PTR [esi+0x732454],eax
    loc_00414FE2:
        mov  eax,DWORD PTR [esi+0x732454]
        mov  edx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [edi],eax
        mov  ecx,DWORD PTR [esi+0x732454]
        mov  edi,DWORD PTR [esp+0x18]
        mov  DWORD PTR [edx],ecx
        jmp loc_00415076
    loc_00414FFC:
        mov  ecx,DWORD PTR [edx]
        test  ecx,ecx
        je loc_00415076
        mov  eax,DWORD PTR [esi+0x72dad4]
        test  eax,eax
        je loc_0041501E
        nop
    loc_00415010:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_00415038
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415010
    loc_0041501E:
        mov  eax,DWORD PTR [esi+0x72dadc]
        test  eax,eax
        je loc_00415070
    loc_00415028:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_00415038
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415028
        jmp loc_00415070
    loc_00415038:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_00415070
        mov  ebp,DWORD PTR [eax+0x18]
        test  ebp,ebp
        mov  ecx,0x1
        mov  WORD PTR [eax+0x304],cx
        jne loc_00415070
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00415070
        jmp loc_00415060
        lea  ebx,[ebx+0x0]
    loc_00415060:
        mov  ebp,DWORD PTR [eax]
        mov  WORD PTR [ebp+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415060
    loc_00415070:
        mov  DWORD PTR [edx],0x0
    loc_00415076:
        inc  ebx
        add  edx,0x4
        cmp  ebx,0xa
        mov  DWORD PTR [esp+0x10],edx
        jb loc_00414F40
        jmp loc_0041513C
    loc_0041508C:
        mov  ecx,DWORD PTR [edi+0x9e24]
        test  ecx,ecx
        je loc_0041510A
        mov  edx,DWORD PTR ds:0x491c10
        mov  eax,DWORD PTR [edx+0x72dad4]
        test  eax,eax
        je loc_004150B3
    loc_004150A6:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_004150CF
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004150A6
    loc_004150B3:
        mov  eax,DWORD PTR [edx+0x72dadc]
        test  eax,eax
        je loc_00415100
        nop
    loc_004150C0:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_004150CF
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004150C0
        jmp loc_00415100
    loc_004150CF:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_00415100
        mov  edx,DWORD PTR [eax+0x18]
        test  edx,edx
        mov  ecx,0x1
        mov  WORD PTR [eax+0x304],cx
        jne loc_00415100
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00415100
        nop
    loc_004150F0:
        mov  edx,DWORD PTR [eax]
        mov  WORD PTR [edx+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004150F0
    loc_00415100:
        mov  DWORD PTR [edi+0x9e24],0x0
    loc_0041510A:
        mov  DWORD PTR [edi+0x9e84],0x0
        mov  DWORD PTR [edi+0x9e94],0x0
        mov  DWORD PTR [edi+0x9e9c],0x0
        mov  DWORD PTR [edi+0x9ea4],0x0
        mov  DWORD PTR [edi+0x9eac],0x0
    loc_0041513C:
        mov  esi,DWORD PTR [edi+0x9eb8]
        test  esi,esi
        je loc_0041549A
        push  esi
        call FUN_00415e90
        test  eax,eax
        jne loc_004151A5
        mov  edx,DWORD PTR [esi+0x8]
        mov  ecx,DWORD PTR [esi+0x10]
        mov  DWORD PTR [esi+0x4],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00415190
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00415190
        fld  DWORD PTR [esi+0xc]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x8],edx
        fstp  DWORD PTR [esi+0xc]
        jmp loc_0041549A
    loc_00415190:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [esi+0xc]
        fst  DWORD PTR [esi+0xc]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x8],eax
        jmp loc_0041549A
    loc_004151A5:
        mov  ebx,DWORD PTR [edi+0x9eb8]
        test  ebx,ebx
        je loc_00415490
        mov  ecx,DWORD PTR [ebx+0x40]
        test  ecx,ecx
        mov  edx,DWORD PTR ds:0x491c10
        mov  esi,0x4000000
        je loc_0041522F
        mov  eax,DWORD PTR [edx+0x72dad4]
        test  eax,eax
        je loc_004151DE
        nop
    loc_004151D0:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_004151F8
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004151D0
    loc_004151DE:
        mov  eax,DWORD PTR [edx+0x72dadc]
        test  eax,eax
        je loc_0041522F
    loc_004151E8:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_004151F8
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004151E8
        jmp loc_0041522F
    loc_004151F8:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_0041522F
        mov  ebp,DWORD PTR [eax+0x35c]
        mov  ecx,DWORD PTR [eax+0x18]
        or   ebp,esi
        test  ecx,ecx
        mov  DWORD PTR [eax+0x35c],ebp
        jne loc_0041522F
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_0041522F
        lea  ebx,[ebx+0x0]
    loc_00415220:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],esi
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415220
    loc_0041522F:
        mov  DWORD PTR [ebx+0x40],0x0
        mov  ecx,DWORD PTR [ebx+0x44]
        test  ecx,ecx
        je loc_004152A1
        mov  eax,DWORD PTR [edx+0x72dad4]
        test  eax,eax
        je loc_00415255
    loc_00415247:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_00415270
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415247
    loc_00415255:
        mov  eax,DWORD PTR [edx+0x72dadc]
        test  eax,eax
        je loc_004152A1
        nop
    loc_00415260:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_00415270
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415260
        jmp loc_004152A1
    loc_00415270:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_004152A1
        mov  ebp,DWORD PTR [eax+0x35c]
        mov  ecx,DWORD PTR [eax+0x18]
        or   ebp,esi
        test  ecx,ecx
        mov  DWORD PTR [eax+0x35c],ebp
        jne loc_004152A1
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_004152A1
    loc_00415292:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],esi
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415292
    loc_004152A1:
        mov  DWORD PTR [ebx+0x44],0x0
        mov  ecx,DWORD PTR [ebx+0x48]
        test  ecx,ecx
        je loc_0041531F
        mov  eax,DWORD PTR [edx+0x72dad4]
        test  eax,eax
        je loc_004152CE
        nop
    loc_004152C0:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_004152E8
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004152C0
    loc_004152CE:
        mov  eax,DWORD PTR [edx+0x72dadc]
        test  eax,eax
        je loc_0041531F
    loc_004152D8:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_004152E8
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004152D8
        jmp loc_0041531F
    loc_004152E8:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_0041531F
        mov  ebp,DWORD PTR [eax+0x35c]
        mov  ecx,DWORD PTR [eax+0x18]
        or   ebp,esi
        test  ecx,ecx
        mov  DWORD PTR [eax+0x35c],ebp
        jne loc_0041531F
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_0041531F
        lea  ebx,[ebx+0x0]
    loc_00415310:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],esi
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415310
    loc_0041531F:
        mov  DWORD PTR [ebx+0x48],0x0
        mov  ecx,DWORD PTR [ebx+0x4c]
        test  ecx,ecx
        je loc_00415391
        mov  eax,DWORD PTR [edx+0x72dad4]
        test  eax,eax
        je loc_00415345
    loc_00415337:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_00415360
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415337
    loc_00415345:
        mov  eax,DWORD PTR [edx+0x72dadc]
        test  eax,eax
        je loc_00415391
        nop
    loc_00415350:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_00415360
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415350
        jmp loc_00415391
    loc_00415360:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_00415391
        mov  ebp,DWORD PTR [eax+0x35c]
        mov  ecx,DWORD PTR [eax+0x18]
        or   ebp,esi
        test  ecx,ecx
        mov  DWORD PTR [eax+0x35c],ebp
        jne loc_00415391
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00415391
    loc_00415382:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],esi
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415382
    loc_00415391:
        mov  DWORD PTR [ebx+0x4c],0x0
        mov  ecx,DWORD PTR [ebx+0x50]
        test  ecx,ecx
        je loc_0041540F
        mov  eax,DWORD PTR [edx+0x72dad4]
        test  eax,eax
        je loc_004153BE
        nop
    loc_004153B0:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_004153D8
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004153B0
    loc_004153BE:
        mov  eax,DWORD PTR [edx+0x72dadc]
        test  eax,eax
        je loc_0041540F
    loc_004153C8:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_004153D8
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004153C8
        jmp loc_0041540F
    loc_004153D8:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_0041540F
        mov  ebp,DWORD PTR [eax+0x35c]
        mov  ecx,DWORD PTR [eax+0x18]
        or   ebp,esi
        test  ecx,ecx
        mov  DWORD PTR [eax+0x35c],ebp
        jne loc_0041540F
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_0041540F
        lea  ebx,[ebx+0x0]
    loc_00415400:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],esi
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415400
    loc_0041540F:
        mov  DWORD PTR [ebx+0x50],0x0
        mov  ecx,DWORD PTR [ebx+0x54]
        test  ecx,ecx
        je loc_00415480
        mov  eax,DWORD PTR [edx+0x72dad4]
        test  eax,eax
        je loc_00415435
    loc_00415427:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_0041544F
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415427
    loc_00415435:
        mov  eax,DWORD PTR [edx+0x72dadc]
        test  eax,eax
        je loc_00415480
        nop
    loc_00415440:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_0041544F
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415440
        jmp loc_00415480
    loc_0041544F:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_00415480
        mov  edx,DWORD PTR [eax+0x35c]
        mov  ecx,DWORD PTR [eax+0x18]
        or   edx,esi
        test  ecx,ecx
        mov  DWORD PTR [eax+0x35c],edx
        jne loc_00415480
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00415480
    loc_00415471:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],esi
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00415471
    loc_00415480:
        push  ebx
        mov  DWORD PTR [ebx+0x54],0x0
        call _free
        add  esp,0x4
    loc_00415490:
        mov  DWORD PTR [edi+0x9eb8],0x0
    loc_0041549A:
        mov  ecx,DWORD PTR ds:0x477704
        test  ecx,ecx
        je loc_00415764
        mov  eax,DWORD PTR [edi+0x9ec0]
        test  eax,eax
        jl loc_004155BA
        mov  edx,DWORD PTR [ecx+0x10]
        test  edx,edx
        je loc_004155BA
        mov  edx,DWORD PTR [edi+0x9eb8]
        test  edx,edx
        jne loc_004155BA
        mov  ecx,DWORD PTR [edi+0x9ec4]
        cmp  eax,ecx
        jge loc_0041553F
        cmp  eax,0x5
        jg loc_0041550C
        mov  eax,DWORD PTR [esp+0x18]
        mov  ecx,0x9
        mov  WORD PTR [eax+0x7c40],cx
        mov  WORD PTR [eax+0x7fec],cx
        push  0x0
        mov  edi,0x24
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  edi,DWORD PTR [esp+0x18]
        jmp loc_00415554
    loc_0041550C:
        cmp  eax,0xa
        jg loc_00415554
        mov  eax,DWORD PTR [esp+0x18]
        mov  ecx,0x8
        mov  WORD PTR [eax+0x7c40],cx
        mov  WORD PTR [eax+0x7fec],cx
        push  0x0
        mov  edi,0x1b
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  edi,DWORD PTR [esp+0x18]
        jmp loc_00415554
    loc_0041553F:
        jle loc_00415554
        mov  eax,0x7
        mov  WORD PTR [edi+0x7c40],ax
        mov  WORD PTR [edi+0x7fec],ax
    loc_00415554:
        mov  ecx,DWORD PTR [edi+0x9ec0]
        cmp  ecx,DWORD PTR [edi+0x9ec4]
        je loc_004155A8
        mov  eax,0x66666667
        imul  ecx
        mov  ecx,DWORD PTR [edi+0x9ec8]
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x8]
        lea  eax,[edi+0x793c]
        call FUN_0043e5a0
        mov  eax,DWORD PTR [edi+0x9ec0]
        cdq
        mov  ecx,0xa
        idiv  ecx
        mov  ecx,DWORD PTR [edi+0x9ec8]
        lea  eax,[edi+0x7ce8]
        add  edx,0x8
        call FUN_0043e5a0
    loc_004155A8:
        mov  edx,DWORD PTR [edi+0x9ec0]
        mov  ecx,DWORD PTR ds:0x477704
        mov  DWORD PTR [edi+0x9ec4],edx
    loc_004155BA:
        mov  esi,DWORD PTR [ecx+0x10]
        test  esi,esi
        je loc_00415764
        mov  eax,DWORD PTR [esi+0x2480]
        mov  ecx,eax
        shr  ecx,0x4
        not  ecx
        test  cl,0x1
        je loc_00415764
        not  eax
        test  al,0x1
        je loc_00415764
        mov  edx,DWORD PTR ds:0x4776f4
        test  BYTE PTR [edx+0x378c],0x1
        mov  eax,DWORD PTR [edi+0x9eb4]
        mov  ecx,eax
        je loc_00415646
        shr  ecx,1
        and  ecx,0x3
        jne loc_0041560F
        cmp  DWORD PTR [esi+0x2404],0x7d0
        jmp loc_00415657
    loc_0041560F:
        cmp  ecx,0x1
        jne loc_00415620
        cmp  DWORD PTR [esi+0x2404],0x3e8
        jmp loc_00415679
    loc_00415620:
        cmp  ecx,0x2
        jne loc_00415631
        cmp  DWORD PTR [esi+0x2404],0x190
        jmp loc_0041569B
    loc_00415631:
        cmp  ecx,0x3
        jne loc_004156CE
        cmp  DWORD PTR [esi+0x2404],0x190
        jmp loc_004156BA
    loc_00415646:
        shr  ecx,1
        and  ecx,0x3
        jne loc_0041566A
        cmp  DWORD PTR [esi+0x2404],0x2bc
    loc_00415657:
        jge loc_004156CE
        and  eax,0xfffffffb
        mov  WORD PTR [edi+0x9d4c],0x7
        or   eax,0x2
        jmp loc_004156C8
    loc_0041566A:
        cmp  ecx,0x1
        jne loc_0041568C
        cmp  DWORD PTR [esi+0x2404],0x190
    loc_00415679:
        jge loc_004156CE
        and  eax,0xfffffffd
        mov  WORD PTR [edi+0x9d4c],0x8
        or   eax,0x4
        jmp loc_004156C8
    loc_0041568C:
        cmp  ecx,0x2
        jne loc_004156AB
        cmp  DWORD PTR [esi+0x2404],0xc8
    loc_0041569B:
        jge loc_004156CE
        mov  WORD PTR [edi+0x9d4c],0x9
        or   eax,0x6
        jmp loc_004156C8
    loc_004156AB:
        cmp  ecx,0x3
        jne loc_004156CE
        cmp  DWORD PTR [esi+0x2404],0xc8
    loc_004156BA:
        jle loc_004156CE
        mov  WORD PTR [edi+0x9d4c],0xa
        and  eax,0xfffffff9
    loc_004156C8:
        mov  DWORD PTR [edi+0x9eb4],eax
    loc_004156CE:
        lea  eax,[edi+0x9a48]
        push  eax
        call FUN_0043ee30
        fld  DWORD PTR [esi+0x1068]
        fadd  DWORD PTR ds:0x470b4c
        mov  ecx,DWORD PTR ds:0x477834
        mov  DWORD PTR [edi+0x9d8c],0x43f00000
        fstp  DWORD PTR [edi+0x9d88]
        fld  DWORD PTR [esi+0x1068]
        fsub  DWORD PTR [ecx+0x3c0]
        fabs
        fcom  QWORD PTR ds:0x470cf0
        fnstsw ax
        test  ah,0x1
        jne loc_00415722
        fstp  st(0)
        mov  BYTE PTR [edi+0x9d47],0xff
        jmp loc_00415737
    loc_00415722:
        fmul  DWORD PTR ds:0x470ce8
        call FUN_00463b2c
        mov  dl,0x40
        sub  dl,al
        mov  BYTE PTR [edi+0x9d47],dl
    loc_00415737:
        fld  DWORD PTR [esi+0x1068]
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x5
        jnp loc_0041575D
        fld  DWORD PTR [esi+0x1068]
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        test  ah,0x41
        jne loc_00415764
    loc_0041575D:
        mov  BYTE PTR [edi+0x9d47],0x0
    loc_00415764:
        mov  edx,DWORD PTR [edi+0x9e64]
        mov  ecx,DWORD PTR [edi+0x9e6c]
        mov  DWORD PTR [edi+0x9e60],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        pop  esi
        pop  ebp
        pop  ebx
        fnstsw ax
        test  ah,0x41
        jne loc_004157BA
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_004157BA
        fld  DWORD PTR [edi+0x9e68]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [edi+0x9e64],edx
        mov  eax,0x1
        fstp  DWORD PTR [edi+0x9e68]
        pop  edi
        pop  ecx
        ret  0x4
    loc_004157BA:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [edi+0x9e68]
        fst  DWORD PTR [edi+0x9e68]
        call FUN_00463b2c
        mov  DWORD PTR [edi+0x9e64],eax
        mov  eax,0x1
        pop  edi
        pop  ecx
        ret  0x4
        nop
        adc  al,0x4e
        inc  ecx
        add  BYTE PTR [esi+ecx*2],ah
        inc  ecx
        add  BYTE PTR [eax],bh
        dec  esi
        inc  ecx
        add  BYTE PTR [esi+ecx*2+0x41],cl
        add  BYTE PTR [ebx+0x4e],ah
        inc  ecx
        add  BYTE PTR [edx+0x4e],ch
        inc  ecx
        add  BYTE PTR [ecx+0x4e],dh
        inc  ecx
        add  ah,cl
    }
}
