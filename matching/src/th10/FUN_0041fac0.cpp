// 0041FAC0: FUN_0041fac0
// Original size: 144 bytes, actual code: 41 instructions
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);
extern "C" void FUN_0044c150(void);
extern "C" void __beginthreadex(void);

extern "C" __declspec(naked) void FUN_0041fac0(void) {
    __asm {
        push  esi
        push  edi
        push  0x41feb0
        call FUN_00449ed0
        mov  esi,eax
        and  DWORD PTR [esi+0x4],0xfffffffd
        mov  eax,ds:0x491be4
        push  eax
        mov  edi,0x3
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449ae0
        push  0x41fef0
        mov  DWORD PTR [ebx+0x8],esi
        call FUN_00449ed0
        mov  esi,eax
        and  DWORD PTR [esi+0x4],0xfffffffd
        mov  ecx,DWORD PTR ds:0x491be4
        push  ecx
        mov  edi,0x2
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449b70
        mov  DWORD PTR [ebx+0xc],esi
        lea  esi,[ebx+0x10]
        call FUN_0044c150
        lea  edx,[esi+0x8]
        push  edx
        push  0x0
        push  ebx
        push  0x41f990
        push  0x0
        push  0x0
        mov  DWORD PTR [esi+0x18],0x41f990
        mov  DWORD PTR [esi+0x10],0x1
        mov  DWORD PTR [esi+0xc],0x0
        call __beginthreadex
        add  esp,0x18
        mov  DWORD PTR [esi+0x4],eax
        pop  edi
        xor  eax,eax
        pop  esi
        ret
    }
}
