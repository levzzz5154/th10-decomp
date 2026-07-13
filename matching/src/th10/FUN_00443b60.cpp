// 00443B60: FUN_00443b60
// Original size: 1056 bytes, actual code: 251 instructions
extern "C" void D3DXVec3Project(void);

extern "C" __declspec(naked) void FUN_00443b60(void) {
    __asm {
        sub  esp,0xa0
        push  esi
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x2c]
        mov  DWORD PTR [esp+0x48],eax
        fld  DWORD PTR [esp+0x48]
        fsincos
        fstp  DWORD PTR [esp+0x4]
        fstp  DWORD PTR [esp+0x8]
        fld  DWORD PTR [esi+0x34c]
        fadd  DWORD PTR [esi+0x340]
        mov  eax,ds:0x491fac
        lea  edx,[eax+0x4c]
        lea  ecx,[esp+0x64]
        fadd  DWORD PTR [esi+0x334]
        push  ecx
        push  edx
        lea  ecx,[eax+0x8c]
        fstp  DWORD PTR [esp+0x9c]
        push  ecx
        fld  DWORD PTR [esi+0x350]
        add  eax,0xcc
        fadd  DWORD PTR [esi+0x344]
        push  eax
        lea  edx,[esp+0x24]
        push  edx
        fadd  DWORD PTR [esi+0x338]
        lea  eax,[esp+0x48]
        push  eax
        mov  DWORD PTR [esp+0x2c],0x0
        fstp  DWORD PTR [esp+0xb0]
        mov  DWORD PTR [esp+0x30],0x0
        fld  DWORD PTR [esi+0x354]
        mov  DWORD PTR [esp+0x34],0x0
        fadd  DWORD PTR [esi+0x348]
        mov  DWORD PTR [esp+0xa8],0x0
        mov  DWORD PTR [esp+0xa0],0x0
        mov  DWORD PTR [esp+0x9c],0x0
        fadd  DWORD PTR [esi+0x33c]
        mov  DWORD PTR [esp+0x98],0x0
        mov  DWORD PTR [esp+0x94],0x0
        mov  DWORD PTR [esp+0x8c],0x0
        fstp  DWORD PTR [esp+0xb4]
        mov  DWORD PTR [esp+0x88],0x0
        mov  DWORD PTR [esp+0x84],0x0
        mov  DWORD PTR [esp+0x80],0x0
        mov  DWORD PTR [esp+0xb8],0x3f800000
        mov  DWORD PTR [esp+0xa4],0x3f800000
        mov  DWORD PTR [esp+0x90],0x3f800000
        mov  DWORD PTR [esp+0x7c],0x3f800000
        call D3DXVec3Project
        fld  DWORD PTR [esp+0x3c]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jnp loc_00443F6C
        fld  DWORD PTR [esp+0x3c]
        fcomp DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x41
        je loc_00443F6C
        mov  eax,ds:0x491fac
        lea  edx,[eax+0x4c]
        lea  ecx,[esp+0x64]
        push  ecx
        push  edx
        lea  ecx,[eax+0x8c]
        push  ecx
        lea  edx,[eax+0xcc]
        push  edx
        add  eax,0x30
        push  eax
        lea  eax,[esp+0x6c]
        push  eax
        call D3DXVec3Project
        fld  DWORD PTR [esp+0x58]
        fsub  DWORD PTR [esp+0x34]
        fstp  DWORD PTR [esp+0x24]
        mov  ecx,DWORD PTR [esp+0x24]
        fld  DWORD PTR [esp+0x5c]
        mov  DWORD PTR [esp+0x4c],ecx
        fsub  DWORD PTR [esp+0x38]
        mov  ecx,DWORD PTR [esp+0x34]
        mov  DWORD PTR [esp+0x40],ecx
        fstp  DWORD PTR [esp+0x28]
        mov  edx,DWORD PTR [esp+0x28]
        fld  DWORD PTR [esp+0x60]
        mov  DWORD PTR [esp+0x50],edx
        fsub  DWORD PTR [esp+0x3c]
        mov  edx,DWORD PTR [esp+0x38]
        mov  DWORD PTR [esp+0x44],edx
        fstp  DWORD PTR [esp+0x2c]
        mov  eax,DWORD PTR [esp+0x2c]
        mov  DWORD PTR [esp+0x54],eax
        fld  DWORD PTR [esp+0x54]
        fmul  DWORD PTR [esp+0x54]
        mov  eax,DWORD PTR [esp+0x3c]
        fld  DWORD PTR [esp+0x50]
        mov  ecx,eax
        fmul  DWORD PTR [esp+0x50]
        mov  edx,eax
        faddp st(1),st
        fld  DWORD PTR [esp+0x4c]
        fmul  DWORD PTR [esp+0x4c]
        faddp st(1),st
        fsqrt
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [esi+0x4c]
        fmul  DWORD PTR [esi+0x3c]
        fmul  st,st(1)
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [esi+0x50]
        fmul  DWORD PTR [esi+0x40]
        mov  ds:0x49791c,eax
        mov  DWORD PTR ds:0x497900,ecx
        mov  DWORD PTR ds:0x4978e4,edx
        fmul  st,st(1)
        mov  ds:0x4978c8,eax
        fstp  DWORD PTR [esp+0xc]
        fstp  st(0)
        fld  DWORD PTR [esp+0x48]
        fsincos
        fstp  DWORD PTR [esp+0x4]
        fstp  DWORD PTR [esp+0x8]
        mov  esi,DWORD PTR [esi+0x35c]
        mov  eax,esi
        shr  eax,0x12
        and  eax,0x3
        sub  eax,0x0
        je loc_00443DF6
        dec  eax
        je loc_00443DD8
        dec  eax
        jne loc_00443E18
        fld  DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0x20],0x0
        fchs
        fst  DWORD PTR [esp+0x1c]
        fstp  DWORD PTR [esp+0x14]
        fld  DWORD PTR ds:0x470b04
        jmp loc_00443E1C
    loc_00443DD8:
        mov  ecx,DWORD PTR [esp+0x10]
        fld  DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0x1c],0x0
        mov  DWORD PTR [esp+0x14],0x0
        mov  DWORD PTR [esp+0x20],ecx
        jmp loc_00443E1C
    loc_00443DF6:
        fld  DWORD PTR [esp+0x10]
        fmul  DWORD PTR ds:0x470b78
        fst  DWORD PTR [esp+0x1c]
        fstp  DWORD PTR [esp+0x14]
        fld  DWORD PTR [esp+0x10]
        fmul  DWORD PTR ds:0x470b0c
        fst  DWORD PTR [esp+0x20]
        jmp loc_00443E1C
    loc_00443E18:
        fld  DWORD PTR [esp+0x18]
    loc_00443E1C:
        shr  esi,0x14
        and  esi,0x3
        sub  esi,0x0
        je loc_00443E69
        dec  esi
        je loc_00443E4B
        dec  esi
        jne loc_00443E8B
        fld  DWORD PTR [esp+0xc]
        mov  DWORD PTR [esp+0x30],0x0
        fchs
        fst  DWORD PTR [esp+0x28]
        fstp  DWORD PTR [esp+0x24]
        fld  DWORD PTR ds:0x470b04
        jmp loc_00443E8F
    loc_00443E4B:
        mov  edx,DWORD PTR [esp+0xc]
        fld  DWORD PTR [esp+0xc]
        mov  DWORD PTR [esp+0x28],0x0
        mov  DWORD PTR [esp+0x24],0x0
        mov  DWORD PTR [esp+0x30],edx
        jmp loc_00443E8F
    loc_00443E69:
        fld  DWORD PTR [esp+0xc]
        fmul  DWORD PTR ds:0x470b78
        fst  DWORD PTR [esp+0x28]
        fstp  DWORD PTR [esp+0x24]
        fld  DWORD PTR [esp+0xc]
        fmul  DWORD PTR ds:0x470b0c
        fst  DWORD PTR [esp+0x30]
        jmp loc_00443E8F
    loc_00443E8B:
        fld  DWORD PTR [esp+0x2c]
    loc_00443E8F:
        fld  DWORD PTR [esp+0x14]
        xor  eax,eax
        fmul  DWORD PTR [esp+0x4]
        pop  esi
        fld  DWORD PTR [esp+0x20]
        fmul  DWORD PTR [esp+0x4]
        fsubp st(1),st
        fadd  DWORD PTR [esp+0x3c]
        fstp  DWORD PTR ds:0x4978c0
        fld  DWORD PTR [esp+0x20]
        fmul  DWORD PTR [esp]
        fld  DWORD PTR [esp+0x10]
        fmul  DWORD PTR [esp+0x4]
        faddp st(1),st
        fadd  DWORD PTR [esp+0x40]
        fstp  DWORD PTR ds:0x4978c4
        fld  st(1)
        fmul  DWORD PTR [esp]
        fld  DWORD PTR [esp+0x24]
        fmul  DWORD PTR [esp+0x4]
        fsubp st(1),st
        fadd  DWORD PTR [esp+0x3c]
        fstp  DWORD PTR ds:0x4978dc
        fxch  st(1)
        fmul  DWORD PTR [esp+0x4]
        fld  DWORD PTR [esp+0x24]
        fmul  DWORD PTR [esp]
        faddp st(1),st
        fadd  DWORD PTR [esp+0x40]
        fstp  DWORD PTR ds:0x4978e0
        fld  DWORD PTR [esp+0x18]
        fmul  DWORD PTR [esp]
        fld  st(1)
        fmul  DWORD PTR [esp+0x4]
        fsubp st(1),st
        fadd  DWORD PTR [esp+0x3c]
        fstp  DWORD PTR ds:0x4978f8
        fld  DWORD PTR [esp]
        fmul  st,st(1)
        fld  DWORD PTR [esp+0x18]
        fmul  DWORD PTR [esp+0x4]
        faddp st(1),st
        fadd  DWORD PTR [esp+0x40]
        fstp  DWORD PTR ds:0x4978fc
        fld  DWORD PTR [esp+0x1c]
        fmul  DWORD PTR [esp]
        fld  DWORD PTR [esp+0x2c]
        fmul  DWORD PTR [esp+0x4]
        fsubp st(1),st
        fadd  DWORD PTR [esp+0x3c]
        fstp  DWORD PTR ds:0x497914
        fld  DWORD PTR [esp+0x2c]
        fmul  DWORD PTR [esp]
        fld  DWORD PTR [esp+0x1c]
        fmul  DWORD PTR [esp+0x4]
        faddp st(1),st
        fadd  DWORD PTR [esp+0x40]
        fstp  DWORD PTR ds:0x497918
        fstp  st(0)
        add  esp,0xa0
        ret
    loc_00443F6C:
        or   eax,0xffffffff
        pop  esi
        add  esp,0xa0
        ret
    }
}
