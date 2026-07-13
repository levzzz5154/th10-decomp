// 0041CFD0: FUN_0041cfd0
// Original size: 752 bytes, actual code: 118 instructions
extern "C" void FUN_0041c510(void);
extern "C" void FUN_0041f800(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_0044bc70(void);

extern "C" __declspec(naked) void FUN_0041cfd0(void) {
    __asm {
        sub  esp,0xc
        push  ebx
        mov  ebx,ecx
        mov  eax,DWORD PTR [ebx+0x40]
        mov  ecx,DWORD PTR [ebx+0x3c]
        push  eax
        push  ecx
        lea  ecx,[esp+0xc]
        call FUN_0041f800
        fld  DWORD PTR [esp+0x4]
        fadd  DWORD PTR [ebx+0x24]
        mov  DWORD PTR [esp+0xc],0x0
        fstp  DWORD PTR [esp+0x4]
        fld  DWORD PTR [esp+0x8]
        fadd  DWORD PTR [ebx+0x28]
        fstp  DWORD PTR [esp+0x8]
        fld  DWORD PTR [esp+0x4]
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x41
        jnp loc_0041D04D
        fld  DWORD PTR [esp+0x4]
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        test  ah,0x1
        je loc_0041D04D
        fld  DWORD PTR [esp+0x8]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x41
        jnp loc_0041D04D
        fld  DWORD PTR [esp+0x8]
        fcomp DWORD PTR ds:0x470b38
        fnstsw ax
        test  ah,0x1
        jne loc_0041D165
    loc_0041D04D:
        push  ebp
        push  edi
        mov  edi,DWORD PTR [ebx+0x40c]
        xor  ebp,ebp
        test  edi,edi
        jl loc_0041D066
        push  ebp
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_0041D066:
        fld  DWORD PTR [esp+0xc]
        push  esi
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x5
        jnp loc_0041D089
        fld  DWORD PTR [esp+0x10]
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        test  ah,0x1
        jne loc_0041D0DD
    loc_0041D089:
        fld  DWORD PTR [ebx+0x3c]
        mov  eax,DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [esp+0x14]
        fchs
        fsub  DWORD PTR ds:0x470b18
        lea  edi,[ebx+0x424]
        mov  edx,edi
        mov  DWORD PTR [edx],eax
        mov  eax,DWORD PTR [esp+0x18]
        mov  DWORD PTR [edx+0x4],ecx
        push  ecx
        fstp  DWORD PTR [esp]
        mov  DWORD PTR [edx+0x8],eax
        call FUN_0044bc70
        fstp  DWORD PTR [ebx+0x430]
        mov  ecx,DWORD PTR [ebx+0x13c]
        mov  esi,DWORD PTR ds:0x47781c
        push  0x0
        mov  DWORD PTR [ebx+0x444],ecx
        mov  ebp,0x1
        call FUN_0041c510
    loc_0041D0DD:
        mov  ecx,DWORD PTR [ebx+0x404]
        test  ecx,0x8000000
        jne loc_0041D154
        fld  DWORD PTR [esp+0x14]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jnp loc_0041D112
        fld  DWORD PTR [esp+0x14]
        fcomp DWORD PTR ds:0x470b38
        fnstsw ax
        test  ah,0x1
        jne loc_0041D154
        test  ch,0x4
        je loc_0041D154
    loc_0041D112:
        mov  eax,DWORD PTR [esp+0x10]
        fld  DWORD PTR [ebx+0x3c]
        mov  ecx,DWORD PTR [esp+0x14]
        fchs
        mov  esi,DWORD PTR ds:0x47781c
        fstp  DWORD PTR [ebx+0x430]
        lea  edi,[ebx+0x424]
        mov  edx,edi
        mov  DWORD PTR [edx],eax
        mov  eax,DWORD PTR [esp+0x18]
        mov  DWORD PTR [edx+0x4],ecx
        mov  ecx,DWORD PTR [ebx+0x13c]
        push  0x0
        mov  DWORD PTR [edx+0x8],eax
        mov  DWORD PTR [ebx+0x444],ecx
        call FUN_0041c510
        jmp loc_0041D158
    loc_0041D154:
        test  ebp,ebp
        je loc_0041D162
    loc_0041D158:
        and  DWORD PTR [ebx+0x404],0xf7fff3ff
    loc_0041D162:
        pop  esi
        pop  edi
        pop  ebp
    loc_0041D165:
        pop  ebx
        add  esp,0xc
        ret
    }
}
