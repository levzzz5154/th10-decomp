// 0041D3D0: FUN_0041d3d0
// Original size: 1008 bytes, actual code: 288 instructions
extern "C" void FUN_0041f7a0(void);
extern "C" void FUN_0041f800(void);
extern "C" void FUN_004267f0(void);
extern "C" void FUN_0043dd10(void);
extern "C" void FUN_0043ee30(void);
extern "C" void FUN_00448db0(void);
extern "C" void FUN_0044bf40(void);

extern "C" __declspec(naked) void FUN_0041d3d0(void) {
    __asm {
        sub  esp,0x1c
        push  ebp
        mov  ebp,ecx
        mov  eax,DWORD PTR [ebp+0x0]
        push  esi
        call  DWORD PTR [eax]
        mov  eax,DWORD PTR [ebp+0x404]
        test  eax,eax
        je loc_0041D4CF
        test  al,0x1
        je loc_0041D3F6
        mov  edx,DWORD PTR [ebp+0x0]
        mov  ecx,ebp
        call  DWORD PTR [edx+0x24]
    loc_0041D3F6:
        test  BYTE PTR [ebp+0x404],0x10
        je loc_0041D407
        mov  eax,DWORD PTR [ebp+0x0]
        mov  ecx,ebp
        call  DWORD PTR [eax+0x28]
    loc_0041D407:
        test  BYTE PTR [ebp+0x404],0x20
        je loc_0041D418
        mov  edx,DWORD PTR [ebp+0x0]
        mov  ecx,ebp
        call  DWORD PTR [edx+0x2c]
    loc_0041D418:
        test  BYTE PTR [ebp+0x404],0x40
        je loc_0041D429
        mov  eax,DWORD PTR [ebp+0x0]
        mov  ecx,ebp
        call  DWORD PTR [eax+0x30]
    loc_0041D429:
        mov  eax,DWORD PTR [ebp+0x404]
        test  ah,0x1
        je loc_0041D43C
        mov  edx,DWORD PTR [ebp+0x0]
        mov  ecx,ebp
        call  DWORD PTR [edx+0x34]
    loc_0041D43C:
        mov  al,BYTE PTR [ebp+0x404]
        test  al,al
        jns loc_0041D44E
        mov  eax,DWORD PTR [ebp+0x0]
        mov  ecx,ebp
        call  DWORD PTR [eax+0x38]
    loc_0041D44E:
        test  DWORD PTR [ebp+0x404],0x8000c00
        je loc_0041D462
        mov  edx,DWORD PTR [ebp+0x0]
        mov  ecx,ebp
        call  DWORD PTR [edx+0x3c]
    loc_0041D462:
        test  DWORD PTR [ebp+0x404],0x100000
        je loc_0041D476
        mov  eax,DWORD PTR [ebp+0x0]
        mov  ecx,ebp
        call  DWORD PTR [eax+0x40]
    loc_0041D476:
        test  DWORD PTR [ebp+0x404],0x200000
        je loc_0041D48A
        mov  edx,DWORD PTR [ebp+0x0]
        mov  ecx,ebp
        call  DWORD PTR [edx+0x44]
    loc_0041D48A:
        test  DWORD PTR [ebp+0x404],0x4000000
        je loc_0041D49E
        mov  eax,DWORD PTR [ebp+0x0]
        mov  ecx,ebp
        call  DWORD PTR [eax+0x48]
    loc_0041D49E:
        mov  eax,DWORD PTR [ebp+0x404]
        test  ah,ah
        jns loc_0041D4CF
        mov  ecx,DWORD PTR [ebp+0x160]
        test  ecx,ecx
        jg loc_0041D4BF
        xor  eax,0x8000
        mov  DWORD PTR [ebp+0x404],eax
        jmp loc_0041D4CF
    loc_0041D4BF:
        push  0xbf800000
        lea  esi,[ebp+0x15c]
        call FUN_0044bf40
    loc_0041D4CF:
        fld  DWORD PTR [ebp+0x40]
        fcomp DWORD PTR [ebp+0x434]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x48]
        fnstsw ax
        test  ah,0x5
        jp loc_0041D50D
        fadd  DWORD PTR [ebp+0x40]
        fst  DWORD PTR [ebp+0x40]
        fcomp DWORD PTR [ebp+0x434]
        fnstsw ax
        test  ah,0x41
        jne loc_0041D592
        mov  ecx,DWORD PTR [ebp+0x434]
        mov  DWORD PTR [ebp+0x40],ecx
        jmp loc_0041D592
    loc_0041D50D:
        fadd  DWORD PTR [ebp+0x4c]
        fstp  DWORD PTR [ebp+0x4c]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x30]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x34]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x38]
        fstp  DWORD PTR [esp+0x20]
        fxch  st(1)
        fadd  DWORD PTR [ebp+0x24]
        fstp  DWORD PTR [ebp+0x24]
        fadd  DWORD PTR [ebp+0x28]
        fstp  DWORD PTR [ebp+0x28]
        fld  DWORD PTR [esp+0x20]
        fadd  DWORD PTR [ebp+0x2c]
        fstp  DWORD PTR [ebp+0x2c]
        fld  DWORD PTR [ebp+0x43c]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x41
        jne loc_0041D592
        fld  DWORD PTR [ebp+0x4c]
        fadd  DWORD PTR [ebp+0x40]
        fcomp DWORD PTR [ebp+0x43c]
        fnstsw ax
        test  ah,0x41
        jne loc_0041D592
        fld  DWORD PTR [ebp+0x43c]
        fsub  DWORD PTR [ebp+0x4c]
        fst  DWORD PTR [ebp+0x40]
        fstp  DWORD PTR [ebp+0x434]
        fld  DWORD PTR [ebp+0x40]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x41
        jnp loc_0041D5F2
    loc_0041D592:
        mov  eax,DWORD PTR [ebp+0x414]
        test  eax,eax
        jg loc_0041D5FD
        mov  edx,DWORD PTR [ebp+0x40]
        mov  eax,DWORD PTR [ebp+0x3c]
        push  edx
        push  eax
        lea  ecx,[esp+0x14]
        call FUN_0041f800
        fld  DWORD PTR [esp+0xc]
        fadd  DWORD PTR [ebp+0x24]
        mov  edx,DWORD PTR [ebp+0x44]
        lea  ecx,[ebp+0x24]
        push  edx
        fstp  DWORD PTR [esp+0x10]
        mov  eax,edx
        fld  DWORD PTR [esp+0x14]
        push  eax
        fadd  DWORD PTR [ecx+0x4]
        fstp  DWORD PTR [esp+0x18]
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [ecx+0x8]
        fstp  DWORD PTR [esp+0x1c]
        call FUN_0041f7a0
        test  eax,eax
        je loc_0041D60D
        mov  ecx,edx
        push  ecx
        push  edx
        lea  ecx,[esp+0x14]
        call FUN_0041f7a0
        test  eax,eax
        je loc_0041D60D
    loc_0041D5F2:
        pop  esi
        mov  eax,0x1
        pop  ebp
        add  esp,0x1c
        ret
    loc_0041D5FD:
        push  0xbf800000
        lea  esi,[ebp+0x410]
        call FUN_0044bf40
    loc_0041D60D:
        fld  DWORD PTR [ebp+0x40]
        fcomp DWORD PTR ds:0x470b48
        fnstsw ax
        test  ah,0x41
        jne loc_0041D750
        fld  DWORD PTR [ebp+0x44]
        fcomp DWORD PTR ds:0x470bd4
        fnstsw ax
        test  ah,0x41
        jne loc_0041D750
        fld  DWORD PTR [ebp+0x40]
        mov  eax,DWORD PTR [ebp+0x3c]
        fmul  DWORD PTR ds:0x470c18
        push  ecx
        lea  ecx,[esp+0x10]
        fstp  DWORD PTR [esp]
        push  eax
        call FUN_0041f800
        fld  DWORD PTR [esp+0xc]
        fadd  DWORD PTR [ebp+0x24]
        fstp  DWORD PTR [esp+0xc]
        fld  DWORD PTR [esp+0x10]
        fadd  DWORD PTR [ebp+0x28]
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [esp+0x14]
        fadd  DWORD PTR [ebp+0x2c]
        fstp  DWORD PTR [esp+0x14]
        fld  DWORD PTR [ebp+0x44]
        fcomp DWORD PTR ds:0x470bcc
        fld  DWORD PTR [ebp+0x44]
        fnstsw ax
        test  ah,0x5
        jp loc_0041D68B
        fmul  DWORD PTR ds:0x470b0c
        jmp loc_0041D69A
    loc_0041D68B:
        fadd  DWORD PTR ds:0x470b48
        fmul  DWORD PTR ds:0x470b0c
        fsubr DWORD PTR [ebp+0x44]
    loc_0041D69A:
        mov  edx,DWORD PTR [ebp+0x3c]
        fstp  DWORD PTR [esp+0x8]
        fld  DWORD PTR [ebp+0x40]
        push  ecx
        fmul  DWORD PTR ds:0x470cc0
        mov  ecx,DWORD PTR [esp+0xc]
        lea  eax,[esp+0x10]
        fstp  DWORD PTR [esp]
        push  ecx
        mov  ecx,DWORD PTR ds:0x477834
        push  edx
        call FUN_004267f0
        cmp  eax,0x1
        jne loc_0041D6FE
        mov  edx,DWORD PTR ds:0x477834
        mov  eax,DWORD PTR [ebp+0x0]
        push  0x0
        lea  ecx,[esp+0x1c]
        push  ecx
        add  edx,0x3c0
        push  edx
        mov  ecx,ebp
        mov  DWORD PTR [esp+0x24],0x42000000
        mov  DWORD PTR [esp+0x28],0x42000000
        mov  DWORD PTR [esp+0x2c],0x0
        call  DWORD PTR [eax+0x18]
        jmp loc_0041D750
    loc_0041D6FE:
        cmp  eax,0x2
        jne loc_0041D750
        mov  eax,DWORD PTR [ebp+0x14]
        cdq
        mov  ecx,0x5
        idiv  ecx
        test  edx,edx
        jne loc_0041D750
        mov  eax,ds:0x4776f0
        mov  ecx,DWORD PTR [eax+0x3e0b50]
        push  ebx
        push  edi
        mov  edi,DWORD PTR ds:0x477834
        push  0x1b2
        lea  edx,[esp+0x14]
        push  edx
        add  edi,0x3c0
        push  ecx
        call FUN_00448db0
        mov  edx,DWORD PTR [ebp+0x24]
        push  edx
        mov  ebx,0x1c
        mov  esi,0x492590
        call FUN_0043dd10
        pop  edi
        pop  ebx
    loc_0041D750:
        mov  ecx,DWORD PTR [ebp+0x994]
        fld  DWORD PTR [ebp+0x44]
        fdiv  DWORD PTR [ecx+0x34]
        mov  esi,DWORD PTR [ebp+0x95c]
        lea  eax,[ebp+0x600]
        mov  ecx,0x8
        or   esi,ecx
        mov  DWORD PTR [eax+0x35c],esi
        push  eax
        fstp  DWORD PTR [eax+0x3c]
        fld  DWORD PTR [ebp+0x40]
        mov  edx,DWORD PTR [ebp+0x994]
        fdiv  DWORD PTR [edx+0x30]
        or   DWORD PTR [eax+0x35c],ecx
        fstp  DWORD PTR [eax+0x40]
        call FUN_0043ee30
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [ebp+0x4c]
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0041D7B1
        add  ebp,0x9ac
        push  ebp
        call FUN_0043ee30
    loc_0041D7B1:
        pop  esi
        xor  eax,eax
        pop  ebp
        add  esp,0x1c
        ret
    }
}
