// 00448450: FUN_00448450
// Original size: 1040 bytes, actual code: 136 instructions
extern "C" void FUN_00442f50(void);
extern "C" void FUN_00447f70(void);
extern "C" void D3DXLoadSurfaceFromSurface(void);

extern "C" __declspec(naked) void FUN_00448450(void) {
    __asm {
        sub  esp,0x20
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x4c]
        push  esi
        push  edi
        mov  edi,eax
        mov  esi,edi
        call FUN_00442f50
        mov  esi,DWORD PTR [esp+0x34]
        mov  eax,DWORD PTR [edi+esi*4+0x3ad4e0]
        test  eax,eax
        lea  ebx,[edi+esi*4+0x3ad4e0]
        je loc_0044847F
        call FUN_00447f70
    loc_0044847F:
        mov  ecx,DWORD PTR [esp+0x38]
        mov  edx,DWORD PTR [esp+0x40]
        mov  eax,DWORD PTR [esp+0x3c]
        mov  DWORD PTR [esp+0x10],ecx
        add  ecx,edx
        mov  edx,DWORD PTR [esp+0x50]
        mov  DWORD PTR [esp+0x18],ecx
        mov  ecx,DWORD PTR [esp+0x44]
        mov  DWORD PTR [esp+0x14],eax
        add  eax,ecx
        mov  ecx,DWORD PTR [esp+0x48]
        mov  DWORD PTR [esp+0x20],ecx
        add  ecx,edx
        mov  DWORD PTR [esp+0x1c],eax
        mov  eax,DWORD PTR [esp+0x4c]
        lea  edx,[esp+0x54]
        push  edx
        mov  DWORD PTR [esp+0x28],eax
        push  0x0
        add  eax,ebp
        push  0x0
        mov  DWORD PTR [esp+0x38],eax
        mov  eax,ds:0x491c30
        push  0x0
        mov  DWORD PTR [esp+0x38],ecx
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x48]
        test  eax,eax
        jne loc_004485C1
        mov  eax,DWORD PTR [esp+0x50]
        imul  esi,esi,0x1c
        push  0x0
        push  ebx
        push  0x1
        push  0x0
        add  esi,edi
        mov  DWORD PTR [esi+0x3ad6e0],eax
        mov  DWORD PTR [esi+0x3ad6e4],ebp
        mov  edx,DWORD PTR ds:0x491d14
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x0
        push  edx
        mov  edx,DWORD PTR [esp+0x68]
        push  ebp
        push  edx
        push  eax
        call  DWORD PTR [ecx+0x70]
        test  eax,eax
        je loc_00448547
        mov  edx,DWORD PTR ds:0x491d14
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x0
        push  ebx
        push  0x3
        push  edx
        mov  edx,DWORD PTR [esi+0x3ad6e4]
        push  edx
        mov  edx,DWORD PTR [esi+0x3ad6e0]
        push  edx
        push  eax
        call  DWORD PTR [ecx+0x90]
        test  eax,eax
        jne loc_004485B3
    loc_00448547:
        mov  ecx,DWORD PTR [esp+0x34]
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x0
        lea  edi,[edi+ecx*4+0x3ad560]
        mov  ecx,DWORD PTR ds:0x491d14
        push  edi
        push  0x3
        push  ecx
        mov  ecx,DWORD PTR [esi+0x3ad6e4]
        push  ecx
        mov  ecx,DWORD PTR [esi+0x3ad6e0]
        push  ecx
        push  eax
        call  DWORD PTR [edx+0x90]
        test  eax,eax
        jne loc_004485B3
        push  eax
        push  0xffffffff
        lea  edx,[esp+0x18]
        push  edx
        mov  edx,DWORD PTR [ebx]
        push  eax
        mov  eax,DWORD PTR [esp+0x64]
        push  eax
        lea  ecx,[esp+0x34]
        push  ecx
        push  0x0
        push  edx
        call D3DXLoadSurfaceFromSurface
        test  eax,eax
        jne loc_004485B3
        mov  ecx,DWORD PTR [edi]
        push  eax
        push  0xffffffff
        push  eax
        push  eax
        mov  eax,DWORD PTR [ebx]
        push  eax
        push  0x0
        push  0x0
        push  ecx
        call D3DXLoadSurfaceFromSurface
    loc_004485B3:
        mov  eax,DWORD PTR [esp+0x54]
        test  eax,eax
        je loc_004485C1
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
    loc_004485C1:
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        add  esp,0x20
        ret  0x24
    }
}
