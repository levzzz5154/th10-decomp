// 0040DC80: FUN_0040dc80
// Original size: 2416 bytes, actual code: 671 instructions
extern "C" void FUN_00404610(void);
extern "C" void FUN_00409d90(void);
extern "C" void FUN_0040c6e0(void);
extern "C" void FUN_0040c730(void);
extern "C" void FUN_0040e5f0(void);
extern "C" void FUN_004127a0(void);
extern "C" void FUN_00412ac0(void);
extern "C" void FUN_004266b0(void);
extern "C" void FUN_00428630(void);
extern "C" void FUN_0043dd10(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_004492f0(void);
extern "C" void FUN_00449350(void);
extern "C" void FUN_004496d0(void);
extern "C" void FUN_0044bc70(void);
extern "C" void FUN_0044bf40(void);
extern "C" void FUN_0044c2a0(void);
extern "C" void FUN_0044c5d0(void);
extern "C" void FUN_0044fd10(void);
extern "C" void FUN_00450470(void);
extern "C" void FUN_00450700(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0040dc80(void) {
    __asm {
        sub  esp,0x18
        push  ebp
        mov  ebp,DWORD PTR [esp+0x20]
        mov  eax,DWORD PTR [ebp+0x1444]
        test  ah,0x4
        je loc_0040DC9C
        xor  eax,eax
        pop  ebp
        add  esp,0x18
        ret  0x4
    loc_0040DC9C:
        or   eax,0x400
        push  esi
        push  edi
        mov  DWORD PTR [ebp+0x1444],eax
        mov  eax,DWORD PTR [ebp+0x208]
        test  eax,eax
        lea  esi,[ebp+0x2c]
        mov  ecx,0xb
        mov  edi,ebp
        rep movsd
        je loc_0040DCE2
        lea  esi,[ebp+0x1d4]
        lea  edi,[esp+0xc]
        call FUN_00412ac0
        mov  eax,DWORD PTR [esp+0xc]
        push  eax
        call FUN_0044bc70
        fstp  DWORD PTR [ebp+0x74]
        mov  ecx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [ebp+0x70],ecx
    loc_0040DCE2:
        mov  eax,DWORD PTR [ebp+0x280]
        test  eax,eax
        je loc_0040DD09
        lea  esi,[ebp+0x24c]
        lea  edi,[esp+0xc]
        call FUN_00412ac0
        mov  edx,DWORD PTR [esp+0xc]
        mov  eax,DWORD PTR [esp+0x10]
        mov  DWORD PTR [ebp+0x78],edx
        mov  DWORD PTR [ebp+0x7c],eax
    loc_0040DD09:
        mov  eax,DWORD PTR [ebp+0x244]
        test  eax,eax
        je loc_0040DD3C
        lea  esi,[ebp+0x210]
        lea  edi,[esp+0xc]
        call FUN_00412ac0
        mov  ecx,DWORD PTR [esp+0xc]
        push  ecx
        call FUN_0044bc70
        fstp  DWORD PTR [ebp+0xa0]
        mov  edx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [ebp+0x9c],edx
    loc_0040DD3C:
        mov  eax,DWORD PTR [ebp+0x2bc]
        test  eax,eax
        je loc_0040DD69
        lea  esi,[ebp+0x288]
        lea  edi,[esp+0xc]
        call FUN_00412ac0
        mov  eax,DWORD PTR [esp+0xc]
        mov  ecx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [ebp+0xa4],eax
        mov  DWORD PTR [ebp+0xa8],ecx
    loc_0040DD69:
        mov  eax,DWORD PTR [ebp+0x180]
        test  eax,eax
        je loc_0040DDB8
        lea  eax,[ebp+0x13c]
        lea  edi,[esp+0x18]
        call FUN_00404610
        fld  DWORD PTR [eax]
        fsub  DWORD PTR [ebp+0x58]
        lea  edx,[ebp+0x64]
        fstp  DWORD PTR [esp+0xc]
        fld  DWORD PTR [eax+0x4]
        fsub  DWORD PTR [ebp+0x5c]
        fstp  DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [esp+0x10]
        fld  DWORD PTR [eax+0x8]
        mov  eax,DWORD PTR [esp+0xc]
        fsub  DWORD PTR [ebp+0x60]
        mov  DWORD PTR [edx],eax
        mov  DWORD PTR [edx+0x4],ecx
        fstp  DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x14]
        mov  DWORD PTR [edx+0x8],eax
        jmp loc_0040DDF5
    loc_0040DDB8:
        test  BYTE PTR [ebp+0x80],0x1
        jne loc_0040DDDA
        mov  ecx,DWORD PTR [ebp+0x70]
        mov  edx,DWORD PTR [ebp+0x74]
        push  ecx
        push  edx
        lea  ecx,[ebp+0x64]
        call FUN_0044c5d0
        mov  DWORD PTR [ebp+0x6c],0x0
        jmp loc_0040DDF5
    loc_0040DDDA:
        fld  DWORD PTR [ebp+0x7c]
        push  ecx
        fadd  DWORD PTR [ebp+0x78]
        fstp  DWORD PTR [ebp+0x78]
        fld  DWORD PTR [ebp+0x70]
        fadd  DWORD PTR [ebp+0x74]
        fstp  DWORD PTR [esp]
        call FUN_0044bc70
        fstp  DWORD PTR [ebp+0x74]
    loc_0040DDF5:
        mov  eax,DWORD PTR [ebp+0x1cc]
        test  eax,eax
        push  ebx
        lea  ebx,[ebp+0x84]
        je loc_0040DE4D
        lea  eax,[ebp+0x188]
        lea  edi,[esp+0x1c]
        call FUN_00404610
        fld  DWORD PTR [eax]
        fsub  DWORD PTR [ebx]
        fstp  DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [esp+0x10]
        fld  DWORD PTR [eax+0x4]
        fsub  DWORD PTR [ebx+0x4]
        fstp  DWORD PTR [esp+0x14]
        mov  edx,DWORD PTR [esp+0x14]
        fld  DWORD PTR [eax+0x8]
        lea  eax,[ebp+0x90]
        fsub  DWORD PTR [ebx+0x8]
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [eax+0x4],edx
        fstp  DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [eax+0x8],ecx
        jmp loc_0040DE87
    loc_0040DE4D:
        test  BYTE PTR [ebx+0x28],0x1
        jne loc_0040DE6C
        mov  edx,DWORD PTR [ebx+0x18]
        mov  eax,DWORD PTR [ebx+0x1c]
        push  edx
        push  eax
        lea  ecx,[ebx+0xc]
        call FUN_0044c5d0
        mov  DWORD PTR [ebx+0x14],0x0
        jmp loc_0040DE87
    loc_0040DE6C:
        fld  DWORD PTR [ebx+0x24]
        push  ecx
        fadd  DWORD PTR [ebx+0x20]
        fstp  DWORD PTR [ebx+0x20]
        fld  DWORD PTR [ebx+0x18]
        fadd  DWORD PTR [ebx+0x1c]
        fstp  DWORD PTR [esp]
        call FUN_0044bc70
        fstp  DWORD PTR [ebx+0x1c]
    loc_0040DE87:
        lea  edi,[ebp+0x58]
        mov  esi,edi
        call FUN_0044c2a0
        test  DWORD PTR [ebp+0x1444],0x40000
        je loc_0040DEBF
        fld  DWORD PTR ds:0x491e6c
        fadd  DWORD PTR [ebx]
        fstp  DWORD PTR [ebx]
        fld  DWORD PTR ds:0x491e70
        fadd  DWORD PTR [ebx+0x4]
        fstp  DWORD PTR [ebx+0x4]
        fld  DWORD PTR ds:0x491e74
        fadd  DWORD PTR [ebx+0x8]
        fstp  DWORD PTR [ebx+0x8]
    loc_0040DEBF:
        mov  esi,ebx
        call FUN_0044c2a0
        fld  DWORD PTR [ebx]
        fadd  DWORD PTR [edi]
        lea  esi,[ebp+0x2c]
        fld  DWORD PTR [ebx+0x4]
        lea  eax,[ebp+0x38]
        fadd  DWORD PTR [edi+0x4]
        fld  DWORD PTR [ebx+0x8]
        fadd  DWORD PTR [edi+0x8]
        fstp  DWORD PTR [esp+0x24]
        fxch  st(1)
        fsub  DWORD PTR [esi]
        fstp  DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [esp+0x10]
        fsub  DWORD PTR [esi+0x4]
        fstp  DWORD PTR [esp+0x14]
        mov  edx,DWORD PTR [esp+0x14]
        fld  DWORD PTR [esp+0x24]
        fsub  DWORD PTR [esi+0x8]
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [eax+0x4],edx
        fstp  DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [eax+0x8],ecx
        call FUN_0044c2a0
        mov  ecx,DWORD PTR [ebp+0x1444]
        test  ch,0x2
        je loc_0040DFDA
        fld  DWORD PTR [ebp+0x13b4]
        fmul  DWORD PTR ds:0x470b0c
        fstp  DWORD PTR [esp+0x2c]
        fld  DWORD PTR [ebp+0x13ac]
        fsub  DWORD PTR [esp+0x2c]
        fcom  DWORD PTR [esi]
        fnstsw ax
        test  ah,0x41
        jne loc_0040DF49
        fstp  DWORD PTR [esi]
        jmp loc_0040DF64
    loc_0040DF49:
        fstp  st(0)
        fld  DWORD PTR [esp+0x2c]
        fadd  DWORD PTR [ebp+0x13ac]
        fcom  DWORD PTR [esi]
        fnstsw ax
        test  ah,0x5
        jp loc_0040DF62
        fstp  DWORD PTR [esi]
        jmp loc_0040DF64
    loc_0040DF62:
        fstp  st(0)
    loc_0040DF64:
        fld  DWORD PTR [ebp+0x13b8]
        fmul  DWORD PTR ds:0x470b0c
        fstp  DWORD PTR [esp+0x2c]
        fld  DWORD PTR [ebp+0x13b0]
        fsub  DWORD PTR [esp+0x2c]
        fcom  DWORD PTR [ebp+0x30]
        fnstsw ax
        test  ah,0x41
        jne loc_0040DF8D
        fstp  DWORD PTR [ebp+0x30]
        jmp loc_0040DFAA
    loc_0040DF8D:
        fstp  st(0)
        fld  DWORD PTR [esp+0x2c]
        fadd  DWORD PTR [ebp+0x13b0]
        fcom  DWORD PTR [ebp+0x30]
        fnstsw ax
        test  ah,0x5
        jp loc_0040DFA8
        fstp  DWORD PTR [ebp+0x30]
        jmp loc_0040DFAA
    loc_0040DFA8:
        fstp  st(0)
    loc_0040DFAA:
        fld  DWORD PTR [esi]
        fsub  DWORD PTR [ebx]
        fstp  DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [esp+0x10]
        fld  DWORD PTR [esi+0x4]
        fsub  DWORD PTR [ebx+0x4]
        fstp  DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x14]
        fld  DWORD PTR [esi+0x8]
        fsub  DWORD PTR [ebx+0x8]
        mov  DWORD PTR [edi],edx
        mov  DWORD PTR [edi+0x4],eax
        fstp  DWORD PTR [esp+0x18]
        mov  edx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [edi+0x8],edx
    loc_0040DFDA:
        fld  DWORD PTR [ebp+0x13a4]
        fmul  DWORD PTR ds:0x470b0c
        fld  st(0)
        fadd  DWORD PTR [esi]
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x5
        jnp loc_0040E09B
        fld  DWORD PTR [esi]
        fsub  st,st(1)
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        fstp  st(0)
        test  ah,0x41
        je loc_0040E09D
        fld  DWORD PTR [ebp+0x13a8]
        fmul  DWORD PTR ds:0x470b0c
        fld  st(0)
        fadd  DWORD PTR [ebp+0x30]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jnp loc_0040E09B
        fld  DWORD PTR [ebp+0x30]
        fsub  st,st(1)
        fcomp DWORD PTR ds:0x470b38
        fnstsw ax
        fstp  st(0)
        test  ah,0x41
        je loc_0040E09D
        or   ecx,0x100
        mov  DWORD PTR [ebp+0x1444],ecx
    loc_0040E050:
        mov  ecx,DWORD PTR [ebp+0x1444]
        test  ecx,0x100000
        je loc_0040E0E9
        mov  eax,ds:0x4776ec
        mov  eax,DWORD PTR [eax+0x28]
        test  eax,eax
        je loc_0040E0B8
        test  ecx,0x200000
        jne loc_0040E0B4
        mov  eax,DWORD PTR [ebp+0x1448]
        mov  DWORD PTR [ebp+0xf4],eax
        push  eax
        lea  eax,[ebp+0xc0]
        call FUN_004496d0
        mov  eax,DWORD PTR [ebp+0x1444]
        or   eax,0x200001
        jmp loc_0040E0E3
    loc_0040E09B:
        fstp  st(0)
    loc_0040E09D:
        test  ch,0x1
        je loc_0040E050
        test  cl,0x4
        jne loc_0040E050
    loc_0040E0A7:
        pop  ebx
        pop  edi
        pop  esi
        or   eax,0xffffffff
        pop  ebp
        add  esp,0x18
        ret  0x4
    loc_0040E0B4:
        test  eax,eax
        jne loc_0040E0E9
    loc_0040E0B8:
        test  ecx,0x200000
        je loc_0040E0E9
        mov  eax,DWORD PTR [ebp+0x144c]
        mov  DWORD PTR [ebp+0xf4],eax
        push  eax
        lea  eax,[ebp+0xc0]
        call FUN_004496d0
        mov  eax,DWORD PTR [ebp+0x1444]
        and  eax,0xffdffffe
    loc_0040E0E3:
        mov  DWORD PTR [ebp+0x1444],eax
    loc_0040E0E9:
        mov  ecx,DWORD PTR [ebp+0x128]
        mov  edx,DWORD PTR [ecx]
        mov  edi,DWORD PTR [ebp+0x14d8]
        mov  eax,edx
        push  eax
        mov  DWORD PTR [esp+0x30],edx
        call FUN_0044fd10
        test  eax,eax
        jne loc_0040E0A7
        mov  edx,DWORD PTR [ebp+0x1444]
        and  edx,0xffffdfff
        mov  eax,edx
        test  al,0x11
        mov  DWORD PTR [ebp+0x1444],edx
        mov  ebx,0x8
        jne loc_0040E275
        mov  edx,DWORD PTR ds:0x477834
        lea  ecx,[ebp+0xb0]
        push  ecx
        lea  eax,[ebp+0x2c]
        push  eax
        push  edx
        xor  ecx,ecx
        call FUN_00428630
        mov  ecx,eax
        mov  eax,ds:0x477834
        mov  eax,DWORD PTR [eax+0x458]
        cmp  eax,0x2
        je loc_0040E157
        test  eax,eax
        jne loc_0040E167
    loc_0040E157:
        mov  eax,0x66666667
        imul  ecx
        sar  edx,1
        mov  ecx,edx
        shr  ecx,0x1f
        add  ecx,edx
    loc_0040E167:
        test  ecx,ecx
        je loc_0040E26B
        mov  edx,DWORD PTR ds:0x4776f4
        test  BYTE PTR [edx+0x378c],0x1
        je loc_0040E1A3
        mov  eax,DWORD PTR [ebp+0x1444]
        test  ah,ah
        jns loc_0040E1A3
        mov  eax,0x66666667
        imul  ecx
        sar  edx,1
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        mov  ecx,eax
        test  ecx,ecx
        jg loc_0040E1A3
        mov  ecx,0x1
    loc_0040E1A3:
        test  BYTE PTR [ebp+0x1444],0x8
        jne loc_0040E1BC
        mov  eax,DWORD PTR [ebp+0x1420]
        test  eax,eax
        jg loc_0040E1BC
        sub  DWORD PTR [ebp+0x13c0],ecx
    loc_0040E1BC:
        mov  ecx,DWORD PTR [ebp+0x14d8]
        call FUN_004127a0
        mov  esi,eax
        test  esi,esi
        je loc_0040E212
        mov  eax,DWORD PTR [ebp+0x14d8]
        call FUN_0040c6e0
        mov  eax,DWORD PTR [ebp+0x14d8]
        call FUN_0040c730
        mov  ecx,esi
        mov  esi,DWORD PTR [ebp+0x14d8]
        call FUN_00450700
        mov  ecx,DWORD PTR [ebp+0x128]
        mov  edx,DWORD PTR [ecx]
        mov  edi,DWORD PTR [ebp+0x14d8]
        mov  eax,edx
        push  eax
        mov  DWORD PTR [esp+0x30],edx
        call FUN_0044fd10
        test  eax,eax
        jne loc_0040E0A7
    loc_0040E212:
        mov  edx,DWORD PTR [ebp+0x13c0]
        xor  ecx,ecx
        test  edx,edx
        mov  edx,DWORD PTR [ebp+0x1444]
        setle cl
        shr  edx,0x6
        not  edx
        and  ecx,edx
        test  cl,0x1
        je loc_0040E261
        mov  eax,DWORD PTR [ebp+0x13bc]
        push  eax
        mov  ecx,0x474c40
        call FUN_00409d90
        mov  ecx,DWORD PTR [ebp+0x14d8]
        push  ecx
        call FUN_0040e5f0
        test  eax,eax
        je loc_0040E261
        pop  ebx
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        add  esp,0x18
        ret  0x4
    loc_0040E261:
        or   DWORD PTR [ebp+0x1444],0x2000
    loc_0040E26B:
        mov  DWORD PTR ds:0x474c50,0x1
    loc_0040E275:
        mov  ecx,DWORD PTR [ebp+0x14d8]
        call FUN_004127a0
        mov  edi,eax
        test  edi,edi
        je loc_0040E2BD
        mov  eax,DWORD PTR [ebp+0x14d8]
        call FUN_0040c6e0
        mov  eax,DWORD PTR [ebp+0x14d8]
        call FUN_0040c730
        mov  esi,DWORD PTR [ebp+0x14d8]
        mov  eax,DWORD PTR [esi+0x102c]
        push  edi
        call FUN_00450470
        mov  edx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [edx+0x4],eax
        mov  eax,DWORD PTR [esi+0x4]
        mov  DWORD PTR [eax],0x0
    loc_0040E2BD:
        test  BYTE PTR [ebp+0x1444],0x12
        jne loc_0040E2E4
        mov  eax,DWORD PTR [ebp+0x1434]
        test  eax,eax
        jg loc_0040E2E4
        mov  edx,DWORD PTR ds:0x477834
        lea  eax,[ebp+0xb8]
        lea  ecx,[ebp+0x2c]
        call FUN_004266b0
    loc_0040E2E4:
        mov  eax,DWORD PTR [ebp+0x1444]
        test  ah,0x10
        je loc_0040E379
        fld  DWORD PTR [ebp+0x38]
        xor  ecx,ecx
        fcomp DWORD PTR ds:0x470d30
        fnstsw ax
        test  ah,0x5
        jp loc_0040E30C
        mov  eax,0xffffffff
        jmp loc_0040E325
    loc_0040E30C:
        fld  DWORD PTR [ebp+0x38]
        fcomp DWORD PTR ds:0x470c18
        fnstsw ax
        test  ah,0x41
        jne loc_0040E323
        mov  eax,0x1
        jmp loc_0040E325
    loc_0040E323:
        xor  eax,eax
    loc_0040E325:
        mov  edx,DWORD PTR [ebp+0xf8]
        cmp  edx,eax
        je loc_0040E379
        cmp  edx,0xffffffff
        je loc_0040E356
        test  edx,edx
        je loc_0040E34B
        cmp  edx,0x1
        jne loc_0040E35F
        mov  ecx,eax
        neg  ecx
        sbb  ecx,ecx
        and  ecx,0xfffffffd
        add  ecx,0x4
        jmp loc_0040E35F
    loc_0040E34B:
        xor  ecx,ecx
        cmp  eax,0xffffffff
        setne cl
        inc  ecx
        jmp loc_0040E35F
    loc_0040E356:
        mov  ecx,eax
        neg  ecx
        sbb  ecx,ecx
        add  ecx,0x3
    loc_0040E35F:
        mov  edx,DWORD PTR [ebp+0xf4]
        add  edx,ecx
        mov  DWORD PTR [ebp+0xf8],eax
        push  edx
        lea  eax,[ebp+0xc0]
        call FUN_004496d0
    loc_0040E379:
        test  DWORD PTR [ebp+0x1444],0x40000
        lea  edi,[ebp+0xc0]
        jne loc_0040E3B2
        mov  DWORD PTR [esp+0x2c],ebx
        mov  ebx,DWORD PTR ds:0x491c10
    loc_0040E395:
        mov  eax,DWORD PTR [edi]
        push  eax
        lea  esi,[ebp+0x2c]
        mov  edx,ebx
        call FUN_00449350
        mov  eax,DWORD PTR [esp+0x2c]
        add  edi,0x4
        dec  eax
        mov  DWORD PTR [esp+0x2c],eax
        jne loc_0040E395
        jmp loc_0040E3DB
    loc_0040E3B2:
        mov  DWORD PTR [esp+0x2c],ebx
        mov  ebx,DWORD PTR ds:0x491c10
        nop
    loc_0040E3C0:
        mov  ecx,DWORD PTR [edi]
        push  ecx
        lea  esi,[ebp+0x2c]
        mov  edx,ebx
        call FUN_004492f0
        mov  eax,DWORD PTR [esp+0x2c]
        add  edi,0x4
        dec  eax
        mov  DWORD PTR [esp+0x2c],eax
        jne loc_0040E3C0
    loc_0040E3DB:
        mov  eax,DWORD PTR [ebp+0x1444]
        test  al,0x11
        jne loc_0040E43E
        test  eax,0xc0000
        jne loc_0040E43E
        mov  ecx,DWORD PTR ds:0x477834
        mov  eax,DWORD PTR [ecx+0x3504]
        test  eax,eax
        je loc_0040E421
        fld  DWORD PTR [eax+0x1068]
        fsub  DWORD PTR [ecx+0x3c0]
        fabs
        fld  DWORD PTR [esi]
        fsub  DWORD PTR [ecx+0x3c0]
        fabs
        fxch  st(1)
        fxch  st(1)
        fcompp
        fnstsw ax
        test  ah,0x41
        jne loc_0040E43E
    loc_0040E421:
        mov  al,BYTE PTR [ecx+0x3508]
        test  al,al
        jne loc_0040E437
        mov  edx,DWORD PTR [ebp+0x14d8]
        mov  DWORD PTR [ecx+0x3504],edx
    loc_0040E437:
        mov  BYTE PTR [ecx+0x3508],0x1
    loc_0040E43E:
        mov  eax,DWORD PTR [ebp+0xc0]
        push  eax
        mov  edx,ebx
        call FUN_004491c0
        test  eax,eax
        jne loc_0040E456
        mov  DWORD PTR [ebp+0xc0],eax
    loc_0040E456:
        mov  ecx,DWORD PTR [ebp+0x1414]
        test  ecx,ecx
        jne loc_0040E510
        mov  ecx,DWORD PTR [ebp+0x1444]
        test  ch,0x20
        je loc_0040E53E
        mov  edx,DWORD PTR [eax+0x35c]
        mov  ecx,0x8000
        or   edx,ecx
        mov  DWORD PTR [eax+0x300],0xff0000ff
        mov  DWORD PTR [eax+0x35c],edx
        test  DWORD PTR [ebp+0x1444],ecx
        mov  DWORD PTR [ebp+0x1414],0x4
        je loc_0040E4FB
        mov  ecx,DWORD PTR ds:0x4776f4
        mov  ecx,DWORD PTR [ecx+0x378c]
        mov  eax,ecx
        and  eax,0x1
        je loc_0040E4BA
        test  cl,0x8
        jne loc_0040E4FB
    loc_0040E4BA:
        test  eax,eax
        je loc_0040E4D4
        mov  edx,DWORD PTR [ebp+0x14d8]
        cmp  DWORD PTR [edx+0x2404],0x12c
        jl loc_0040E4E6
        test  eax,eax
        jne loc_0040E4FB
    loc_0040E4D4:
        mov  eax,DWORD PTR [ebp+0x14d8]
        cmp  DWORD PTR [eax+0x2404],0x384
        jge loc_0040E4FB
    loc_0040E4E6:
        mov  ecx,DWORD PTR [ebp+0x2c]
        push  ecx
        mov  ebx,0x23
        mov  esi,0x492590
        call FUN_0043dd10
        jmp loc_0040E53E
    loc_0040E4FB:
        mov  edx,DWORD PTR [ebp+0x2c]
        push  edx
        mov  ebx,0x13
        mov  esi,0x492590
        call FUN_0043dd10
        jmp loc_0040E53E
    loc_0040E510:
        mov  edx,DWORD PTR [eax+0x35c]
        mov  ecx,0xffff7fff
        and  edx,ecx
        mov  DWORD PTR [eax+0x35c],edx
        mov  eax,DWORD PTR [ebp+0x1444]
        test  ah,ah
        jns loc_0040E538
        mov  eax,ds:0x47770c
        and  DWORD PTR [eax+0x9da4],ecx
    loc_0040E538:
        dec  DWORD PTR [ebp+0x1414]
    loc_0040E53E:
        mov  eax,DWORD PTR [ebp+0x1420]
        test  eax,eax
        jle loc_0040E558
        push  0xbf800000
        lea  esi,[ebp+0x141c]
        call FUN_0044bf40
    loc_0040E558:
        mov  eax,DWORD PTR [ebp+0x1434]
        test  eax,eax
        jle loc_0040E572
        push  0xbf800000
        lea  esi,[ebp+0x1430]
        call FUN_0044bf40
    loc_0040E572:
        mov  edx,DWORD PTR [ebp+0x120]
        mov  ecx,DWORD PTR [ebp+0x128]
        mov  DWORD PTR [ebp+0x11c],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_0040E5C7
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0040E5C7
        fld  DWORD PTR [ebp+0x124]
        pop  ebx
        fadd  DWORD PTR ds:0x470afc
        pop  edi
        inc  edx
        pop  esi
        fstp  DWORD PTR [ebp+0x124]
        mov  DWORD PTR [ebp+0x120],edx
        xor  eax,eax
        pop  ebp
        add  esp,0x18
        ret  0x4
    loc_0040E5C7:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [ebp+0x124]
        fst  DWORD PTR [ebp+0x124]
        call FUN_00463b2c
        pop  ebx
        pop  edi
        mov  DWORD PTR [ebp+0x120],eax
        pop  esi
        xor  eax,eax
        pop  ebp
        add  esp,0x18
        ret  0x4
    }
}
