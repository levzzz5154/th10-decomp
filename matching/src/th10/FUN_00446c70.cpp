// 00446C70: FUN_00446c70
// Original size: 256 bytes, actual code: 76 instructions
extern "C" void FUN_004465b0(void);
extern "C" void D3DXLoadSurfaceFromMemory(void);
extern "C" void D3DXLoadSurfaceFromFileInMemory(void);

extern "C" __declspec(naked) void FUN_00446c70(void) {
    __asm {
        sub  esp,0x18
        test  BYTE PTR ds:0x491d78,0x1
        mov  DWORD PTR [esp+0x4],eax
        je loc_00446CA7
        mov  eax,DWORD PTR [eax*4+0x46f288]
        cmp  eax,0x15
        je loc_00446C9F
        test  eax,eax
        je loc_00446C9F
        cmp  eax,0x14
        jne loc_00446CA7
        mov  DWORD PTR [esp+0x4],0x3
        jmp loc_00446CA7
    loc_00446C9F:
        mov  DWORD PTR [esp+0x4],0x5
    loc_00446CA7:
        mov  eax,DWORD PTR [edi]
        lea  edx,[esp]
        push  edx
        push  0x0
        mov  DWORD PTR [edi+0x8],ebx
        mov  DWORD PTR [esp+0x8],0x0
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x48]
        mov  eax,DWORD PTR [esp+0x20]
        test  eax,eax
        push  0x0
        jne loc_00446CE2
        mov  eax,DWORD PTR [esp+0x4]
        push  0x0
        push  0x1
        push  0x0
        push  ebx
        push  esi
        push  0x0
        push  0x0
        push  eax
        call D3DXLoadSurfaceFromFileInMemory
        jmp loc_00446D3D
    loc_00446CE2:
        mov  ecx,DWORD PTR [esi+0x30]
        lea  eax,[ecx+esi*1]
        mov  DWORD PTR [esp+0xc],0x0
        mov  DWORD PTR [esp+0x10],0x0
        movsx edx,WORD PTR [eax+0x8]
        mov  DWORD PTR [esp+0x14],edx
        movsx ecx,WORD PTR [eax+0xa]
        push  0x1
        mov  DWORD PTR [esp+0x1c],ecx
        movsx ecx,WORD PTR [eax+0x6]
        lea  edx,[esp+0x10]
        push  edx
        movsx edx,WORD PTR [eax+0x8]
        shl  ecx,0x2
        imul  edx,DWORD PTR [ecx+0x46f2a0]
        mov  ecx,DWORD PTR [ecx+0x46f288]
        push  0x0
        push  edx
        mov  edx,DWORD PTR [esp+0x14]
        push  ecx
        add  eax,0x10
        push  eax
        push  0x0
        push  0x0
        push  edx
        call D3DXLoadSurfaceFromMemory
    loc_00446D3D:
        mov  eax,DWORD PTR [esp]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  eax,edi
        call FUN_004465b0
        mov  edx,DWORD PTR [esp+0x4]
        mov  eax,DWORD PTR [edx*4+0x46f2a0]
        mov  DWORD PTR [edi+0xc],eax
        xor  eax,eax
        add  esp,0x18
        ret  0x8
    }
}
