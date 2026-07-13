// 0042B4D0: FUN_0042b4d0
// Original size: 160 bytes, actual code: 45 instructions
extern "C" void FUN_00401de0(void);
extern "C" void FUN_0043e5a0(void);
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);

extern "C" __declspec(naked) void FUN_0042b4d0(void) {
    __asm {
        push  ebx
        push  esi
        mov  ebx,eax
        mov  eax,ds:0x4776e0
        mov  ecx,DWORD PTR [eax+0x8994]
        push  edi
        push  0x42b9a0
        mov  DWORD PTR [ebx+0x10],ecx
        call FUN_00449ed0
        mov  edx,DWORD PTR ds:0x491be4
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x4]
        and  eax,0xfffffffd
        push  edx
        mov  edi,0xf
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],eax
        call FUN_00449ae0
        push  0x42b9b0
        mov  DWORD PTR [ebx+0x8],esi
        call FUN_00449ed0
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x4]
        mov  eax,ds:0x491be4
        and  edx,0xfffffffd
        push  eax
        mov  edi,0x23
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],edx
        call FUN_00449b70
        mov  DWORD PTR [ebx+0xc],esi
        lea  esi,[ebx+0x18]
        mov  ebx,DWORD PTR [ebx+0x10]
        mov  edx,esi
        call FUN_00401de0
        mov  edx,0xc4
        mov  eax,esi
        mov  ecx,ebx
        mov  DWORD PTR [esi+0x308],ebx
        call FUN_0043e5a0
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebx
        ret
    }
}
