// 0041AFD0: FUN_0041afd0
// Original size: 2688 bytes, actual code: 702 instructions
extern "C" void FUN_00404f30(void);
extern "C" void FUN_004054b0(void);
extern "C" void FUN_00405b60(void);
extern "C" void FUN_00409d90(void);
extern "C" void FUN_00412ff0(void);
extern "C" void FUN_004188a0(void);
extern "C" void FUN_00418930(void);
extern "C" void FUN_0041ba50(void);
extern "C" void FUN_0041be80(void);
extern "C" void FUN_0041beb0(void);
extern "C" void FUN_00426660(void);
extern "C" void FUN_00426f70(void);
extern "C" void FUN_0042b9c0(void);
extern "C" void FUN_0043dd10(void);
extern "C" void FUN_0043e5a0(void);
extern "C" void FUN_0043ee30(void);
extern "C" void FUN_004451c0(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0041afd0(void) {
    __asm {
        sub  esp,0x58
        mov  eax,DWORD PTR [esp+0x5c]
        push  ebx
        push  ebp
        push  esi
        xor  ecx,ecx
        lea  esi,[eax+0x14]
        push  edi
        mov  DWORD PTR [esp+0x10],esi
        mov  DWORD PTR [esp+0x14],ecx
        mov  DWORD PTR [eax+0x21cebc],ecx
        mov  DWORD PTR [eax+0x21ceb4],ecx
        lea  ebp,[esi+0x3b0]
        mov  DWORD PTR [esp+0x1c],0x896
        jmp loc_0041B010
    loc_0041B004:
        xor  ecx,ecx
        jmp loc_0041B010
        nop
        nop
    loc_0041B010:
        mov  eax,DWORD PTR [ebp+0x2c]
        cmp  eax,ecx
        je loc_0041B85A
        cmp  eax,0x5
        jne loc_0041B04F
        dec  DWORD PTR [ebp+0x3c]
        jns loc_0041B85A
        mov  ecx,DWORD PTR ds:0x4776f0
        mov  eax,DWORD PTR [ebp+0x30]
        mov  DWORD PTR [ebp+0x2c],0x2
        mov  edx,DWORD PTR [ecx+0x3e0b50]
        add  eax,0x176
        push  edx
        call FUN_00404f30
        jmp loc_0041B85A
    loc_0041B04F:
        mov  ebx,0x1
        cmp  eax,ebx
        jne loc_0041B133
        mov  edx,DWORD PTR ds:0x477834
        mov  eax,DWORD PTR [edx+0x458]
        cmp  eax,0x2
        je loc_0041B085
        cmp  eax,0x4
        je loc_0041B085
        fld  DWORD PTR [edx+0x3c4]
        fcomp DWORD PTR ds:0x470bf4
        fnstsw ax
        test  ah,0x5
        jnp loc_0041B08F
    loc_0041B085:
        mov  eax,ds:0x4776ec
        cmp  DWORD PTR [eax+0x28],ecx
        je loc_0041B0A7
    loc_0041B08F:
        mov  ecx,DWORD PTR [edx+0x45c]
        mov  eax,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [ebp+0x38],eax
        mov  DWORD PTR [ebp+0x2c],0x3
        jmp loc_0041B1E7
    loc_0041B0A7:
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x8]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0xc]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x10]
        fstp  DWORD PTR [esp+0x40]
        fxch  st(1)
        fadd  DWORD PTR [ebp-0x4]
        fstp  DWORD PTR [ebp-0x4]
        fadd  DWORD PTR [ebp+0x0]
        fstp  DWORD PTR [ebp+0x0]
        fld  DWORD PTR [esp+0x40]
        fadd  DWORD PTR [ebp+0x4]
        fstp  DWORD PTR [ebp+0x4]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR ds:0x470cdc
        fadd  DWORD PTR [ebp+0xc]
        fst  DWORD PTR [ebp+0xc]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x1
        jne loc_0041B100
        mov  DWORD PTR [ebp+0x8],ecx
    loc_0041B100:
        fld  DWORD PTR [ebp+0xc]
        fcomp DWORD PTR ds:0x470b08
        fnstsw ax
        test  ah,0x41
        jne loc_0041B117
        mov  DWORD PTR [ebp+0xc],0x40000000
    loc_0041B117:
        fld  DWORD PTR [ebp+0x0]
        fcomp DWORD PTR ds:0x470be0
        fnstsw ax
        test  ah,0x41
        jne loc_0041B347
        mov  DWORD PTR [ebp+0x2c],ecx
        jmp loc_0041B85A
    loc_0041B133:
        cmp  eax,0x2
        jne loc_0041B1D8
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x8]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0xc]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x10]
        fstp  DWORD PTR [esp+0x4c]
        fxch  st(1)
        fadd  DWORD PTR [ebp-0x4]
        fstp  DWORD PTR [ebp-0x4]
        fadd  DWORD PTR [ebp+0x0]
        fstp  DWORD PTR [ebp+0x0]
        fld  DWORD PTR [esp+0x4c]
        fadd  DWORD PTR [ebp+0x4]
        fstp  DWORD PTR [ebp+0x4]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR ds:0x470cdc
        fadd  DWORD PTR [ebp+0xc]
        fst  DWORD PTR [ebp+0xc]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x1
        jne loc_0041B1AD
        mov  ecx,DWORD PTR ds:0x477834
        mov  edx,DWORD PTR [ecx+0x45c]
        mov  eax,DWORD PTR [edx+0x8]
        mov  DWORD PTR [ebp+0x38],eax
        mov  DWORD PTR [ebp+0x2c],0x3
        jmp loc_0041B1E1
    loc_0041B1AD:
        fld  DWORD PTR [ebp+0x0]
        fcomp DWORD PTR ds:0x470be0
        fnstsw ax
        test  ah,0x41
        jne loc_0041B341
        mov  DWORD PTR [ebp+0x2c],ecx
        mov  ecx,0xfffffffc
        mov  eax,0x474c40
        call FUN_00405b60
        jmp loc_0041B85A
    loc_0041B1D8:
        cmp  eax,0x3
        jne loc_0041B2A1
    loc_0041B1E1:
        mov  edx,DWORD PTR ds:0x477834
    loc_0041B1E7:
        fld  DWORD PTR [edx+0x3c0]
        fsub  DWORD PTR [ebp-0x4]
        fld  DWORD PTR [edx+0x3c4]
        fsub  DWORD PTR [ebp+0x0]
        fld  DWORD PTR ds:0x470b04
        fld  st(1)
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0041B229
        fld  DWORD PTR ds:0x470b04
        fld  st(2)
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0041B229
        fstp  st(0)
        mov  DWORD PTR [esp+0x18],0x3fc90fdb
        fstp  st(0)
        jmp loc_0041B231
    loc_0041B229:
        fxch  st(1)
        fpatan
        fstp  DWORD PTR [esp+0x18]
    loc_0041B231:
        mov  ecx,DWORD PTR [ebp+0x38]
        mov  eax,DWORD PTR [esp+0x18]
        push  ecx
        lea  edi,[ebp+0x8]
        push  eax
        mov  ecx,edi
        call FUN_0041beb0
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [edi]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0xc]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x10]
        fstp  DWORD PTR [esp+0x58]
        fxch  st(1)
        fadd  DWORD PTR [ebp-0x4]
        fstp  DWORD PTR [ebp-0x4]
        fadd  DWORD PTR [ebp+0x0]
        fstp  DWORD PTR [ebp+0x0]
        fld  DWORD PTR [esp+0x58]
        fadd  DWORD PTR [ebp+0x4]
        fstp  DWORD PTR [ebp+0x4]
        fld  DWORD PTR [ebp+0x38]
        fcomp DWORD PTR ds:0x470cd8
        fnstsw ax
        test  ah,0x5
        jp loc_0041B296
        fld  DWORD PTR [ebp+0x38]
        fadd  DWORD PTR ds:0x470c38
        fstp  DWORD PTR [ebp+0x38]
    loc_0041B296:
        mov  eax,DWORD PTR [edx+0x458]
        jmp loc_0041B32A
    loc_0041B2A1:
        cmp  eax,0x4
        jne loc_0041B341
        mov  ecx,DWORD PTR [ebp+0x38]
        mov  esi,DWORD PTR ds:0x477834
        lea  edx,[ebp-0x4]
        push  ecx
        mov  eax,edx
        mov  ecx,esi
        lea  edi,[ebp+0x8]
        call FUN_00426660
        push  ecx
        mov  ecx,edi
        fstp  DWORD PTR [esp]
        call FUN_0041beb0
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [edi]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0xc]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x10]
        fstp  DWORD PTR [esp+0x64]
        fxch  st(1)
        fadd  DWORD PTR [edx]
        fstp  DWORD PTR [edx]
        fadd  DWORD PTR [ebp+0x0]
        fstp  DWORD PTR [ebp+0x0]
        fld  DWORD PTR [esp+0x64]
        fadd  DWORD PTR [ebp+0x4]
        fstp  DWORD PTR [ebp+0x4]
        fld  DWORD PTR [ebp+0x38]
        fcomp DWORD PTR ds:0x470cd8
        fnstsw ax
        test  ah,0x5
        jp loc_0041B31E
        fld  DWORD PTR [ebp+0x38]
        fadd  DWORD PTR ds:0x470c38
        fstp  DWORD PTR [ebp+0x38]
    loc_0041B31E:
        mov  eax,DWORD PTR [esi+0x458]
        mov  edx,DWORD PTR ds:0x477834
    loc_0041B32A:
        cmp  eax,0x4
        jne loc_0041B347
        mov  DWORD PTR [ebp+0x2c],ebx
        mov  DWORD PTR [edi],0x0
        mov  DWORD PTR [ebp+0xc],0x0
        jmp loc_0041B347
    loc_0041B341:
        mov  edx,DWORD PTR ds:0x477834
    loc_0041B347:
        cmp  DWORD PTR [edx+0x458],0x2
        je loc_0041B7FD
        mov  eax,DWORD PTR [ebp-0x4]
        fld  DWORD PTR [edx+0x4324]
        mov  ecx,DWORD PTR [ebp+0x0]
        lea  edi,[ebp-0x4]
        mov  DWORD PTR [esp+0x20],eax
        fcomp DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x2c],eax
        mov  DWORD PTR [esp+0x30],ecx
        mov  DWORD PTR [esp+0x24],ecx
        fnstsw ax
        test  ah,0x41
        je loc_0041B737
        fld  DWORD PTR [edx+0x4328]
        fcomp DWORD PTR [esp+0x24]
        fnstsw ax
        test  ah,0x41
        je loc_0041B737
        fld  DWORD PTR [edx+0x4330]
        fcomp DWORD PTR [esp+0x2c]
        fnstsw ax
        test  ah,0x5
        jnp loc_0041B737
        fld  DWORD PTR [edx+0x4334]
        fcomp DWORD PTR [esp+0x30]
        fnstsw ax
        test  ah,0x5
        jnp loc_0041B737
        mov  eax,DWORD PTR [ebp+0x30]
        dec  eax
        cmp  eax,0xa
        ja loc_0041B718
        jmp  DWORD PTR [eax*4+0x41b8a0]
        push  ebx
        mov  eax,0x474c40
        call FUN_00418930
        mov  ebx,eax
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
        test  ebx,ebx
        je loc_0041B47D
        mov  ecx,DWORD PTR ds:0x477834
        push  ecx
        call FUN_00426f70
        mov  esi,DWORD PTR ds:0x477840
        push  0xffffff40
        or   eax,0xffffffff
        call FUN_0042b9c0
        mov  edx,DWORD PTR [ebp-0x4]
        push  edx
        mov  ebx,0x1d
        mov  esi,0x492590
        call FUN_0043dd10
        cmp  WORD PTR ds:0x474c48,0x64
        jl loc_0041B45D
        mov  DWORD PTR [esp+0x14],0x1
    loc_0041B45D:
        mov  ecx,0xc
        mov  eax,0x474c40
        call FUN_00405b60
        push  0x3c
        mov  edi,0x474c40
        call FUN_00412ff0
        jmp loc_0041B718
    loc_0041B47D:
        movsx eax,WORD PTR ds:0x474c48
        mov  esi,DWORD PTR ds:0x477840
        cdq
        sub  eax,edx
        push  0xffff4040
        sar  eax,1
        call FUN_0042b9c0
        push  0x3c
        mov  edi,0x474c40
        call FUN_00412ff0
        jmp loc_0041B718
        fld  DWORD PTR [edx+0x3c4]
        fcomp DWORD PTR ds:0x470cd4
        fnstsw ax
        test  ah,0x5
        jp loc_0041B4D5
        mov  eax,ds:0x474c4c
        lea  ebx,[eax+eax*4]
        shl  ebx,1
        mov  eax,ebx
        cdq
        mov  ecx,0xa
        idiv  ecx
        sub  ebx,edx
        jmp loc_0041B542
    loc_0041B4D5:
        fld  DWORD PTR [edx+0x3c4]
        fsub  DWORD PTR ds:0x470cd4
        fmul  DWORD PTR ds:0x470cd0
        fild  DWORD PTR ds:0x474c4c
        fmul  DWORD PTR ds:0x470b0c
        fsub  DWORD PTR ds:0x470ce0
        fmulp st(1),st
        call FUN_00463b2c
        mov  ecx,eax
        mov  eax,ds:0x474c4c
        lea  eax,[eax+eax*4]
        shl  eax,1
        cdq
        sub  eax,edx
        mov  ebx,eax
        sar  ebx,1
        sub  ebx,ecx
        mov  eax,ebx
        cdq
        mov  ecx,0xa
        idiv  ecx
        mov  esi,DWORD PTR ds:0x477840
        push  0xffffffff
        sub  ebx,edx
        mov  eax,ebx
        call FUN_0042b9c0
        mov  ecx,0x1
        jmp loc_0041B559
        mov  ebx,DWORD PTR ds:0x474c4c
        lea  ebx,[ebx+ebx*4]
        shl  ebx,1
    loc_0041B542:
        mov  esi,DWORD PTR ds:0x477840
        mov  eax,ebx
        push  0xffffff00
        call FUN_0042b9c0
        mov  ecx,0x8
    loc_0041B559:
        mov  eax,0x474c40
        call FUN_00405b60
        push  ebx
        mov  ecx,0x474c40
        call FUN_00409d90
        push  0x64
        mov  edi,0x474c40
        call FUN_00412ff0
        jmp loc_0041B718
        mov  eax,ds:0x474c74
        cmp  eax,0x4
        mov  ebx,0x1388
        ja loc_0041B5A8
        jmp  DWORD PTR [eax*4+0x41b8cc]
        mov  ebx,0x1388
        jmp loc_0041B5A8
        mov  ebx,0x1f40
        jmp loc_0041B5A8
        mov  ebx,0x2710
    loc_0041B5A8:
        mov  esi,DWORD PTR ds:0x477840
        push  0xff00ff00
        mov  eax,ebx
        call FUN_0042b9c0
        push  ebx
        mov  ecx,0x474c40
        call FUN_0041be80
        push  0x78
        mov  edi,0x474c40
        call FUN_00412ff0
        jmp loc_0041B718
        push  0xa
        mov  ecx,0x474c40
        call FUN_0041be80
        push  0x3
        mov  edi,0x474c40
        call FUN_00412ff0
        push  0xa
        mov  ecx,edi
        call FUN_00409d90
        jmp loc_0041B718
        mov  esi,DWORD PTR ds:0x477840
        push  0xff00ff00
        mov  eax,0x64
        call FUN_0042b9c0
        push  0x64
        mov  ecx,0x474c40
        call FUN_0041be80
        push  0x3c
        mov  edi,0x474c40
        call FUN_00412ff0
        jmp loc_0041B718
        push  0x14
        mov  eax,0x474c40
        call FUN_00418930
        mov  ebx,eax
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
        test  ebx,ebx
        je loc_0041B6D3
        mov  ecx,DWORD PTR ds:0x477834
        push  ecx
        call FUN_00426f70
        mov  edx,DWORD PTR [edi]
        push  edx
        mov  ebx,0x1d
        mov  esi,0x492590
        call FUN_0043dd10
        mov  esi,DWORD PTR ds:0x477840
        push  0xffffff40
        or   eax,0xffffffff
        call FUN_0042b9c0
        mov  ecx,0x18
        mov  eax,0x474c40
        call FUN_00405b60
        cmp  WORD PTR ds:0x474c48,0x64
        jl loc_0041B6EF
        push  0x14
        mov  edi,0x474c40
        mov  DWORD PTR [esp+0x18],0x1
        call FUN_00412ff0
        jmp loc_0041B718
    loc_0041B6D3:
        movsx eax,WORD PTR ds:0x474c48
        mov  esi,DWORD PTR ds:0x477840
        cdq
        sub  eax,edx
        push  0xffff4040
        sar  eax,1
        call FUN_0042b9c0
    loc_0041B6EF:
        push  0x14
        mov  edi,0x474c40
        call FUN_00412ff0
        jmp loc_0041B718
        mov  ecx,ebx
        mov  eax,0x474c40
        call FUN_004188a0
        mov  ecx,0x100
        mov  eax,0x474c40
        call FUN_00405b60
    loc_0041B718:
        mov  eax,DWORD PTR [ebp-0x4]
        push  eax
        mov  ebx,0x14
        mov  esi,0x492590
        mov  DWORD PTR [ebp+0x2c],0x0
        call FUN_0043dd10
        jmp loc_0041B85A
    loc_0041B737:
        mov  eax,DWORD PTR [ebp+0x2c]
        cmp  eax,0x4
        je loc_0041B7FD
        cmp  eax,0x3
        je loc_0041B7FD
        mov  ecx,DWORD PTR ds:0x474e5c
        and  ecx,0x4
        je loc_0041B79B
        fld  DWORD PTR [edx+0x433c]
        fcomp DWORD PTR [esp+0x20]
        fnstsw ax
        test  ah,0x41
        je loc_0041B79B
        fld  DWORD PTR [edx+0x4340]
        fcomp DWORD PTR [esp+0x24]
        fnstsw ax
        test  ah,0x41
        je loc_0041B79B
        fld  DWORD PTR [edx+0x4348]
        fcomp DWORD PTR [esp+0x2c]
        fnstsw ax
        test  ah,0x5
        jnp loc_0041B79B
        fld  DWORD PTR [edx+0x434c]
        fcomp DWORD PTR [esp+0x30]
        fnstsw ax
        test  ah,0x5
        jp loc_0041B7E4
    loc_0041B79B:
        test  cx,cx
        jne loc_0041B7FD
        fld  DWORD PTR [edx+0x4354]
        fcomp DWORD PTR [esp+0x20]
        fnstsw ax
        test  ah,0x41
        je loc_0041B7FD
        fld  DWORD PTR [edx+0x4358]
        fcomp DWORD PTR [esp+0x24]
        fnstsw ax
        test  ah,0x41
        je loc_0041B7FD
        fld  DWORD PTR [edx+0x4360]
        fcomp DWORD PTR [esp+0x2c]
        fnstsw ax
        test  ah,0x5
        jnp loc_0041B7FD
        fld  DWORD PTR [edx+0x4364]
        fcomp DWORD PTR [esp+0x30]
        fnstsw ax
        test  ah,0x5
        jnp loc_0041B7FD
    loc_0041B7E4:
        mov  ecx,DWORD PTR [edx+0x45c]
        fld  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [ebp+0x2c],0x4
        fmul  DWORD PTR ds:0x470cc4
        fstp  DWORD PTR [ebp+0x38]
    loc_0041B7FD:
        mov  edx,DWORD PTR [esp+0x10]
        push  edx
        call FUN_0043ee30
        mov  edx,DWORD PTR [ebp+0x1c]
        mov  ecx,DWORD PTR [ebp+0x24]
        mov  DWORD PTR [ebp+0x18],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_0041B840
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0041B840
        fld  DWORD PTR [ebp+0x20]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [ebp+0x1c],edx
        fstp  DWORD PTR [ebp+0x20]
        jmp loc_0041B850
    loc_0041B840:
        fld  DWORD PTR [ebp+0x20]
        fadd  DWORD PTR [ecx]
        fst  DWORD PTR [ebp+0x20]
        call FUN_00463b2c
        mov  DWORD PTR [ebp+0x1c],eax
    loc_0041B850:
        mov  eax,DWORD PTR [esp+0x6c]
        inc  DWORD PTR [eax+0x21ceb4]
    loc_0041B85A:
        mov  esi,DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [esp+0x1c]
        add  esi,0x3f0
        add  ebp,0x3f0
        dec  eax
        mov  DWORD PTR [esp+0x10],esi
        mov  DWORD PTR [esp+0x1c],eax
        jne loc_0041B004
        mov  eax,DWORD PTR [esp+0x14]
        test  eax,eax
        je loc_0041B88E
        mov  esi,DWORD PTR [esp+0x6c]
        call FUN_0041ba50
    loc_0041B88E:
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        add  esp,0x58
        ret  0x4
        nop
        aad  0xb3
        inc  ecx
        add  BYTE PTR [edx+0x7f0041b4],ch
        mov  ch,0x41
        add  BYTE PTR [esi],ch
        mov  dh,0x41
        add  BYTE PTR [edi],dh
        mov  ch,0x41
        add  BYTE PTR [eax],bl
        mov  bh,0x41
        add  ch,bh
        mov  dh,0x41
        add  dh,dl
        mov  ch,0x41
        add  ah,bh
        mov  ch,0x41
        add  ch,dl
        mov  bl,0x41
        add  BYTE PTR [esi],ch
        mov  dh,0x41
        add  BYTE PTR [ebp-0x6affbe4b],dl
        mov  ch,0x41
        add  BYTE PTR [ebp+esi*4-0x4a5cffbf],bl
        inc  ecx
        add  BYTE PTR [ebx+0x530041b5],ah
        push  ebp
        push  esi
        push  edi
        mov  edi,eax
        add  edi,0x14
        lea  esi,[edi+0x338]
        mov  ebp,0x896
        mov  bl,0xff
        jmp loc_0041B900
        nop
        nop
    loc_0041B900:
        mov  eax,DWORD PTR [esi+0xa4]
        test  eax,eax
        je loc_0041B9DC
        fld  DWORD PTR [esi+0x74]
        fadd  DWORD PTR ds:0x470b4c
        fstp  DWORD PTR [esi-0x4]
        fld  DWORD PTR [esi+0x78]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [esi]
        mov  eax,DWORD PTR [esi+0x7c]
        mov  DWORD PTR [esi+0x4],eax
        fld  DWORD PTR [esi]
        fcomp DWORD PTR ds:0x470bd0
        fnstsw ax
        test  ah,0x5
        jp loc_0041B99F
        fld  DWORD PTR [esi]
        mov  DWORD PTR [esi],0x41c00000
        fsub  DWORD PTR ds:0x470bd0
        fcom  DWORD PTR ds:0x470bcc
        fnstsw ax
        test  ah,0x1
        jne loc_0041B95C
        fstp  st(0)
        mov  BYTE PTR [esi-0x39],bl
        jmp loc_0041B970
    loc_0041B95C:
        fmul  DWORD PTR ds:0x470d20
        fmul  DWORD PTR ds:0x470bf8
        call FUN_00463b2c
        mov  BYTE PTR [esi-0x39],al
    loc_0041B970:
        mov  eax,DWORD PTR [esi+0xac]
        movsx ecx,WORD PTR [esi+0x4c]
        lea  edx,[eax+0x161]
        cmp  ecx,edx
        je loc_0041B9CF
        mov  ecx,DWORD PTR ds:0x4776f0
        mov  ecx,DWORD PTR [ecx+0x3e0b50]
        lea  edx,[eax+0x160]
        mov  eax,edi
        call FUN_0043e5a0
        jmp loc_0041B9CF
    loc_0041B99F:
        mov  eax,DWORD PTR [esi+0xac]
        movsx edx,WORD PTR [esi+0x4c]
        lea  ecx,[eax+0x158]
        cmp  edx,ecx
        je loc_0041B9CF
        mov  ecx,DWORD PTR ds:0x4776f0
        mov  ecx,DWORD PTR [ecx+0x3e0b50]
        lea  edx,[eax+0x157]
        mov  eax,edi
        call FUN_0043e5a0
        mov  BYTE PTR [esi-0x39],bl
    loc_0041B9CF:
        mov  ecx,DWORD PTR ds:0x491c10
        mov  eax,edi
        call FUN_004451c0
    loc_0041B9DC:
        add  edi,0x3f0
        add  esi,0x3f0
        dec  ebp
        jne loc_0041B900
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        ret
    }
}
