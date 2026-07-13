// 00428280: FUN_00428280
// Original size: 944 bytes, actual code: 273 instructions
extern "C" void FUN_00409e50(void);
extern "C" void FUN_0040c4d0(void);
extern "C" void FUN_00428d70(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_004492a0(void);
extern "C" void FUN_0044bc70(void);
extern "C" void FUN_0044c2a0(void);
extern "C" void FUN_0044c5d0(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00428280(void) {
    __asm {
        sub  esp,0x8
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x14]
        push  esi
        push  edi
        lea  edi,[ebp+0x49c]
        mov  DWORD PTR [esp+0x10],edi
        add  edi,0x20
        mov  DWORD PTR [esp+0x14],0x80
        xor  ebx,ebx
        jmp loc_004282B0
    loc_004282A4:
        mov  ebp,DWORD PTR [esp+0x1c]
        jmp loc_004282B0
        lea  ebx,[ebx+0x0]
    loc_004282B0:
        mov  eax,DWORD PTR [edi+0x20]
        cmp  eax,ebx
        je loc_004285C3
        mov  ecx,DWORD PTR [edi+0x38]
        cmp  BYTE PTR [ecx+0x1d],0x3
        mov  esi,0x1
        jne loc_00428309
        cmp  eax,esi
        jne loc_00428309
        cmp  DWORD PTR [ebp+0x464],ebx
        jl loc_004282E4
        movsx eax,BYTE PTR [ecx+0x1c]
        mov  ecx,DWORD PTR [ebp+0x3500]
        dec  eax
        cmp  eax,ecx
        jl loc_00428309
    loc_004282E4:
        lea  eax,[edi+0x24]
        call FUN_00409e50
        lea  eax,[edi+0x28]
        call FUN_00409e50
        mov  ecx,DWORD PTR [edi+0x38]
        mov  DWORD PTR [edi+0x20],0x2
        movsx edx,BYTE PTR [ecx+0x1c]
        mov  DWORD PTR [ebp+edx*4+0x42f4],ebx
    loc_00428309:
        mov  eax,DWORD PTR [edi+0x38]
        cmp  BYTE PTR [eax+0x1d],0x3
        jne loc_00428355
        cmp  DWORD PTR [edi+0x20],esi
        jne loc_00428355
        mov  eax,ds:0x47770c
        cmp  eax,ebx
        je loc_00428328
        cmp  DWORD PTR [eax+0x9eb8],ebx
        jne loc_00428330
    loc_00428328:
        cmp  DWORD PTR ds:0x477704,ebx
        jne loc_00428355
    loc_00428330:
        lea  eax,[edi+0x24]
        mov  DWORD PTR [edi+0x20],0x2
        call FUN_00409e50
        lea  eax,[edi+0x28]
        call FUN_00409e50
        mov  ecx,DWORD PTR [edi+0x38]
        movsx edx,BYTE PTR [ecx+0x1c]
        mov  DWORD PTR [ebp+edx*4+0x42f4],ebx
    loc_00428355:
        mov  eax,DWORD PTR [edi+0x38]
        cmp  BYTE PTR [eax+0x1d],0x3
        jne loc_00428378
        cmp  DWORD PTR [edi+0x30],ebx
        jne loc_00428378
        cmp  DWORD PTR [edi+0x20],esi
        jne loc_00428378
        cmp  DWORD PTR [edi+0x34],esi
        jne loc_00428378
        lea  eax,[edi+0x24]
        call FUN_0040c4d0
        mov  DWORD PTR [edi+0x34],ebx
    loc_00428378:
        mov  ecx,DWORD PTR [edi+0x38]
        mov  DWORD PTR [edi+0x30],ebx
        mov  eax,DWORD PTR [ecx+0x28]
        cmp  eax,ebx
        je loc_0042838D
        mov  edx,DWORD PTR [esp+0x10]
        mov  ecx,ebp
        call  eax
    loc_0042838D:
        test  BYTE PTR [edi+0x1c],0x1
        jne loc_004283A7
        mov  edx,DWORD PTR [edi+0xc]
        mov  eax,DWORD PTR [edi+0x10]
        push  edx
        push  eax
        mov  ecx,edi
        call FUN_0044c5d0
        mov  DWORD PTR [edi+0x8],ebx
        jmp loc_004283C2
    loc_004283A7:
        fld  DWORD PTR [edi+0x18]
        push  ecx
        fadd  DWORD PTR [edi+0x14]
        fstp  DWORD PTR [edi+0x14]
        fld  DWORD PTR [edi+0xc]
        fadd  DWORD PTR [edi+0x10]
        fstp  DWORD PTR [esp]
        call FUN_0044bc70
        fstp  DWORD PTR [edi+0x10]
    loc_004283C2:
        lea  esi,[edi-0xc]
        call FUN_0044c2a0
        mov  ecx,DWORD PTR [edi+0x24]
        cmp  ecx,ebx
        mov  edx,DWORD PTR ds:0x491c10
        je loc_0042841A
        mov  eax,DWORD PTR [edx+0x72dad4]
        cmp  eax,ebx
        je loc_004283EF
    loc_004283E1:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_00428410
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_004283E1
    loc_004283EF:
        mov  eax,DWORD PTR [edx+0x72dadc]
        cmp  eax,ebx
        je loc_0042841A
        nop
    loc_00428400:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_00428410
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_00428400
        jmp loc_0042841A
    loc_00428410:
        mov  ebp,DWORD PTR [eax]
        cmp  ebp,ebx
        jne loc_004284AD
    loc_0042841A:
        mov  DWORD PTR [edi+0x20],ebx
        mov  ecx,DWORD PTR [edi+0x28]
        cmp  ecx,ebx
        je loc_0042849F
        mov  eax,DWORD PTR [edx+0x72dad4]
        cmp  eax,ebx
        je loc_0042843D
        mov  edi,edi
    loc_00428430:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_00428462
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_00428430
    loc_0042843D:
        mov  eax,DWORD PTR [edx+0x72dadc]
        cmp  eax,ebx
        je loc_0042849F
    loc_00428447:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_00428462
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_00428447
        mov  DWORD PTR [edi+0x28],ebx
        mov  DWORD PTR [edi+0x24],ebx
        mov  DWORD PTR [edi+0x28],ebx
        jmp loc_004285C3
    loc_00428462:
        mov  eax,DWORD PTR [eax]
        cmp  eax,ebx
        je loc_0042849F
        mov  esi,DWORD PTR [eax+0x35c]
        mov  ecx,DWORD PTR [eax+0x18]
        mov  edx,0x4000000
        or   esi,edx
        cmp  ecx,ebx
        mov  DWORD PTR [eax+0x35c],esi
        jne loc_0042849F
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,ebx
        je loc_0042849F
        nop
    loc_00428490:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],edx
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_00428490
    loc_0042849F:
        mov  DWORD PTR [edi+0x28],ebx
        mov  DWORD PTR [edi+0x24],ebx
        mov  DWORD PTR [edi+0x28],ebx
        jmp loc_004285C3
    loc_004284AD:
        mov  eax,DWORD PTR [edi+0x38]
        cmp  BYTE PTR [eax+0x1d],0x3
        je loc_004284F7
        cmp  DWORD PTR [edi-0x1c],0xa
        jl loc_004284F7
        mov  eax,DWORD PTR [ebp+0x394]
        fld  DWORD PTR [eax+0x30]
        sub  esp,0x8
        fmul  DWORD PTR [ebp+0x40]
        mov  ecx,esi
        fstp  DWORD PTR [esp+0x4]
        fld  DWORD PTR [eax+0x34]
        fmul  DWORD PTR [ebp+0x3c]
        fstp  DWORD PTR [esp]
        call FUN_00428d70
        test  eax,eax
        je loc_004284F7
        mov  ecx,DWORD PTR [edi+0x24]
        push  ecx
        call FUN_004492a0
        mov  DWORD PTR [edi+0x24],ebx
        mov  DWORD PTR [edi+0x20],ebx
        jmp loc_004285C3
    loc_004284F7:
        fld  DWORD PTR [esi]
        fadd  DWORD PTR ds:0x470b4c
        fstp  DWORD PTR [ebp+0x340]
        fld  DWORD PTR [edi-0x8]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [ebp+0x344]
        mov  eax,DWORD PTR [edi-0x4]
        mov  DWORD PTR [ebp+0x348],eax
        mov  eax,DWORD PTR [edi+0x28]
        cmp  eax,ebx
        je loc_0042855B
        mov  ecx,eax
        push  ecx
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_00428535
        mov  DWORD PTR [edi+0x28],ebx
        jmp loc_0042855B
    loc_00428535:
        fld  DWORD PTR [esi]
        fadd  DWORD PTR ds:0x470b4c
        fstp  DWORD PTR [eax+0x340]
        fld  DWORD PTR [edi-0x8]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [eax+0x344]
        mov  edx,DWORD PTR [edi-0x4]
        mov  DWORD PTR [eax+0x348],edx
    loc_0042855B:
        mov  eax,DWORD PTR [ebp+0x35c]
        test  eax,0x8000000
        je loc_00428577
        mov  ecx,DWORD PTR [edi+0x10]
        or   eax,0x4
        mov  DWORD PTR [ebp+0x2c],ecx
        mov  DWORD PTR [ebp+0x35c],eax
    loc_00428577:
        mov  eax,DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [edi-0x1c]
        mov  ecx,DWORD PTR [edi-0x14]
        mov  DWORD PTR [eax],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_004285B3
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_004285B3
        fld  DWORD PTR [edi-0x18]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [edi-0x1c],edx
        fstp  DWORD PTR [edi-0x18]
        jmp loc_004285C3
    loc_004285B3:
        fld  DWORD PTR [edi-0x18]
        fadd  DWORD PTR [ecx]
        fst  DWORD PTR [edi-0x18]
        call FUN_00463b2c
        mov  DWORD PTR [edi-0x1c],eax
    loc_004285C3:
        mov  edx,DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [esp+0x14]
        add  edx,0x5c
        add  edi,0x5c
        dec  eax
        mov  DWORD PTR [esp+0x10],edx
        mov  DWORD PTR [esp+0x14],eax
        jne loc_004282A4
        pop  edi
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0x8
        ret  0x4
    }
}
