// 0040C9D0: FUN_0040c9d0
// Original size: 640 bytes, actual code: 140 instructions
extern "C" void FUN_00413270(void);
extern "C" void FUN_0041bb00(void);
extern "C" void FUN_0044bb90(void);
extern "C" void FUN_0044bc70(void);

extern "C" __declspec(naked) void FUN_0040c9d0(void) {
    __asm {
        sub  esp,0x18
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x24]
        push  edi
        mov  ecx,0x4918b0
        call FUN_0044bb90
        fmul  DWORD PTR ds:0x470b18
        lea  edi,[ebp+0x4]
        mov  DWORD PTR [esp+0xc],0x0
        fstp  DWORD PTR [esp+0x28]
        mov  DWORD PTR [esp+0x10],edi
        nop
    loc_0040CA00:
        mov  eax,DWORD PTR [edi]
        xor  ebx,ebx
        test  eax,eax
        jle loc_0040CB9C
        nop
    loc_0040CA10:
        mov  eax,DWORD PTR [ebp+0x38]
        mov  ecx,DWORD PTR [ebp+0x34]
        mov  edx,DWORD PTR [esp+0x28]
        push  eax
        push  ecx
        push  edx
        lea  ecx,[esp+0x24]
        call FUN_00413270
        mov  eax,ds:0x4918b0
        xor  ecx,ecx
        xor  eax,0x9630
        sub  eax,0x6553
        mov  cx,ax
        shr  cx,0xe
        lea  edx,[eax*4+0x0]
        add  ecx,edx
        mov  WORD PTR ds:0x4918b0,cx
        mov  eax,ds:0x4918b0
        mov  edx,DWORD PTR ds:0x4918b4
        xor  eax,0x9630
        xor  ecx,ecx
        sub  eax,0x6553
        mov  cx,ax
        shr  cx,0xe
        shl  eax,0x2
        inc  edx
        add  ecx,eax
        movzx eax,cx
        mov  WORD PTR ds:0x4918b0,cx
        mov  ecx,eax
        shl  ecx,0x10
        or   ecx,eax
        inc  edx
        test  ecx,ecx
        mov  DWORD PTR [esp+0x14],ecx
        mov  DWORD PTR ds:0x4918b4,edx
        fild  DWORD PTR [esp+0x14]
        jge loc_0040CA9C
        fadd  DWORD PTR ds:0x470b98
    loc_0040CA9C:
        mov  eax,DWORD PTR [esp+0xc]
        mov  edx,DWORD PTR [esi+0x8]
        fmul  DWORD PTR ds:0x470d18
        push  0x400ccccd
        push  0xbfc90fdb
        fadd  DWORD PTR ds:0x470b0c
        inc  eax
        fld  DWORD PTR [esp+0x20]
        push  0xffffffff
        push  eax
        mov  eax,ds:0x477818
        fmul  st,st(1)
        fld  DWORD PTR [esp+0x2c]
        lea  ecx,[esp+0x28]
        fmul  st,st(2)
        mov  DWORD PTR [esp+0x30],edx
        fstp  DWORD PTR [esp+0x2c]
        fadd  DWORD PTR [esi]
        fstp  DWORD PTR [esp+0x28]
        fstp  st(0)
        fld  DWORD PTR [esp+0x2c]
        fadd  DWORD PTR [esi+0x4]
        fstp  DWORD PTR [esp+0x2c]
        call FUN_0041bb00
        mov  eax,ds:0x4918b0
        xor  ecx,ecx
        xor  eax,0x9630
        sub  eax,0x6553
        mov  cx,ax
        shr  cx,0xe
        lea  edx,[eax*4+0x0]
        add  ecx,edx
        mov  WORD PTR ds:0x4918b0,cx
        mov  eax,ds:0x4918b0
        mov  edx,DWORD PTR ds:0x4918b4
        xor  eax,0x9630
        xor  ecx,ecx
        sub  eax,0x6553
        mov  cx,ax
        shr  cx,0xe
        shl  eax,0x2
        inc  edx
        add  ecx,eax
        movzx eax,cx
        mov  WORD PTR ds:0x4918b0,cx
        mov  ecx,eax
        shl  ecx,0x10
        or   ecx,eax
        inc  edx
        test  ecx,ecx
        mov  DWORD PTR [esp+0x14],ecx
        mov  DWORD PTR ds:0x4918b4,edx
        fild  DWORD PTR [esp+0x14]
        jge loc_0040CB68
        fadd  DWORD PTR ds:0x470b98
    loc_0040CB68:
        fmul  DWORD PTR ds:0x470bec
        push  ecx
        fsub  DWORD PTR ds:0x470afc
        fmul  DWORD PTR ds:0x470c48
        fadd  DWORD PTR [esp+0x2c]
        fadd  DWORD PTR ds:0x470b94
        fstp  DWORD PTR [esp]
        call FUN_0044bc70
        mov  eax,DWORD PTR [edi]
        fstp  DWORD PTR [esp+0x28]
        inc  ebx
        cmp  ebx,eax
        jl loc_0040CA10
    loc_0040CB9C:
        mov  eax,DWORD PTR [esp+0xc]
        inc  eax
        add  edi,0x4
        cmp  eax,0xb
        mov  DWORD PTR [esp+0xc],eax
        jl loc_0040CA00
        mov  edi,DWORD PTR [esp+0x10]
        mov  ecx,0xc
        xor  eax,eax
        rep stosd
        pop  edi
        pop  ebp
        pop  ebx
        add  esp,0x18
        ret  0x4
    }
}
