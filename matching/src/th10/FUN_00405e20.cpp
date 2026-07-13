// 00405E20: FUN_00405e20
// Original size: 176 bytes, actual code: 46 instructions
extern "C" void FUN_00447280(void);
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);
extern "C" void FUN_0044b810(void);

extern "C" __declspec(naked) void FUN_00405e20(void) {
    __asm {
        mov  edx,DWORD PTR ds:0x491c10
        push  0x46cd88
        mov  ecx,0x7
        call FUN_00447280
        test  eax,eax
        mov  DWORD PTR [ebx+0x3e0b50],eax
        jne loc_00405E55
        push  0x46cd54
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        or   eax,0xffffffff
        ret
    loc_00405E55:
        push  esi
        push  edi
        lea  eax,[ebx+0x60]
        push  0x406770
        mov  DWORD PTR [ebx+0x10],eax
        mov  WORD PTR [ebx+0x3e07a6],0x5
        call FUN_00449ed0
        mov  ecx,DWORD PTR ds:0x491be4
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x4]
        and  eax,0xfffffffd
        push  ecx
        mov  edi,0x14
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],eax
        call FUN_00449ae0
        push  0x4067a0
        mov  DWORD PTR [ebx+0x8],esi
        call FUN_00449ed0
        mov  edx,DWORD PTR ds:0x491be4
        mov  esi,eax
        mov  ecx,DWORD PTR [esi+0x4]
        and  ecx,0xfffffffd
        push  edx
        mov  edi,0x1d
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],ecx
        call FUN_00449b70
        pop  edi
        mov  DWORD PTR [ebx+0xc],esi
        xor  eax,eax
        pop  esi
        ret
    }
}
