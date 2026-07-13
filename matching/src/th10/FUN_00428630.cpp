// 00428630: FUN_00428630
// Original size: 1520 bytes, actual code: 355 instructions
extern "C" void FUN_004059f0(void);
extern "C" void FUN_0040c480(void);
extern "C" void FUN_00427b50(void);
extern "C" void FUN_00427c70(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_00449450(void);
extern "C" void FUN_00449630(void);

extern "C" __declspec(naked) void FUN_00428630(void) {
    __asm {
        sub  esp,0x40
        push  ebp
        mov  ebp,DWORD PTR [esp+0x48]
        mov  eax,DWORD PTR [ebp+0x478]
        cmp  eax,DWORD PTR [ebp+0x474]
        mov  DWORD PTR [esp+0x48],0x0
        jne loc_00428657
        xor  eax,eax
        pop  ebp
        add  esp,0x40
        ret  0xc
    loc_00428657:
        test  ecx,ecx
        mov  eax,DWORD PTR [esp+0x50]
        fld  DWORD PTR [eax]
        push  ebx
        fmul  DWORD PTR ds:0x470b0c
        push  esi
        push  edi
        mov  edi,DWORD PTR [esp+0x58]
        fld  DWORD PTR [edi]
        lea  ebx,[ebp+0x49c]
        fsub  st,st(1)
        mov  DWORD PTR [esp+0x10],ebx
        fstp  DWORD PTR [esp+0x38]
        fld  DWORD PTR [eax+0x4]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [edi+0x4]
        fsub  st,st(1)
        fstp  DWORD PTR [esp+0x3c]
        fxch  st(1)
        fadd  DWORD PTR [edi]
        fstp  DWORD PTR [esp+0x2c]
        fadd  DWORD PTR [edi+0x4]
        fstp  DWORD PTR [esp+0x30]
        je loc_004286A7
        mov  DWORD PTR [ecx],0x0
    loc_004286A7:
        lea  esi,[ebx+0x44]
        mov  DWORD PTR [esp+0x14],0x80
    loc_004286B2:
        mov  eax,DWORD PTR [esi-0x4]
        test  eax,eax
        je loc_0042886C
        cmp  eax,0x2
        je loc_0042886C
        mov  ecx,DWORD PTR [esi+0x14]
        fld  DWORD PTR [ecx+0xc]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [esi-0x30]
        fsub  st,st(1)
        fstp  DWORD PTR [esp+0x44]
        fld  DWORD PTR [ecx+0x10]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [esi-0x2c]
        fsub  st,st(1)
        fstp  DWORD PTR [esp+0x48]
        fxch  st(1)
        fadd  DWORD PTR [esi-0x30]
        fstp  DWORD PTR [esp+0x20]
        fadd  DWORD PTR [esi-0x2c]
        fld  DWORD PTR [esp+0x48]
        fcomp DWORD PTR [esp+0x30]
        fnstsw ax
        test  ah,0x41
        je loc_0042894D
        fld  DWORD PTR [esp+0x44]
        fcomp DWORD PTR [esp+0x2c]
        fnstsw ax
        test  ah,0x41
        je loc_0042894D
        fcomp DWORD PTR [esp+0x3c]
        fnstsw ax
        test  ah,0x5
        jnp loc_0042886C
        fld  DWORD PTR [esp+0x20]
        fcomp DWORD PTR [esp+0x38]
        fnstsw ax
        test  ah,0x5
        jnp loc_0042886C
        mov  dl,BYTE PTR [ecx+0x1d]
        cmp  dl,0x3
        je loc_00428763
        fld  DWORD PTR [esp+0x48]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jnp loc_0042886C
        cmp  dl,0x3
        jne loc_00428778
    loc_00428763:
        fld  DWORD PTR [esp+0x30]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jnp loc_0042886C
    loc_00428778:
        mov  eax,DWORD PTR [ecx+0x30]
        test  eax,eax
        je loc_0042878E
        push  edi
        mov  edx,ebx
        mov  ecx,ebp
        call  eax
        test  eax,eax
        jne loc_0042886C
    loc_0042878E:
        mov  eax,DWORD PTR [esi+0x10]
        test  eax,eax
        jne loc_004287A3
        mov  eax,esi
        call FUN_0040c480
        mov  DWORD PTR [esi+0x10],0x1
    loc_004287A3:
        mov  edi,DWORD PTR [esi+0x14]
        mov  DWORD PTR [esi+0xc],0x1
        mov  bl,BYTE PTR [edi+0x1d]
        cmp  bl,0x3
        jne loc_004287C4
        mov  ecx,DWORD PTR [esp+0x10]
        push  0x4
        call FUN_00427c70
        test  eax,eax
        je loc_004287CC
    loc_004287C4:
        movsx ecx,WORD PTR [edi+0x2]
        add  DWORD PTR [esp+0x54],ecx
    loc_004287CC:
        cmp  bl,0x3
        je loc_00428835
        call FUN_00449450
        mov  edx,DWORD PTR [eax+0x2c]
        mov  DWORD PTR [esp+0x18],edx
        call FUN_00449630
        mov  eax,DWORD PTR [esi+0x14]
        movsx ecx,WORD PTR [eax+0x20]
        mov  edx,DWORD PTR [ebp+0x10]
        push  0xf
        add  ecx,0x5
        push  ecx
        push  edx
        lea  edi,[esp+0x28]
        call FUN_00448d00
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [esi],eax
        call FUN_00449450
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [eax+0x2c],ecx
        mov  ecx,DWORD PTR [eax+0x35c]
        or   ecx,0x4
        mov  DWORD PTR [eax+0x35c],ecx
        fld  DWORD PTR [esi-0x18]
        fmul  DWORD PTR ds:0x470b90
        mov  DWORD PTR [esi-0x28],0x3dcccccd
        mov  DWORD PTR [esi-0x4],0x2
        fstp  DWORD PTR [esi-0x18]
    loc_00428835:
        mov  eax,DWORD PTR [esi+0x14]
        cmp  BYTE PTR [eax+0x1d],0x2
        jne loc_00428868
        movsx ecx,WORD PTR [eax+0x2]
        mov  eax,0x55555556
        imul  ecx
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        push  eax
        push  0xd
        push  0x3fb33333
        push  0x42000000
        lea  eax,[esi-0x30]
        push  eax
        mov  edx,ebp
        call FUN_00427b50
    loc_00428868:
        mov  edi,DWORD PTR [esp+0x58]
    loc_0042886C:
        mov  ebx,DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [esp+0x14]
        add  ebx,0x5c
        add  esi,0x5c
        dec  eax
        mov  DWORD PTR [esp+0x10],ebx
        mov  DWORD PTR [esp+0x14],eax
        jne loc_004286B2
        mov  ecx,DWORD PTR ds:0x4776ec
        mov  eax,edi
        call FUN_004059f0
        mov  ecx,DWORD PTR [esp+0x54]
        add  ecx,eax
        add  ebp,0x350c
        mov  DWORD PTR [esp+0x54],ecx
        lea  ecx,[ebp+0x48]
        mov  esi,0x20
        mov  edi,edi
    loc_004288B0:
        mov  ebx,DWORD PTR [ecx+0x20]
        test  bl,0x1
        je loc_00428A60
        mov  eax,DWORD PTR [ecx]
        cmp  eax,DWORD PTR [ecx-0x4]
        je loc_004288CF
        cdq
        idiv  DWORD PTR [ecx+0x1c]
        test  edx,edx
        je loc_00428A60
    loc_004288CF:
        test  bl,0x2
        jne loc_00428A0C
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [ecx-0x40]
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_00428954
        fld  DWORD PTR [ecx-0x38]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [ecx-0x30]
        fsub  st,st(1)
        fcomp DWORD PTR [esp+0x2c]
        fnstsw ax
        test  ah,0x41
        je loc_00428A5E
        fadd  DWORD PTR [ecx-0x30]
        fcomp DWORD PTR [esp+0x38]
        fnstsw ax
        test  ah,0x5
        jnp loc_00428A60
        fld  DWORD PTR [ecx-0x34]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [ecx-0x2c]
        fsub  st,st(1)
        fcomp DWORD PTR [esp+0x30]
        fnstsw ax
        test  ah,0x41
        je loc_00428A5E
        fadd  DWORD PTR [ecx-0x2c]
        fcomp DWORD PTR [esp+0x3c]
        fnstsw ax
        test  ah,0x5
        jp loc_00428A37
        jmp loc_00428A60
    loc_0042894D:
        fstp  st(0)
        jmp loc_0042886C
    loc_00428954:
        fld  DWORD PTR [edi]
        mov  edx,DWORD PTR [esp+0x5c]
        fsub  DWORD PTR [ecx-0x30]
        fld  DWORD PTR [edi+0x4]
        fsub  DWORD PTR [ecx-0x2c]
        fld  DWORD PTR [ecx-0x40]
        fchs
        fld  st(0)
        fsin
        fstp  DWORD PTR [esp+0x58]
        fcos
        fld  st(0)
        fmul  st,st(3)
        fld  DWORD PTR [esp+0x58]
        fmul  st,st(3)
        fsubp st(1),st
        fstp  DWORD PTR [esp+0x20]
        fld  DWORD PTR [esp+0x58]
        fmul  st,st(3)
        fxch  st(1)
        fmul  st,st(2)
        faddp st(1),st
        fstp  DWORD PTR [esp+0x24]
        fstp  st(0)
        fstp  st(0)
        fld  DWORD PTR [edx]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [ecx-0x38]
        fmul  DWORD PTR ds:0x470b78
        fld  st(1)
        fadd  DWORD PTR [esp+0x20]
        fcompp
        fnstsw ax
        test  ah,0x5
        jnp loc_00428A5E
        fld  DWORD PTR [ecx-0x38]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [esp+0x20]
        fsub  st,st(2)
        fcompp
        fnstsw ax
        fstp  st(0)
        test  ah,0x41
        je loc_00428A60
        fld  DWORD PTR [edx+0x4]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [ecx-0x34]
        fmul  DWORD PTR ds:0x470b78
        fld  st(1)
        fadd  DWORD PTR [esp+0x24]
        fcompp
        fnstsw ax
        test  ah,0x5
        jnp loc_00428A5E
        fld  DWORD PTR [ecx-0x34]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [esp+0x24]
        fsub  st,st(2)
        fcompp
        jmp loc_00428A2E
    loc_00428A0C:
        fld  DWORD PTR [ebp+0x0]
        fld  DWORD PTR [ecx-0x2c]
        fsub  DWORD PTR [edi+0x4]
        fld  DWORD PTR [ecx-0x30]
        fsub  DWORD PTR [edi]
        fld  st(2)
        fmul  st,st(3)
        fld  st(1)
        fmul  st,st(2)
        fld  st(3)
        fmul  st,st(4)
        faddp st(1),st
        fcompp
        fstp  st(0)
        fstp  st(0)
    loc_00428A2E:
        fnstsw ax
        fstp  st(0)
        test  ah,0x41
        je loc_00428A60
    loc_00428A37:
        mov  eax,DWORD PTR [ecx+0x10]
        mov  edx,DWORD PTR [esp+0x54]
        mov  ebx,DWORD PTR [ecx+0x14]
        add  edx,eax
        add  ebx,eax
        mov  DWORD PTR [esp+0x54],edx
        mov  edx,DWORD PTR [ecx+0x18]
        mov  eax,ebx
        cmp  edx,eax
        mov  DWORD PTR [ecx+0x14],ebx
        jg loc_00428A60
        mov  DWORD PTR [ecx+0x10],0x0
        jmp loc_00428A60
    loc_00428A5E:
        fstp  st(0)
    loc_00428A60:
        add  ebp,0x6c
        add  ecx,0x6c
        dec  esi
        jne loc_004288B0
        mov  ecx,DWORD PTR [esp+0x54]
        test  ecx,ecx
        je loc_00428AB6
        mov  eax,0x66666667
        imul  ecx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0xa]
        mov  eax,0x66666667
        imul  edx
        mov  eax,ds:0x474c44
        sar  edx,0x2
        mov  esi,edx
        shr  esi,0x1f
        add  esi,edx
        add  eax,esi
        cmp  eax,0x3b9aca00
        mov  ds:0x474c44,eax
        jl loc_00428AB6
        mov  DWORD PTR ds:0x474c44,0x3b9ac9ff
    loc_00428AB6:
        pop  edi
        pop  esi
        pop  ebx
        mov  eax,ecx
        pop  ebp
        add  esp,0x40
        ret  0xc
    }
}
