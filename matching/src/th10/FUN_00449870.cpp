// 00449870: FUN_00449870
// Original size: 224 bytes, actual code: 47 instructions
extern "C" void FUN_0043e7e0(void);

extern "C" __declspec(naked) void FUN_00449870(void) {
    __asm {
        sub  esp,0xc
        mov  edx,DWORD PTR [esp+0x10]
        push  esi
        push  edi
        mov  DWORD PTR [esp+0x8],0x0
        mov  edi,DWORD PTR [esp+0x8]
        lea  esi,[edx+0x340]
        mov  DWORD PTR [esi],edi
        mov  DWORD PTR [esp+0xc],0x0
        mov  edi,DWORD PTR [esp+0xc]
        mov  DWORD PTR [esi+0x4],edi
        mov  DWORD PTR [esp+0x10],0x0
        mov  edi,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esi+0x8],edi
        mov  DWORD PTR [esp+0x8],0x0
        mov  edi,DWORD PTR [esp+0x8]
        lea  esi,[edx+0x334]
        mov  DWORD PTR [esi],edi
        mov  DWORD PTR [esp+0xc],0x0
        mov  edi,DWORD PTR [esp+0xc]
        mov  DWORD PTR [esi+0x4],edi
        mov  DWORD PTR [esp+0x10],0x0
        mov  edi,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esi+0x8],edi
        mov  eax,ecx
        mov  ecx,DWORD PTR [edx+0x35c]
        lea  esi,[edx+0x34c]
        mov  DWORD PTR [esp+0x8],0x0
        mov  edi,DWORD PTR [esp+0x8]
        mov  DWORD PTR [esi],edi
        or   ecx,0x40000000
        mov  DWORD PTR [esp+0xc],0x0
        mov  edi,DWORD PTR [esp+0xc]
        mov  DWORD PTR [esi+0x4],edi
        mov  DWORD PTR [edx+0x35c],ecx
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esp+0x10],0x0
        mov  edi,DWORD PTR [esp+0x10]
        mov  WORD PTR [edx+0x38a],cx
        mov  DWORD PTR [esi+0x8],edi
        mov  BYTE PTR [edx+0x3a1],0x10
        mov  BYTE PTR [edx+0x3a0],0x10
        call FUN_0043e7e0
        pop  edi
        pop  esi
        add  esp,0xc
        ret  0x8
    }
}
