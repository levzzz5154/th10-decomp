// 0041C120: FUN_0041c120
// Original size: 160 bytes, actual code: 41 instructions
extern "C" void FUN_00447280(void);
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);
extern "C" void FUN_0044b810(void);

extern "C" __declspec(naked) void FUN_0041c120(void) {
    __asm {
        mov  edx,DWORD PTR ds:0x491c10
        push  0x46cd88
        mov  ecx,0x7
        call FUN_00447280
        test  eax,eax
        mov  DWORD PTR [ebx+0x458],eax
        jne loc_0041C155
        push  0x46cd54
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        or   eax,0xffffffff
        ret
    loc_0041C155:
        push  esi
        push  edi
        push  0x41c480
        call FUN_00449ed0
        mov  esi,eax
        and  DWORD PTR [esi+0x4],0xfffffffd
        mov  eax,ds:0x491be4
        push  eax
        mov  edi,0x13
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449ae0
        push  0x41c4e0
        mov  DWORD PTR [ebx+0x8],esi
        call FUN_00449ed0
        mov  esi,eax
        and  DWORD PTR [esi+0x4],0xfffffffd
        mov  ecx,DWORD PTR ds:0x491be4
        push  ecx
        mov  edi,0x1b
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449b70
        lea  edx,[ebx+0x10]
        pop  edi
        mov  DWORD PTR [ebx+0xc],esi
        mov  DWORD PTR [ebx+0x434],edx
        xor  eax,eax
        pop  esi
        ret
    }
}
