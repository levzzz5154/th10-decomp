// 00448120: FUN_00448120
// Original size: 336 bytes, actual code: 115 instructions
extern "C" void D3DXLoadSurfaceFromSurface(void);

extern "C" __declspec(naked) void FUN_00448120(void) {
    __asm {
        sub  esp,0x18
        push  ebp
        mov  ebp,DWORD PTR [esp+0x20]
        mov  eax,DWORD PTR [ebp+ebx*4+0x3ad560]
        test  eax,eax
        je loc_0044825E
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        lea  edx,[esp+0x20]
        push  edx
        push  0x0
        push  0x0
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x48]
        test  eax,eax
        jne loc_0044825E
        mov  eax,DWORD PTR [ebp+ebx*4+0x3ad4e0]
        test  eax,eax
        push  esi
        lea  esi,[ebp+ebx*4+0x3ad4e0]
        push  edi
        jne loc_00448201
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x0
        mov  ecx,ebx
        imul  ecx,ecx,0x1c
        push  esi
        push  0x1
        push  0x0
        lea  edi,[ecx+ebp*1]
        mov  ecx,DWORD PTR ds:0x491d14
        push  0x0
        push  ecx
        mov  ecx,DWORD PTR [edi+0x3ad6e4]
        push  ecx
        mov  ecx,DWORD PTR [edi+0x3ad6e0]
        push  ecx
        push  eax
        call  DWORD PTR [edx+0x70]
        test  eax,eax
        je loc_004481CE
        mov  ecx,DWORD PTR ds:0x491d14
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x0
        push  esi
        push  0x3
        push  ecx
        mov  ecx,DWORD PTR [edi+0x3ad6e4]
        push  ecx
        mov  ecx,DWORD PTR [edi+0x3ad6e0]
        push  ecx
        push  eax
        call  DWORD PTR [edx+0x90]
        test  eax,eax
        jne loc_004481EE
    loc_004481CE:
        mov  eax,DWORD PTR [ebp+ebx*4+0x3ad560]
        mov  ecx,DWORD PTR [esi]
        push  0x0
        push  0x1
        push  0x0
        push  0x0
        push  eax
        push  0x0
        push  0x0
        push  ecx
        call D3DXLoadSurfaceFromSurface
        test  eax,eax
        je loc_00448201
    loc_004481EE:
        mov  eax,DWORD PTR [esp+0x28]
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
        pop  edi
        pop  esi
        pop  ebp
        add  esp,0x18
        ret  0x1c
    loc_00448201:
        mov  ecx,DWORD PTR [esp+0x34]
        mov  edx,DWORD PTR [esp+0x3c]
        mov  eax,DWORD PTR [esp+0x38]
        mov  DWORD PTR [esp+0x14],ecx
        add  ecx,edx
        mov  edx,DWORD PTR [esp+0x2c]
        mov  DWORD PTR [esp+0xc],edx
        lea  edx,[esp+0xc]
        push  edx
        mov  edx,DWORD PTR [esp+0x2c]
        mov  DWORD PTR [esp+0x1c],eax
        mov  DWORD PTR [esp+0x20],ecx
        mov  ecx,DWORD PTR [esp+0x44]
        push  edx
        add  eax,ecx
        mov  DWORD PTR [esp+0x28],eax
        mov  eax,DWORD PTR [esp+0x38]
        lea  edx,[esp+0x1c]
        push  edx
        mov  edx,DWORD PTR [esi]
        mov  DWORD PTR [esp+0x1c],eax
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  edx
        push  eax
        call  DWORD PTR [ecx+0x78]
        mov  eax,DWORD PTR [esp+0x28]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        pop  edi
        pop  esi
    loc_0044825E:
        pop  ebp
        add  esp,0x18
        ret  0x1c
    }
}
