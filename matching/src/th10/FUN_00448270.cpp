// 00448270: FUN_00448270
// Original size: 480 bytes, actual code: 163 instructions
extern "C" void FUN_00442f50(void);
extern "C" void D3DXLoadSurfaceFromSurface(void);

extern "C" __declspec(naked) void FUN_00448270(void) {
    __asm {
        sub  esp,0x24
        push  ebp
        mov  ebp,DWORD PTR [esp+0x40]
        shl  eax,0x4
        push  esi
        mov  esi,ecx
        push  edi
        mov  edi,eax
        mov  eax,DWORD PTR [esi+ebx*4+0x3ad06c]
        mov  ecx,DWORD PTR [eax+0x120]
        cmp  DWORD PTR [edi+ecx*1],0x0
        je loc_00448357
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        lea  ecx,[esp+0x48]
        push  ecx
        push  0x0
        push  0x0
        push  0x0
        push  eax
        call  DWORD PTR [edx+0x48]
        test  eax,eax
        jne loc_00448357
        mov  edx,DWORD PTR [esi+ebx*4+0x3ad06c]
        mov  eax,DWORD PTR [edx+0x120]
        mov  edi,DWORD PTR [edi+eax*1]
        mov  ecx,DWORD PTR [edi]
        lea  edx,[esp+0xc]
        push  edx
        push  0x0
        push  edi
        call  DWORD PTR [ecx+0x48]
        test  eax,eax
        jne loc_0044834D
        mov  ecx,DWORD PTR [esp+0x34]
        mov  edx,DWORD PTR [esp+0x3c]
        mov  eax,DWORD PTR [esp+0x38]
        mov  DWORD PTR [esp+0x10],ecx
        add  ecx,edx
        mov  edx,DWORD PTR [esp+0x4c]
        mov  DWORD PTR [esp+0x14],eax
        mov  DWORD PTR [esp+0x18],ecx
        mov  ecx,DWORD PTR [esp+0x40]
        add  eax,ecx
        push  0x0
        mov  DWORD PTR [esp+0x20],eax
        mov  eax,DWORD PTR [esp+0x48]
        push  0x2
        mov  DWORD PTR [esp+0x28],eax
        add  eax,edx
        mov  edx,DWORD PTR [esp+0x50]
        lea  ecx,[esp+0x18]
        push  ecx
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [esp+0x34],eax
        mov  eax,DWORD PTR [esp+0x5c]
        push  0x0
        mov  DWORD PTR [esp+0x34],ebp
        add  ebp,eax
        push  edx
        lea  eax,[esp+0x34]
        push  eax
        push  0x0
        push  ecx
        mov  DWORD PTR [esp+0x4c],ebp
        call D3DXLoadSurfaceFromSurface
        test  eax,eax
        mov  eax,DWORD PTR [esp+0xc]
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
    loc_0044834D:
        mov  eax,DWORD PTR [esp+0x48]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
    loc_00448357:
        pop  edi
        pop  esi
        pop  ebp
        add  esp,0x24
        ret  0x20
        push  ecx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        shl  eax,0x4
        push  esi
        mov  esi,edx
        push  edi
        mov  edi,eax
        mov  eax,DWORD PTR [esi+ebp*4+0x3ad06c]
        mov  edx,DWORD PTR [eax+0x120]
        cmp  DWORD PTR [edi+edx*1],0x0
        je loc_0044843C
        mov  eax,DWORD PTR [esp+0x18]
        shl  ecx,0x4
        push  ebx
        mov  ebx,ecx
        mov  ecx,DWORD PTR [esi+eax*4+0x3ad06c]
        mov  edx,DWORD PTR [ecx+0x120]
        cmp  DWORD PTR [ebx+edx*1],0x0
        je loc_0044843B
        call FUN_00442f50
        mov  eax,DWORD PTR [esi+ebp*4+0x3ad06c]
        mov  ecx,DWORD PTR [eax+0x120]
        mov  edi,DWORD PTR [edi+ecx*1]
        mov  edx,DWORD PTR [edi]
        lea  eax,[esp+0x18]
        push  eax
        push  0x0
        push  edi
        call  DWORD PTR [edx+0x48]
        test  eax,eax
        jne loc_0044843B
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  edx,DWORD PTR [esi+ecx*4+0x3ad06c]
        mov  eax,DWORD PTR [edx+0x120]
        mov  eax,DWORD PTR [ebx+eax*1]
        mov  ecx,DWORD PTR [eax]
        lea  edx,[esp+0x10]
        push  edx
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x48]
        test  eax,eax
        je loc_00448404
        mov  eax,DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        pop  ebx
        pop  edi
        pop  esi
        pop  ebp
        pop  ecx
        ret  0x10
    loc_00448404:
        mov  edx,DWORD PTR [esp+0x24]
        mov  eax,DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [esp+0x20]
        push  0x0
        push  0xffffffff
        push  edx
        mov  edx,DWORD PTR [esp+0x24]
        push  0x0
        push  eax
        push  ecx
        push  0x0
        push  edx
        call D3DXLoadSurfaceFromSurface
        test  eax,eax
        mov  eax,DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  eax,DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
    loc_0044843B:
        pop  ebx
    loc_0044843C:
        pop  edi
        pop  esi
        pop  ebp
        pop  ecx
        ret  0x10
    }
}
