// 004452F0: FUN_004452f0
// Original size: 816 bytes, actual code: 197 instructions
extern "C" void FUN_004458b0(void);
extern "C" void FUN_0044bb90(void);
extern "C" void _free(void);
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_004452f0(void) {
    __asm {
        mov  eax,DWORD PTR [edi+0x358]
        sub  esp,0x28
        test  eax,eax
        je loc_00445310
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [edi+0x358],0x0
    loc_00445310:
        push  ebx
        push  ebp
        push  esi
        push  0x4b0
        call _malloc
        mov  ebx,eax
        add  esp,0x4
        mov  ecx,0x4918b0
        mov  DWORD PTR [edi+0x358],ebx
        mov  DWORD PTR [edi+0x398],0x445620
        mov  DWORD PTR [edi+0x39c],0x445880
        call FUN_0044bb90
        fmul  DWORD PTR ds:0x470c7c
        mov  ecx,0x4918b0
        fstp  DWORD PTR [ebx+0x4a4]
        call FUN_0044bb90
        fmul  DWORD PTR ds:0x470c7c
        mov  eax,ebx
        mov  DWORD PTR [esp+0x10],0xc0490fdb
        lea  esi,[ebx+0x1c]
        fstp  DWORD PTR [ebx+0x4a8]
        fld  DWORD PTR [edi+0x340]
        fadd  DWORD PTR [edi+0x334]
        fstp  DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR [esp+0x1c]
        fld  DWORD PTR [edi+0x344]
        fadd  DWORD PTR [edi+0x338]
        fstp  DWORD PTR [esp+0x20]
        mov  edx,DWORD PTR [esp+0x20]
        fld  DWORD PTR [edi+0x348]
        fadd  DWORD PTR [edi+0x33c]
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [eax+0x4],edx
        mov  DWORD PTR [ebx+0xc],0x3f800000
        fstp  DWORD PTR [esp+0x24]
        mov  ecx,DWORD PTR [esp+0x24]
        mov  DWORD PTR [eax+0x8],ecx
        mov  eax,0x3f000000
        mov  ecx,0x4918b0
        mov  DWORD PTR [ebx+0x14],eax
        mov  DWORD PTR [ebx+0x18],eax
        call FUN_0044bb90
        fmul  DWORD PTR ds:0x470c78
        lea  edx,[ebx+0x3a0]
        mov  DWORD PTR [esp+0x14],0x1f
        fstp  DWORD PTR [esp+0xc]
        nop
    loc_004453F0:
        fld  DWORD PTR [esp+0x10]
        fcomp DWORD PTR ds:0x470b18
        fnstsw ax
        test  ah,0x1
        jne loc_0044540F
        fld  DWORD PTR [esp+0x10]
        fsub  DWORD PTR ds:0x470b14
        fstp  DWORD PTR [esp+0x10]
    loc_0044540F:
        mov  ebp,DWORD PTR [esp+0x10]
        push  0x3f000000
        push  ebp
        lea  ecx,[esp+0x24]
        mov  DWORD PTR [esi+0xc],0x3f800000
        call FUN_004458b0
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR ds:0x470b0c
        xor  ecx,ecx
        mov  DWORD PTR [esi+0x8],0x0
        fstp  DWORD PTR [esi+0x14]
        fld  DWORD PTR [esp+0x20]
        fadd  DWORD PTR ds:0x470b0c
        fstp  DWORD PTR [esi+0x18]
        mov  eax,ds:0x4918b0
        xor  eax,0x9630
        sub  eax,0x6553
        mov  cx,ax
        shr  cx,0xe
        shl  eax,0x2
        mov  ebx,DWORD PTR ds:0x4918b4
        add  ecx,eax
        mov  WORD PTR ds:0x4918b0,cx
        mov  eax,ds:0x4918b0
        xor  eax,0x9630
        xor  ecx,ecx
        sub  eax,0x6553
        mov  cx,ax
        shr  cx,0xe
        shl  eax,0x2
        inc  ebx
        add  ecx,eax
        movzx eax,cx
        mov  WORD PTR ds:0x4918b0,cx
        mov  ecx,eax
        shl  ecx,0x10
        or   ecx,eax
        inc  ebx
        test  ecx,ecx
        mov  DWORD PTR [esp+0x18],ecx
        mov  DWORD PTR ds:0x4918b4,ebx
        fild  DWORD PTR [esp+0x18]
        jge loc_004454BC
        fadd  DWORD PTR ds:0x470b98
    loc_004454BC:
        mov  eax,DWORD PTR [esp+0xc]
        fmul  DWORD PTR ds:0x470bec
        mov  DWORD PTR [edx+0x84],eax
        xor  ecx,ecx
        fsub  DWORD PTR ds:0x470afc
        fmul  DWORD PTR ds:0x470bd0
        fadd  DWORD PTR ds:0x470c28
        fstp  DWORD PTR [edx]
        mov  eax,ds:0x4918b0
        xor  eax,0x9630
        sub  eax,0x6553
        mov  cx,ax
        shr  cx,0xe
        shl  eax,0x2
        mov  ebx,DWORD PTR ds:0x4918b4
        add  ecx,eax
        mov  WORD PTR ds:0x4918b0,cx
        mov  eax,ds:0x4918b0
        xor  eax,0x9630
        xor  ecx,ecx
        sub  eax,0x6553
        mov  cx,ax
        shr  cx,0xe
        shl  eax,0x2
        inc  ebx
        add  ecx,eax
        movzx eax,cx
        mov  WORD PTR ds:0x4918b0,cx
        mov  ecx,eax
        shl  ecx,0x10
        or   ecx,eax
        inc  ebx
        test  ecx,ecx
        mov  DWORD PTR [esp+0x18],ecx
        mov  DWORD PTR ds:0x4918b4,ebx
        fild  DWORD PTR [esp+0x18]
        jge loc_00445552
        fadd  DWORD PTR ds:0x470b98
    loc_00445552:
        fmul  DWORD PTR ds:0x470bec
        fsub  DWORD PTR ds:0x470afc
        fmul  DWORD PTR ds:0x470c74
        fadd  DWORD PTR [esp+0xc]
        fst  DWORD PTR [esp+0xc]
        fcomp DWORD PTR ds:0x470c70
        fnstsw ax
        test  ah,0x5
        jp loc_00445583
        mov  DWORD PTR [esp+0xc],0xbd888889
        jmp loc_0044559C
    loc_00445583:
        fld  DWORD PTR [esp+0xc]
        fcomp DWORD PTR ds:0x470c78
        fnstsw ax
        test  ah,0x41
        jne loc_0044559C
        mov  DWORD PTR [esp+0xc],0x3d888889
    loc_0044559C:
        mov  eax,DWORD PTR [edx]
        push  eax
        push  ebp
        mov  ecx,esi
        call FUN_004458b0
        fld  DWORD PTR [edi+0x340]
        fadd  DWORD PTR [edi+0x334]
        mov  eax,DWORD PTR [esp+0x14]
        fld  DWORD PTR [edi+0x338]
        add  esi,0x1c
        fadd  DWORD PTR [edi+0x344]
        add  edx,0x4
        fld  DWORD PTR [edi+0x348]
        dec  eax
        fadd  DWORD PTR [edi+0x33c]
        mov  DWORD PTR [esp+0x14],eax
        fstp  DWORD PTR [esp+0x30]
        fxch  st(1)
        fadd  DWORD PTR [esi-0x1c]
        fstp  DWORD PTR [esi-0x1c]
        fadd  DWORD PTR [esi-0x18]
        fstp  DWORD PTR [esi-0x18]
        fld  DWORD PTR [esp+0x30]
        fadd  DWORD PTR [esi-0x14]
        fstp  DWORD PTR [esi-0x14]
        fld  DWORD PTR [esp+0x10]
        fadd  DWORD PTR ds:0x470b6c
        fstp  DWORD PTR [esp+0x10]
        jne loc_004453F0
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0x28
        ret
    }
}
