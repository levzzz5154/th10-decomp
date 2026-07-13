// 00408D60: FUN_00408d60
// Original size: 1120 bytes, actual code: 271 instructions
extern "C" void FUN_0043e5a0(void);
extern "C" void FUN_0043ee30(void);
extern "C" void FUN_00449350(void);
extern "C" void FUN_00449470(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00408d60(void) {
    __asm {
        mov  al,BYTE PTR [edi+0x378c]
        sub  esp,0x1c
        test  al,0x1
        je loc_00409178
        cmp  DWORD PTR [edi+0x3738],0x3c
        jl loc_00408D86
        mov  eax,ds:0x4776e8
        and  DWORD PTR [eax+0x2a18],0xfffffffe
    loc_00408D86:
        cmp  DWORD PTR [edi+0x3738],0x12c
        push  ebx
        push  ebp
        push  esi
        jl loc_00408DE2
        test  BYTE PTR [edi+0x378c],0x8
        jne loc_00408DE2
        mov  ecx,DWORD PTR [edi+0x3794]
        mov  eax,0x66666667
        imul  ecx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        add  edx,eax
        mov  eax,ecx
        mov  ecx,DWORD PTR [edi+0x3798]
        sub  eax,edx
        cdq
        sub  ecx,0x12c
        idiv  ecx
        mov  ecx,DWORD PTR [edi+0x3790]
        mov  esi,0xa
        sub  ecx,eax
        mov  eax,ecx
        cdq
        idiv  esi
        sub  ecx,edx
        mov  DWORD PTR [edi+0x3790],ecx
    loc_00408DE2:
        lea  edx,[edi+0x10]
        push  edx
        call FUN_0043ee30
        lea  eax,[edi+0x3bc]
        push  eax
        call FUN_0043ee30
        mov  edx,DWORD PTR [edi+0x3738]
        mov  ecx,DWORD PTR [edi+0x3740]
        mov  DWORD PTR [edi+0x3734],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00408E42
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00408E42
        fld  DWORD PTR [edi+0x373c]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [edi+0x3738],edx
        fstp  DWORD PTR [edi+0x373c]
        jmp loc_00408E5B
    loc_00408E42:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [edi+0x373c]
        fst  DWORD PTR [edi+0x373c]
        call FUN_00463b2c
        mov  DWORD PTR [edi+0x3738],eax
    loc_00408E5B:
        cmp  DWORD PTR [edi+0x3738],0x78
        jl loc_00408F7C
        test  BYTE PTR [edi+0x378c],0x4
        jne loc_00408EFB
        mov  ecx,DWORD PTR ds:0x477834
        fld  DWORD PTR [ecx+0x3c4]
        fcomp DWORD PTR ds:0x470c80
        fnstsw ax
        test  ah,0x5
        jp loc_00408F7C
        lea  ebp,[edi+0x768]
        mov  ebx,0x3
        nop
    loc_00408EA0:
        mov  esi,0x3
        mov  eax,ebp
        call FUN_00449470
        add  ebp,0x4
        dec  ebx
        jne loc_00408EA0
        lea  eax,[edi+0xa7c]
        mov  ecx,0x8
        nop
    loc_00408EC0:
        mov  WORD PTR [eax],0x3
        add  eax,0x3ac
        dec  ecx
        jne loc_00408EC0
        lea  eax,[edi+0x27dc]
        mov  ecx,0x5
        jmp loc_00408EE0
        lea  ebx,[ebx+0x0]
    loc_00408EE0:
        mov  WORD PTR [eax],0x3
        add  eax,0x3ac
        dec  ecx
        jne loc_00408EE0
        mov  eax,DWORD PTR [edi+0x378c]
        or   eax,0x4
        jmp loc_00408F76
    loc_00408EFB:
        mov  edx,DWORD PTR ds:0x477834
        fld  DWORD PTR [edx+0x3c4]
        fcomp DWORD PTR ds:0x470bf4
        fnstsw ax
        test  ah,0x41
        jne loc_00408F7C
        lea  ebp,[edi+0x768]
        mov  ebx,0x3
        nop
    loc_00408F20:
        mov  esi,0x2
        mov  eax,ebp
        call FUN_00449470
        add  ebp,0x4
        dec  ebx
        jne loc_00408F20
        lea  eax,[edi+0xa7c]
        mov  ecx,0x8
        nop
    loc_00408F40:
        mov  WORD PTR [eax],0x2
        add  eax,0x3ac
        dec  ecx
        jne loc_00408F40
        lea  eax,[edi+0x27dc]
        mov  ecx,0x5
        jmp loc_00408F60
        lea  ebx,[ebx+0x0]
    loc_00408F60:
        mov  WORD PTR [eax],0x2
        add  eax,0x3ac
        dec  ecx
        jne loc_00408F60
        mov  eax,DWORD PTR [edi+0x378c]
        and  eax,0xfffffffb
    loc_00408F76:
        mov  DWORD PTR [edi+0x378c],eax
    loc_00408F7C:
        test  BYTE PTR [edi+0x378c],0x2
        je loc_00408FEB
        mov  ecx,DWORD PTR [edi+0x3790]
        mov  esi,0x989680
        lea  ebx,[edi+0x778]
        mov  DWORD PTR [esp+0xc],0x8
        mov  edi,edi
    loc_00408FA0:
        mov  eax,ecx
        cdq
        idiv  esi
        mov  ecx,DWORD PTR ds:0x47770c
        mov  ecx,DWORD PTR [ecx+0x9ec8]
        mov  ebp,edx
        lea  edx,[eax+0x1e]
        mov  eax,ebx
        call FUN_0043e5a0
        push  ebx
        call FUN_0043ee30
        mov  eax,0x66666667
        imul  esi
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        mov  esi,eax
        mov  eax,DWORD PTR [esp+0xc]
        add  ebx,0x3ac
        dec  eax
        mov  ecx,ebp
        mov  DWORD PTR [esp+0xc],eax
        jne loc_00408FA0
        jmp loc_0040900F
    loc_00408FEB:
        mov  ecx,DWORD PTR ds:0x47770c
        mov  ecx,DWORD PTR [ecx+0x9ec8]
        lea  esi,[edi+0xed0]
        mov  edx,0x29
        mov  eax,esi
        call FUN_0043e5a0
        push  esi
        call FUN_0043ee30
    loc_0040900F:
        mov  eax,ds:0x474c68
        mov  edx,DWORD PTR ds:0x474c6c
        mov  esi,DWORD PTR ds:0x47783c
        lea  ecx,[edx+eax*2]
        add  ecx,eax
        mov  eax,DWORD PTR [edi+0x3788]
        imul  ecx,ecx,0x437c
        lea  edx,[eax+eax*8]
        shl  edx,0x4
        add  ecx,esi
        mov  eax,DWORD PTR [edx+ecx*1+0x624]
        cmp  eax,0x64
        jl loc_0040904A
        mov  eax,0x63
    loc_0040904A:
        cdq
        mov  ecx,0xa
        idiv  ecx
        mov  esi,DWORD PTR ds:0x47770c
        mov  ecx,DWORD PTR [esi+0x9ec8]
        lea  ebx,[edi+0x24d8]
        mov  ebp,edx
        lea  edx,[eax+0x1e]
        mov  eax,ebx
        call FUN_0043e5a0
        mov  ecx,DWORD PTR [esi+0x9ec8]
        lea  edx,[ebp+0x1e]
        lea  eax,[edi+0x2884]
        call FUN_0043e5a0
        mov  eax,ds:0x474c68
        mov  edx,DWORD PTR ds:0x474c6c
        mov  ebp,DWORD PTR ds:0x47783c
        lea  ecx,[edx+eax*2]
        add  ecx,eax
        mov  eax,DWORD PTR [edi+0x3788]
        imul  ecx,ecx,0x437c
        lea  edx,[eax+eax*8]
        shl  edx,0x4
        add  ecx,ebp
        mov  eax,DWORD PTR [edx+ecx*1+0x628]
        cmp  eax,0x64
        jl loc_004090BF
        mov  eax,0x63
    loc_004090BF:
        cdq
        mov  ecx,0xa
        idiv  ecx
        mov  ecx,DWORD PTR [esi+0x9ec8]
        mov  ebp,edx
        lea  edx,[eax+0x1e]
        lea  eax,[edi+0x2fdc]
        call FUN_0043e5a0
        mov  ecx,DWORD PTR [esi+0x9ec8]
        lea  edx,[ebp+0x1e]
        lea  eax,[edi+0x3388]
        call FUN_0043e5a0
        mov  esi,0x5
    loc_004090F6:
        push  ebx
        call FUN_0043ee30
        add  ebx,0x3ac
        dec  esi
        jne loc_004090F6
        mov  edx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [edx+0x10]
        fld  DWORD PTR [eax+0x1068]
        lea  esi,[edi+0x379c]
        fsub  DWORD PTR [esi]
        add  eax,0x1068
        fld  DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x491c10
        fsub  DWORD PTR [esi+0x4]
        fld  DWORD PTR [eax+0x8]
        fsub  DWORD PTR [esi+0x8]
        fstp  DWORD PTR [esp+0x18]
        fxch  st(1)
        fmul  DWORD PTR ds:0x470c84
        fstp  DWORD PTR [esp+0x1c]
        fmul  DWORD PTR ds:0x470c84
        fld  DWORD PTR [esp+0x18]
        fmul  DWORD PTR ds:0x470c84
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [esi]
        fstp  DWORD PTR [esi]
        fxch  st(1)
        fadd  DWORD PTR [esi+0x4]
        fstp  DWORD PTR [esi+0x4]
        fadd  DWORD PTR [esi+0x8]
        fstp  DWORD PTR [esi+0x8]
        mov  eax,DWORD PTR [edi+0x774]
        push  eax
        call FUN_00449350
        pop  esi
        pop  ebp
        pop  ebx
    loc_00409178:
        mov  eax,0x1
        add  esp,0x1c
        ret
    }
}
