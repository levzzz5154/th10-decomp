// 00447FD0: FUN_00447fd0
// Original size: 336 bytes, actual code: 115 instructions
extern "C" void D3DXLoadSurfaceFromSurface(void);

extern "C" __declspec(naked) void FUN_00447fd0(void) {
    __asm {
        sub  esp,0x1c
        push  esi
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+esi*4+0x3ad560]
        test  eax,eax
        je loc_00448113
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        lea  edx,[esp+0x4]
        push  edx
        push  0x0
        push  0x0
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x48]
        test  eax,eax
        jne loc_00448113
        mov  eax,DWORD PTR [ebx+esi*4+0x3ad4e0]
        test  eax,eax
        push  ebp
        push  edi
        lea  edi,[ebx+esi*4+0x3ad4e0]
        jne loc_004480AF
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x0
        mov  ecx,esi
        imul  ecx,ecx,0x1c
        push  edi
        push  0x1
        push  0x0
        lea  ebp,[ecx+ebx*1]
        mov  ecx,DWORD PTR ds:0x491d14
        push  0x0
        push  ecx
        mov  ecx,DWORD PTR [ebp+0x3ad6e4]
        push  ecx
        mov  ecx,DWORD PTR [ebp+0x3ad6e0]
        push  ecx
        push  eax
        call  DWORD PTR [edx+0x70]
        test  eax,eax
        je loc_0044807C
        mov  ecx,DWORD PTR ds:0x491d14
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x0
        push  edi
        push  0x3
        push  ecx
        mov  ecx,DWORD PTR [ebp+0x3ad6e4]
        push  ecx
        mov  ecx,DWORD PTR [ebp+0x3ad6e0]
        push  ecx
        push  eax
        call  DWORD PTR [edx+0x90]
        test  eax,eax
        jne loc_0044809C
    loc_0044807C:
        mov  eax,DWORD PTR [ebx+esi*4+0x3ad560]
        mov  ecx,DWORD PTR [edi]
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
        je loc_004480AF
    loc_0044809C:
        mov  eax,DWORD PTR [esp+0xc]
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
        pop  edi
        pop  ebp
        pop  esi
        add  esp,0x1c
        ret  0x10
    loc_004480AF:
        mov  eax,DWORD PTR [esp+0x2c]
        imul  esi,esi,0x1c
        mov  edx,DWORD PTR [esi+ebx*1+0x3ad6e0]
        mov  ecx,DWORD PTR [esp+0x30]
        mov  DWORD PTR [esp+0x18],eax
        lea  eax,[esi+ebx*1]
        mov  eax,DWORD PTR [eax+0x3ad6e4]
        mov  DWORD PTR [esp+0x20],edx
        mov  edx,DWORD PTR [esp+0x38]
        mov  DWORD PTR [esp+0x14],edx
        lea  edx,[esp+0x10]
        push  edx
        mov  edx,DWORD PTR [esp+0x10]
        push  edx
        lea  edx,[esp+0x20]
        push  edx
        mov  edx,DWORD PTR [edi]
        mov  DWORD PTR [esp+0x28],ecx
        mov  ecx,DWORD PTR [esp+0x40]
        mov  DWORD PTR [esp+0x30],eax
        mov  eax,ds:0x491c30
        push  edx
        mov  DWORD PTR [esp+0x20],ecx
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x78]
        mov  eax,DWORD PTR [esp+0xc]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        pop  edi
        pop  ebp
    loc_00448113:
        pop  esi
        add  esp,0x1c
        ret  0x10
    }
}
