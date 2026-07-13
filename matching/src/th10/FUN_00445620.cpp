// 00445620: FUN_00445620
// Original size: 656 bytes, actual code: 166 instructions
extern "C" void FUN_004458b0(void);

extern "C" __declspec(naked) void FUN_00445620(void) {
    __asm {
        sub  esp,0x18
        mov  edx,ecx
        fld  DWORD PTR [edx+0x340]
        push  ebx
        fadd  DWORD PTR [edx+0x334]
        push  ebp
        mov  ebp,DWORD PTR [edx+0x358]
        mov  eax,ebp
        fstp  DWORD PTR [esp+0x14]
        mov  ecx,DWORD PTR [esp+0x14]
        fld  DWORD PTR [edx+0x344]
        push  esi
        fadd  DWORD PTR [edx+0x338]
        push  edi
        mov  DWORD PTR [esp+0x10],0xc0490fdb
        fstp  DWORD PTR [esp+0x20]
        fld  DWORD PTR [edx+0x348]
        fadd  DWORD PTR [edx+0x33c]
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR [esp+0x20]
        mov  DWORD PTR [eax+0x4],ecx
        fstp  DWORD PTR [esp+0x24]
        mov  ecx,DWORD PTR [esp+0x24]
        fld  DWORD PTR [ebp+0x4a4]
        mov  DWORD PTR [eax+0x8],ecx
        fadd  DWORD PTR [ebp+0x14]
        fst  DWORD PTR [ebp+0x14]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jp loc_004456CA
        lea  eax,[ebp+0x30]
        mov  ecx,0xb
        mov  edi,edi
    loc_004456A0:
        fld  DWORD PTR [eax-0x1c]
        add  eax,0x54
        dec  ecx
        fadd  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [eax-0x70]
        fld  DWORD PTR [eax-0x54]
        fadd  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [eax-0x54]
        fld  DWORD PTR [eax-0x38]
        fadd  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [eax-0x38]
        jne loc_004456A0
    loc_004456CA:
        fld  DWORD PTR [ebp+0x4a4]
        fadd  DWORD PTR [ebp+0x18]
        fst  DWORD PTR [ebp+0x18]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jp loc_0044571A
        lea  eax,[ebp+0x34]
        mov  ecx,0xb
        jmp loc_004456F0
        nop
    loc_004456F0:
        fld  DWORD PTR [eax-0x1c]
        add  eax,0x54
        dec  ecx
        fadd  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [eax-0x70]
        fld  DWORD PTR [eax-0x54]
        fadd  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [eax-0x54]
        fld  DWORD PTR [eax-0x38]
        fadd  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [eax-0x38]
        jne loc_004456F0
    loc_0044571A:
        mov  eax,DWORD PTR [edx+0x2fc]
        lea  edi,[ebp+0x1c]
        mov  DWORD PTR [ebp+0x10],eax
        mov  DWORD PTR [esp+0x18],edi
        lea  esi,[ebp+0x3a0]
        mov  ebx,0x1f
        jmp loc_00445740
        nop
        mov  edi,edi
    loc_00445740:
        fld  DWORD PTR [ebp+0x4a4]
        fadd  DWORD PTR [edi+0x14]
        fst  DWORD PTR [edi+0x14]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jp loc_0044578B
        lea  eax,[ebp+0x30]
        mov  ecx,0xb
    loc_00445761:
        fld  DWORD PTR [eax-0x1c]
        add  eax,0x54
        dec  ecx
        fadd  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [eax-0x70]
        fld  DWORD PTR [eax-0x54]
        fadd  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [eax-0x54]
        fld  DWORD PTR [eax-0x38]
        fadd  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [eax-0x38]
        jne loc_00445761
    loc_0044578B:
        fld  DWORD PTR [edi+0x18]
        fadd  DWORD PTR [ebp+0x4a4]
        fst  DWORD PTR [edi+0x18]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jp loc_004457DA
        lea  eax,[ebp+0x34]
        mov  ecx,0xb
        nop
    loc_004457B0:
        fld  DWORD PTR [eax-0x1c]
        add  eax,0x54
        dec  ecx
        fadd  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [eax-0x70]
        fld  DWORD PTR [eax-0x54]
        fadd  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [eax-0x54]
        fld  DWORD PTR [eax-0x38]
        fadd  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [eax-0x38]
        jne loc_004457B0
    loc_004457DA:
        mov  ecx,DWORD PTR [edx+0x2fc]
        mov  DWORD PTR [edi+0x10],ecx
        mov  ecx,DWORD PTR [esp+0x10]
        mov  BYTE PTR [edi+0x13],0x0
        fld  DWORD PTR [esi+0x84]
        fadd  DWORD PTR [esi]
        fst  DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x14]
        fstp  DWORD PTR [esi]
        push  eax
        push  ecx
        mov  ecx,edi
        call FUN_004458b0
        fld  DWORD PTR [edx+0x340]
        fadd  DWORD PTR [edx+0x334]
        add  edi,0x1c
        fld  DWORD PTR [edx+0x338]
        add  esi,0x4
        dec  ebx
        fadd  DWORD PTR [edx+0x344]
        fld  DWORD PTR [edx+0x348]
        fadd  DWORD PTR [edx+0x33c]
        fstp  DWORD PTR [esp+0x24]
        fxch  st(1)
        fadd  DWORD PTR [edi-0x1c]
        fstp  DWORD PTR [edi-0x1c]
        fadd  DWORD PTR [edi-0x18]
        fstp  DWORD PTR [edi-0x18]
        fld  DWORD PTR [esp+0x24]
        fadd  DWORD PTR [edi-0x14]
        fstp  DWORD PTR [edi-0x14]
        fld  DWORD PTR [esp+0x10]
        fadd  DWORD PTR ds:0x470b6c
        fstp  DWORD PTR [esp+0x10]
        jne loc_00445740
        mov  esi,DWORD PTR [esp+0x18]
        mov  ecx,0x7
        rep movsd
        pop  edi
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0x18
        ret
    }
}
