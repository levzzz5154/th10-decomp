// 0041E700: FUN_0041e700
// Original size: 1024 bytes, actual code: 283 instructions
extern "C" void FUN_00405410(void);
extern "C" void FUN_0041f800(void);
extern "C" void FUN_004267f0(void);
extern "C" void FUN_0043dd10(void);
extern "C" void FUN_0043ee30(void);
extern "C" void FUN_004451c0(void);
extern "C" void FUN_00448db0(void);
extern "C" void FUN_0044bc10(void);
extern "C" void FUN_E886EA7F(void);

extern "C" __declspec(naked) void FUN_0041e700(void) {
    __asm {
        sub  esp,0x1c
        push  ebp
        mov  ebp,ecx
        fld  DWORD PTR [ebp+0x40]
        fcomp DWORD PTR [ebp+0x444]
        fnstsw ax
        test  ah,0x5
        jp loc_0041E73B
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x48]
        fadd  DWORD PTR [ebp+0x40]
        fst  DWORD PTR [ebp+0x40]
        fcomp DWORD PTR [ebp+0x444]
        fnstsw ax
        test  ah,0x41
        jne loc_0041E73B
        mov  eax,DWORD PTR [ebp+0x444]
        mov  DWORD PTR [ebp+0x40],eax
    loc_0041E73B:
        fld  DWORD PTR ds:0x476f78
        push  ecx
        fmul  DWORD PTR [ebp+0x440]
        mov  ecx,DWORD PTR [ebp+0x3c]
        fstp  DWORD PTR [esp]
        push  ecx
        call FUN_0044bc10
        fstp  DWORD PTR [ebp+0x3c]
        test  BYTE PTR [ebp+0x468],0x1
        je loc_0041E785
        mov  edx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [edx+0x10]
        test  eax,eax
        je loc_0041E785
        add  eax,0x1068
        mov  edx,DWORD PTR [eax]
        lea  ecx,[ebp+0x24]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ecx+0x4],edx
        mov  eax,DWORD PTR [eax+0x8]
        mov  DWORD PTR [ecx+0x8],eax
    loc_0041E785:
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x430]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x434]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x438]
        fstp  DWORD PTR [esp+0x1c]
        fxch  st(1)
        fadd  DWORD PTR [ebp+0x24]
        fstp  DWORD PTR [ebp+0x24]
        fadd  DWORD PTR [ebp+0x28]
        fstp  DWORD PTR [ebp+0x28]
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [ebp+0x2c]
        fstp  DWORD PTR [ebp+0x2c]
        mov  eax,DWORD PTR [ebp+0xc]
        add  eax,0xfffffffe
        cmp  eax,0x3
        ja loc_0041E886
        jmp  DWORD PTR [eax*4+0x41ea30]
        mov  ecx,DWORD PTR [ebp+0x14]
        cmp  ecx,DWORD PTR [ebp+0x454]
        jl loc_0041E886
        push  0x0
        lea  eax,[ebp+0x10]
        call FUN_00405410
        mov  DWORD PTR [ebp+0xc],0x4
        jmp loc_0041E886
        mov  eax,DWORD PTR [ebp+0x458]
        cmp  DWORD PTR [ebp+0x14],eax
        mov  DWORD PTR [esp+0x4],eax
        jl loc_0041E85E
        push  0x0
        lea  eax,[ebp+0x10]
        call FUN_00405410
        mov  edx,DWORD PTR [ebp+0x44c]
        mov  DWORD PTR [ebp+0xc],0x2
        mov  DWORD PTR [ebp+0x44],edx
        mov  eax,DWORD PTR [ebp+0x14]
        cmp  eax,DWORD PTR [ebp+0x45c]
        jl loc_0041E886
        push  0x0
        lea  eax,[ebp+0x10]
        call FUN_00405410
        mov  DWORD PTR [ebp+0xc],0x5
        mov  eax,DWORD PTR [ebp+0x460]
        cmp  DWORD PTR [ebp+0x14],eax
        mov  DWORD PTR [esp+0x4],eax
        jl loc_0041E870
        mov  eax,0x1
        pop  ebp
        add  esp,0x1c
        ret
    loc_0041E85E:
        fld  DWORD PTR [ebp+0x44c]
        fmul  DWORD PTR [ebp+0x18]
        fidiv DWORD PTR [esp+0x4]
        fstp  DWORD PTR [ebp+0x44]
        jmp loc_0041E886
    loc_0041E870:
        fld  DWORD PTR [ebp+0x44c]
        fld  st(0)
        fmul  DWORD PTR [ebp+0x18]
        fidiv DWORD PTR [esp+0x4]
        fsubr st,st(1)
        fstp  DWORD PTR [ebp+0x44]
        fstp  st(0)
    loc_0041E886:
        mov  eax,DWORD PTR [ebp+0xc]
        cmp  eax,0x4
        push  esi
        je loc_0041E898
        cmp  eax,0x2
        jne loc_0041E9C7
    loc_0041E898:
        fld  DWORD PTR [ebp+0x40]
        fcomp DWORD PTR ds:0x470b48
        fnstsw ax
        test  ah,0x41
        jne loc_0041E9C7
        fld  DWORD PTR [ebp+0x40]
        push  ecx
        fmul  DWORD PTR ds:0x470c18
        mov  ecx,DWORD PTR [ebp+0x3c]
        fstp  DWORD PTR [esp]
        push  ecx
        lea  ecx,[esp+0x14]
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
        jp loc_0041E902
        fmul  DWORD PTR ds:0x470b0c
        jmp loc_0041E911
    loc_0041E902:
        fadd  DWORD PTR ds:0x470b48
        fmul  DWORD PTR ds:0x470cc4
        fsubr DWORD PTR [ebp+0x44]
    loc_0041E911:
        mov  eax,DWORD PTR [ebp+0x3c]
        fstp  DWORD PTR [esp+0x8]
        fld  DWORD PTR [ebp+0x40]
        mov  edx,DWORD PTR [esp+0x8]
        fmul  DWORD PTR ds:0x470cc0
        push  ecx
        mov  ecx,DWORD PTR ds:0x477834
        fstp  DWORD PTR [esp]
        push  edx
        push  eax
        lea  eax,[esp+0x18]
        call FUN_004267f0
        cmp  eax,0x1
        jne loc_0041E975
        mov  ecx,DWORD PTR ds:0x477834
        mov  edx,DWORD PTR [ebp+0x0]
        push  0x0
        lea  eax,[esp+0x1c]
        add  ecx,0x3c0
        push  eax
        push  ecx
        mov  ecx,ebp
        mov  DWORD PTR [esp+0x24],0x42000000
        mov  DWORD PTR [esp+0x28],0x42000000
        mov  DWORD PTR [esp+0x2c],0x0
        call  DWORD PTR [edx+0x18]
        jmp loc_0041E9C7
    loc_0041E975:
        cmp  eax,0x2
        jne loc_0041E9C7
        mov  eax,DWORD PTR [ebp+0x14]
        cdq
        mov  ecx,0x5
        idiv  ecx
        test  edx,edx
        jne loc_0041E9C7
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
    loc_0041E9C7:
        mov  ecx,DWORD PTR [ebp+0x9b0]
        fld  DWORD PTR [ebp+0x44]
        fdiv  DWORD PTR [ecx+0x34]
        mov  esi,DWORD PTR [ebp+0x978]
        lea  eax,[ebp+0x61c]
        mov  ecx,0x8
        or   esi,ecx
        mov  DWORD PTR [eax+0x35c],esi
        push  eax
        fstp  DWORD PTR [eax+0x3c]
        fld  DWORD PTR [ebp+0x40]
        mov  edx,DWORD PTR [ebp+0x9b0]
        fdiv  DWORD PTR [edx+0x30]
        or   DWORD PTR [eax+0x35c],ecx
        fstp  DWORD PTR [eax+0x40]
        call FUN_0043ee30
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [ebp+0x4c]
        pop  esi
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0041EA29
        add  ebp,0x9c8
        push  ebp
        call FUN_0043ee30
    loc_0041EA29:
        xor  eax,eax
        pop  ebp
        add  esp,0x1c
        ret
        sub  eax,ebp
        inc  ecx
        add  bl,bl
        out  0x41,eax
        add  BYTE PTR [eax],al
        call FUN_E886EA7F
        inc  ecx
        add  BYTE PTR [esi-0x75],dl
        int1
        fld  DWORD PTR [esi+0x24]
        push  edi
        fadd  DWORD PTR ds:0x470b4c
        push  0x3fc90fdb
        lea  edi,[esi+0x61c]
        fstp  DWORD PTR [esi+0x950]
        fld  DWORD PTR [esi+0x28]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [esi+0x954]
        mov  eax,DWORD PTR [esi+0x2c]
        mov  DWORD PTR [esi+0x958],eax
        mov  ecx,DWORD PTR [esi+0x3c]
        push  ecx
        call FUN_0044bc10
        fstp  DWORD PTR [edi+0x2c]
        mov  eax,DWORD PTR [edi+0x35c]
        mov  ecx,DWORD PTR ds:0x491c10
        or   eax,0x4
        mov  DWORD PTR [edi+0x35c],eax
        mov  eax,edi
        call FUN_004451c0
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [esi+0x4c]
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0041EAE8
        fld  DWORD PTR [esi+0x24]
        mov  ecx,DWORD PTR ds:0x491c10
        fadd  DWORD PTR ds:0x470b4c
        lea  eax,[esi+0x9c8]
        fstp  DWORD PTR [esi+0xcfc]
        fld  DWORD PTR [esi+0x28]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [esi+0xd00]
        mov  edx,DWORD PTR [esi+0x2c]
        mov  DWORD PTR [esi+0xd04],edx
        call FUN_004451c0
    loc_0041EAE8:
        pop  edi
        xor  eax,eax
        pop  esi
        ret
    }
}
