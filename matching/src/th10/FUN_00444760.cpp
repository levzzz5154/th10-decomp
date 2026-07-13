// 00444760: FUN_00444760
// Original size: 944 bytes, actual code: 270 instructions
extern "C" void FUN_004423e0(void);
extern "C" void FUN_00442f50(void);
extern "C" void D3DXMatrixRotationX(void);
extern "C" void D3DXMatrixMultiply(void);
extern "C" void D3DXMatrixRotationY(void);
extern "C" void D3DXMatrixRotationZ(void);

extern "C" __declspec(naked) void FUN_00444760(void) {
    __asm {
        sub  esp,0xc0
        push  ebx
        mov  ebx,eax
        mov  eax,DWORD PTR [ebx+0x35c]
        test  al,0x1
        je loc_00444777
        test  al,0x2
        jne loc_00444784
    loc_00444777:
        or   eax,0xffffffff
        pop  ebx
        add  esp,0xc0
        ret  0x4
    loc_00444784:
        mov  al,BYTE PTR [ebx+0x2ff]
        test  al,al
        jne loc_0044479D
        mov  eax,0xffffffff
        pop  ebx
        add  esp,0xc0
        ret  0x4
    loc_0044479D:
        push  ebp
        mov  ebp,DWORD PTR [esp+0xcc]
        mov  eax,DWORD PTR [ebp+0x3adac8]
        test  eax,eax
        push  esi
        je loc_004447B7
        mov  esi,ebp
        call FUN_00442f50
    loc_004447B7:
        mov  eax,DWORD PTR [ebx+0x35c]
        test  ah,0x40
        push  edi
        jne loc_0044489F
        test  al,0xc
        je loc_0044489F
        fld  DWORD PTR [ebx+0x3c]
        lea  ebp,[ebx+0x27c]
        lea  esi,[ebx+0x23c]
        mov  ecx,0x10
        mov  edi,ebp
        rep movsd
        fmul  DWORD PTR [ebp+0x0]
        fstp  DWORD PTR [ebp+0x0]
        fld  DWORD PTR [ebx+0x40]
        fmul  DWORD PTR [ebx+0x290]
        fstp  DWORD PTR [ebx+0x290]
        fld  DWORD PTR [ebx+0x24]
        fld  QWORD PTR ds:0x470b70
        and  eax,0xfffffff7
        fucompp
        mov  DWORD PTR [ebx+0x35c],eax
        fnstsw ax
        test  ah,0x44
        jnp loc_00444831
        mov  eax,DWORD PTR [ebx+0x24]
        push  eax
        lea  ecx,[esp+0x54]
        push  ecx
        call D3DXMatrixRotationX
        lea  edx,[esp+0x50]
        push  edx
        push  ebp
        push  ebp
        call D3DXMatrixMultiply
    loc_00444831:
        fld  DWORD PTR [ebx+0x28]
        fld  QWORD PTR ds:0x470b70
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_0044485D
        mov  eax,DWORD PTR [ebx+0x28]
        push  eax
        lea  ecx,[esp+0x54]
        push  ecx
        call D3DXMatrixRotationY
        lea  edx,[esp+0x50]
        push  edx
        push  ebp
        push  ebp
        call D3DXMatrixMultiply
    loc_0044485D:
        fld  DWORD PTR [ebx+0x2c]
        fld  QWORD PTR ds:0x470b70
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_00444889
        mov  eax,DWORD PTR [ebx+0x2c]
        push  eax
        lea  ecx,[esp+0x54]
        push  ecx
        call D3DXMatrixRotationZ
        lea  edx,[esp+0x50]
        push  edx
        push  ebp
        push  ebp
        call D3DXMatrixMultiply
    loc_00444889:
        mov  eax,DWORD PTR [ebx+0x35c]
        mov  ebp,DWORD PTR [esp+0xd4]
        and  eax,0xfffffffb
        mov  DWORD PTR [ebx+0x35c],eax
    loc_0044489F:
        lea  esi,[ebx+0x27c]
        mov  ecx,0x10
        lea  edi,[esp+0x10]
        rep movsd
        mov  ecx,DWORD PTR [ebx+0x35c]
        mov  eax,ecx
        shr  eax,0x12
        and  eax,0x3
        sub  eax,0x0
        je loc_00444907
        dec  eax
        je loc_004448DF
        dec  eax
        jne loc_0044491D
        fld  DWORD PTR [ebx+0x4c]
        fmul  DWORD PTR [ebx+0x3c]
        fmul  DWORD PTR ds:0x470b0c
        fabs
        fadd  DWORD PTR [ebx+0x34c]
        jmp loc_0044490D
    loc_004448DF:
        fld  DWORD PTR [ebx+0x34c]
        fadd  DWORD PTR [ebx+0x340]
        fadd  DWORD PTR [ebx+0x334]
        fld  DWORD PTR [ebx+0x4c]
        fmul  DWORD PTR [ebx+0x3c]
        fmul  DWORD PTR ds:0x470b0c
        fabs
        fxch  st(1)
        fxch  st(1)
        fsubp st(1),st
        jmp loc_00444919
    loc_00444907:
        fld  DWORD PTR [ebx+0x34c]
    loc_0044490D:
        fadd  DWORD PTR [ebx+0x340]
        fadd  DWORD PTR [ebx+0x334]
    loc_00444919:
        fstp  DWORD PTR [esp+0x40]
    loc_0044491D:
        shr  ecx,0x14
        and  ecx,0x3
        sub  ecx,0x0
        je loc_0044496C
        dec  ecx
        je loc_00444944
        dec  ecx
        jne loc_00444982
        fld  DWORD PTR [ebx+0x50]
        fmul  DWORD PTR [ebx+0x40]
        fmul  DWORD PTR ds:0x470b0c
        fabs
        fadd  DWORD PTR [ebx+0x350]
        jmp loc_00444972
    loc_00444944:
        fld  DWORD PTR [ebx+0x350]
        fadd  DWORD PTR [ebx+0x344]
        fadd  DWORD PTR [ebx+0x338]
        fld  DWORD PTR [ebx+0x50]
        fmul  DWORD PTR [ebx+0x40]
        fmul  DWORD PTR ds:0x470b0c
        fabs
        fxch  st(1)
        fxch  st(1)
        fsubp st(1),st
        jmp loc_0044497E
    loc_0044496C:
        fld  DWORD PTR [ebx+0x350]
    loc_00444972:
        fadd  DWORD PTR [ebx+0x344]
        fadd  DWORD PTR [ebx+0x338]
    loc_0044497E:
        fstp  DWORD PTR [esp+0x44]
    loc_00444982:
        fld  DWORD PTR [ebx+0x33c]
        mov  eax,ebp
        fadd  DWORD PTR [ebx+0x348]
        fstp  DWORD PTR [esp+0x48]
        call FUN_004423e0
        fld  DWORD PTR [ebx+0x354]
        mov  eax,ds:0x491c30
        fadd  DWORD PTR [ebx+0x33c]
        lea  edx,[esp+0x10]
        push  edx
        push  0x100
        fadd  DWORD PTR [ebx+0x348]
        push  eax
        fstp  DWORD PTR [esp+0x54]
        mov  ecx,DWORD PTR [eax]
        call  DWORD PTR [ecx+0xb0]
        mov  eax,DWORD PTR [ebx+0x394]
        mov  eax,DWORD PTR [eax+0x4]
        cmp  DWORD PTR [ebp+0x3ada64],eax
        je loc_004449F0
        push  eax
        mov  DWORD PTR [ebp+0x3ada64],eax
        mov  ecx,DWORD PTR ds:0x491c30
        mov  edx,DWORD PTR [ecx]
        push  0x0
        push  ecx
        call  DWORD PTR [edx+0x104]
    loc_004449F0:
        mov  ecx,DWORD PTR [ebx+0x394]
        cmp  DWORD PTR [ebp+0x3ada70],ecx
        jne loc_00444A22
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [ebx+0x54]
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_00444A22
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [ebx+0x54]
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_00444A74
    loc_00444A22:
        mov  DWORD PTR [ebp+0x3ada70],ecx
        mov  eax,DWORD PTR [ebx+0x394]
        lea  esi,[ebx+0x2bc]
        mov  ecx,0x10
        lea  edi,[esp+0x90]
        rep movsd
        fld  DWORD PTR [eax+0x20]
        fadd  DWORD PTR [ebx+0x54]
        fstp  DWORD PTR [esp+0xb0]
        fld  DWORD PTR [eax+0x24]
        fadd  DWORD PTR [ebx+0x58]
        fstp  DWORD PTR [esp+0xb4]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        lea  edx,[esp+0x90]
        push  edx
        push  0x10
        push  eax
        call  DWORD PTR [ecx+0xb0]
    loc_00444A74:
        mov  al,BYTE PTR [ebp+0x3ada6a]
        mov  ebx,0x2
        cmp  al,bl
        pop  edi
        je loc_00444AE0
        mov  edx,DWORD PTR [ebp+0x3ada74]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x14
        push  0x0
        push  edx
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x190]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x102
        push  eax
        call  DWORD PTR [ecx+0x164]
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x3
        push  0x6
        push  0x0
        push  eax
        call  DWORD PTR [edx+0x10c]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x3
        push  0x3
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x10c]
        mov  BYTE PTR [ebp+0x3ada6a],bl
    loc_00444AE0:
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  ebx
        push  0x0
        push  0x5
        push  eax
        call  DWORD PTR [edx+0x144]
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0xc0
        ret  0x4
    }
}
