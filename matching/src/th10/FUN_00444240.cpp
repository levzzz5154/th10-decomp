// 00444240: FUN_00444240
// Original size: 832 bytes, actual code: 205 instructions
extern "C" void D3DXVec3Project(void);
extern "C" void D3DXMatrixRotationX(void);
extern "C" void D3DXMatrixMultiply(void);
extern "C" void D3DXMatrixRotationY(void);
extern "C" void D3DXMatrixRotationZ(void);

extern "C" __declspec(naked) void FUN_00444240(void) {
    __asm {
        sub  esp,0xb0
        push  ebx
        mov  ebx,eax
        mov  eax,DWORD PTR [ebx+0x35c]
        test  ah,0x40
        push  esi
        push  edi
        jne loc_00444337
        test  al,0xc
        je loc_00444337
        fld  DWORD PTR [ebx+0x3c]
        push  ebp
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
        jnp loc_004442CB
        mov  eax,DWORD PTR [ebx+0x24]
        push  eax
        lea  ecx,[esp+0x84]
        push  ecx
        call D3DXMatrixRotationX
        lea  edx,[esp+0x80]
        push  edx
        push  ebp
        push  ebp
        call D3DXMatrixMultiply
    loc_004442CB:
        fld  DWORD PTR [ebx+0x28]
        fld  QWORD PTR ds:0x470b70
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_004442FD
        mov  eax,DWORD PTR [ebx+0x28]
        push  eax
        lea  ecx,[esp+0x84]
        push  ecx
        call D3DXMatrixRotationY
        lea  edx,[esp+0x80]
        push  edx
        push  ebp
        push  ebp
        call D3DXMatrixMultiply
    loc_004442FD:
        fld  DWORD PTR [ebx+0x2c]
        fld  QWORD PTR ds:0x470b70
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_0044432F
        mov  eax,DWORD PTR [ebx+0x2c]
        push  eax
        lea  ecx,[esp+0x84]
        push  ecx
        call D3DXMatrixRotationZ
        lea  edx,[esp+0x80]
        push  edx
        push  ebp
        push  ebp
        call D3DXMatrixMultiply
    loc_0044432F:
        and  DWORD PTR [ebx+0x35c],0xfffffffb
        pop  ebp
    loc_00444337:
        fld  DWORD PTR [ebx+0x34c]
        lea  esi,[ebx+0x27c]
        fadd  DWORD PTR [ebx+0x340]
        mov  ecx,0x10
        lea  edi,[esp+0x3c]
        rep movsd
        fadd  DWORD PTR [ebx+0x334]
        fadd  DWORD PTR [esp+0x6c]
        fstp  DWORD PTR [esp+0x6c]
        fld  DWORD PTR [ebx+0x350]
        fadd  DWORD PTR [ebx+0x344]
        fadd  DWORD PTR [ebx+0x338]
        fadd  DWORD PTR [esp+0x70]
        fstp  DWORD PTR [esp+0x70]
        fld  DWORD PTR [ebx+0x354]
        fadd  DWORD PTR [ebx+0x348]
        fadd  DWORD PTR [ebx+0x33c]
        mov  ebx,DWORD PTR [ebx+0x35c]
        mov  eax,ebx
        shr  eax,0x12
        and  eax,0x3
        fstp  DWORD PTR [esp+0x74]
        sub  eax,0x0
        je loc_004443EF
        dec  eax
        je loc_004443CD
        dec  eax
        jne loc_0044440F
        mov  DWORD PTR [esp+0x24],0xc3800000
        mov  DWORD PTR [esp+0xc],0xc3800000
        mov  DWORD PTR [esp+0x30],0x0
        mov  DWORD PTR [esp+0x18],0x0
        jmp loc_0044440F
    loc_004443CD:
        mov  DWORD PTR [esp+0x24],0x0
        mov  DWORD PTR [esp+0xc],0x0
        mov  DWORD PTR [esp+0x30],0x43800000
        mov  DWORD PTR [esp+0x18],0x43800000
        jmp loc_0044440F
    loc_004443EF:
        mov  DWORD PTR [esp+0x24],0xc3000000
        mov  DWORD PTR [esp+0xc],0xc3000000
        mov  DWORD PTR [esp+0x30],0x43000000
        mov  DWORD PTR [esp+0x18],0x43000000
    loc_0044440F:
        shr  ebx,0x14
        and  ebx,0x3
        sub  ebx,0x0
        je loc_00444464
        dec  ebx
        je loc_00444442
        dec  ebx
        jne loc_00444484
        mov  DWORD PTR [esp+0x1c],0xc3800000
        mov  DWORD PTR [esp+0x10],0xc3800000
        mov  DWORD PTR [esp+0x34],0x0
        mov  DWORD PTR [esp+0x28],0x0
        jmp loc_00444484
    loc_00444442:
        mov  DWORD PTR [esp+0x1c],0x0
        mov  DWORD PTR [esp+0x10],0x0
        mov  DWORD PTR [esp+0x34],0x43800000
        mov  DWORD PTR [esp+0x28],0x43800000
        jmp loc_00444484
    loc_00444464:
        mov  DWORD PTR [esp+0x1c],0xc3000000
        mov  DWORD PTR [esp+0x10],0xc3000000
        mov  DWORD PTR [esp+0x34],0x43000000
        mov  DWORD PTR [esp+0x28],0x43000000
    loc_00444484:
        lea  eax,[esp+0x3c]
        push  eax
        mov  eax,ds:0x491fac
        lea  ecx,[eax+0x4c]
        push  ecx
        lea  edx,[eax+0x8c]
        push  edx
        add  eax,0xcc
        push  eax
        lea  eax,[esp+0x1c]
        push  eax
        push  0x4978c0
        mov  DWORD PTR [esp+0x50],0x0
        mov  DWORD PTR [esp+0x44],0x0
        mov  DWORD PTR [esp+0x38],0x0
        mov  DWORD PTR [esp+0x2c],0x0
        call D3DXVec3Project
        mov  eax,ds:0x491fac
        lea  ecx,[esp+0x3c]
        push  ecx
        lea  edx,[eax+0x4c]
        push  edx
        lea  ecx,[eax+0x8c]
        push  ecx
        add  eax,0xcc
        push  eax
        lea  edx,[esp+0x28]
        push  edx
        push  0x4978dc
        call D3DXVec3Project
        lea  eax,[esp+0x3c]
        push  eax
        mov  eax,ds:0x491fac
        lea  ecx,[eax+0x4c]
        push  ecx
        lea  edx,[eax+0x8c]
        push  edx
        add  eax,0xcc
        push  eax
        lea  eax,[esp+0x34]
        push  eax
        push  0x4978f8
        call D3DXVec3Project
        mov  eax,ds:0x491fac
        lea  ecx,[esp+0x3c]
        push  ecx
        lea  edx,[eax+0x4c]
        push  edx
        lea  ecx,[eax+0x8c]
        push  ecx
        add  eax,0xcc
        push  eax
        lea  edx,[esp+0x40]
        push  edx
        push  0x497914
        call D3DXVec3Project
        mov  edi,DWORD PTR [esp+0xc0]
        add  edi,0x3ad0f0
        mov  ecx,0x10
        lea  esi,[esp+0x3c]
        rep movsd
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebx
        add  esp,0xb0
        ret  0x4
    }
}
