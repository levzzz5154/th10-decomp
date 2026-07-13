// 004215A0: FUN_004215a0
// Original size: 336 bytes, actual code: 108 instructions
extern "C" void FUN_00442f50(void);
extern "C" void D3DXVec3Normalize(void);
extern "C" void D3DXMatrixLookAtLH(void);
extern "C" void D3DXMatrixPerspectiveFovLH(void);

extern "C" __declspec(naked) void FUN_004215a0(void) {
    __asm {
        sub  esp,0x28
        push  ebx
        push  ebp
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        test  esi,esi
        je loc_004215B5
        call FUN_00442f50
    loc_004215B5:
        fld  DWORD PTR [edi+0xc]
        lea  esi,[edi+0x18]
        fadd  DWORD PTR [edi]
        push  esi
        lea  eax,[esp+0x20]
        push  eax
        fstp  DWORD PTR [esp+0x24]
        lea  ecx,[esp+0x30]
        fld  DWORD PTR [edi+0x10]
        push  ecx
        fadd  DWORD PTR [edi+0x4]
        lea  ebx,[edi+0x4c]
        push  ebx
        fstp  DWORD PTR [esp+0x30]
        fld  DWORD PTR [edi+0x14]
        fadd  DWORD PTR [edi+0x8]
        fstp  DWORD PTR [esp+0x34]
        fld  DWORD PTR [edi+0x3c]
        fadd  DWORD PTR [edi]
        fstp  DWORD PTR [esp+0x38]
        fld  DWORD PTR [edi+0x40]
        fadd  DWORD PTR [edi+0x4]
        fstp  DWORD PTR [esp+0x3c]
        fld  DWORD PTR [edi+0x44]
        fadd  DWORD PTR [edi+0x8]
        fstp  DWORD PTR [esp+0x40]
        call D3DXMatrixLookAtLH
        mov  edx,DWORD PTR [edi+0xd4]
        fild  DWORD PTR [edi+0xd4]
        test  edx,edx
        push  0x44e10000
        lea  ebp,[edi+0x8c]
        push  0x41f00000
        jge loc_0042162C
        fadd  DWORD PTR ds:0x470b98
    loc_0042162C:
        mov  eax,DWORD PTR [edi+0xd8]
        fild  DWORD PTR [edi+0xd8]
        test  eax,eax
        jge loc_00421642
        fadd  DWORD PTR ds:0x470b98
    loc_00421642:
        fdivp st(1),st
        push  ecx
        mov  ecx,DWORD PTR [edi+0x48]
        fstp  DWORD PTR [esp]
        push  ecx
        push  ebp
        call D3DXMatrixPerspectiveFovLH
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  ebx
        push  0x2
        push  eax
        call  DWORD PTR [edx+0xb0]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  ebp
        push  0x3
        push  eax
        call  DWORD PTR [ecx+0xb0]
        fld  DWORD PTR [esi+0x8]
        fmul  DWORD PTR [edi+0x10]
        lea  eax,[edi+0x30]
        fld  DWORD PTR [esi+0x4]
        mov  edx,eax
        fmul  DWORD PTR [edi+0x14]
        push  eax
        push  eax
        fsubp st(1),st
        fstp  DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [esp+0x18]
        fld  DWORD PTR [esi]
        fmul  DWORD PTR [edi+0x14]
        fld  DWORD PTR [esi+0x8]
        fmul  DWORD PTR [edi+0xc]
        fsubp st(1),st
        fstp  DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esi+0x4]
        fmul  DWORD PTR [edi+0xc]
        fld  DWORD PTR [esi]
        fmul  DWORD PTR [edi+0x10]
        mov  DWORD PTR [edx],ecx
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [edx+0x4],ecx
        fsubp st(1),st
        fstp  DWORD PTR [esp+0x20]
        mov  ecx,DWORD PTR [esp+0x20]
        mov  DWORD PTR [edx+0x8],ecx
        call D3DXVec3Normalize
        mov  eax,ds:0x491c10
        test  eax,eax
        pop  esi
        pop  ebp
        pop  ebx
        je loc_004216E6
        mov  edx,DWORD PTR [edi+0xe8]
        mov  DWORD PTR [eax+0x5c],edx
        mov  ecx,DWORD PTR [edi+0xec]
        mov  DWORD PTR [eax+0x60],ecx
    loc_004216E6:
        add  esp,0x28
        ret
    }
}
