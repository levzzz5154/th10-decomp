// 00421480: FUN_00421480
// Original size: 288 bytes, actual code: 79 instructions
extern "C" void FUN_00442f50(void);
extern "C" void D3DXMatrixLookAtLH(void);
extern "C" void D3DXMatrixPerspectiveFovLH(void);

extern "C" __declspec(naked) void FUN_00421480(void) {
    __asm {
        sub  esp,0x2c
        push  ebx
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        test  esi,esi
        je loc_00421494
        call FUN_00442f50
    loc_00421494:
        mov  eax,DWORD PTR [edi+0xd4]
        fild  DWORD PTR [edi+0xd4]
        test  eax,eax
        jge loc_004214AA
        fadd  DWORD PTR ds:0x470b98
    loc_004214AA:
        mov  ecx,DWORD PTR [edi+0xd8]
        fst  DWORD PTR [esp+0x8]
        test  ecx,ecx
        fmul  DWORD PTR ds:0x470b0c
        fild  DWORD PTR [edi+0xd8]
        jge loc_004214CA
        fadd  DWORD PTR ds:0x470b98
    loc_004214CA:
        fst  DWORD PTR [esp+0xc]
        lea  edx,[esp+0x10]
        fmul  DWORD PTR ds:0x470b0c
        push  edx
        fld  DWORD PTR [esp+0xc]
        lea  eax,[esp+0x20]
        fdiv  DWORD PTR [esp+0x10]
        push  eax
        lea  ecx,[esp+0x30]
        push  ecx
        lea  esi,[edi+0x4c]
        push  esi
        mov  DWORD PTR [esp+0x34],0x0
        mov  DWORD PTR [esp+0x20],0x0
        mov  DWORD PTR [esp+0x24],0xbf800000
        mov  DWORD PTR [esp+0x28],0x0
        fstp  DWORD PTR [esp+0x1c]
        fld  st(1)
        fstp  DWORD PTR [esp+0x38]
        fst  DWORD PTR [esp+0x3c]
        fld  QWORD PTR ds:0x470ba0
        fptan
        fstp  st(0)
        fdivr st,st(1)
        fstp  DWORD PTR [esp+0x40]
        fxch  st(1)
        fstp  DWORD PTR [esp+0x2c]
        fstp  DWORD PTR [esp+0x30]
        call D3DXMatrixLookAtLH
        mov  edx,DWORD PTR [esp+0xc]
        push  0x461c4000
        push  0x3f800000
        push  edx
        push  0x3ea0d97c
        lea  ebx,[edi+0x8c]
        push  ebx
        call D3DXMatrixPerspectiveFovLH
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  esi
        push  0x2
        push  eax
        call  DWORD PTR [ecx+0xb0]
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  ebx
        push  0x3
        push  eax
        call  DWORD PTR [edx+0xb0]
        mov  eax,ds:0x491c10
        test  eax,eax
        pop  esi
        pop  ebx
        je loc_0042159B
        mov  ecx,DWORD PTR [edi+0xe8]
        mov  DWORD PTR [eax+0x5c],ecx
        mov  edx,DWORD PTR [edi+0xec]
        mov  DWORD PTR [eax+0x60],edx
    loc_0042159B:
        add  esp,0x2c
        ret
    }
}
