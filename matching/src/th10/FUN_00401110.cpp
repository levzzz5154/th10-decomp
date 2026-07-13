// 00401110: FUN_00401110
// Original size: 336 bytes, actual code: 91 instructions
extern "C" void FUN_00401de0(void);
extern "C" void FUN_0043e5a0(void);
extern "C" void FUN_00447280(void);
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);
extern "C" void FUN_0044b810(void);

extern "C" __declspec(naked) void FUN_00401110(void) {
    __asm {
        mov  edx,DWORD PTR ds:0x491c10
        push  ebx
        push  0x46cb80
        mov  ecx,0x2
        mov  ebx,eax
        call FUN_00447280
        test  eax,eax
        mov  DWORD PTR [ebx+0x8994],eax
        je loc_0040116D
        mov  edx,DWORD PTR ds:0x491c10
        push  0x46cb5c
        xor  ecx,ecx
        call FUN_00447280
        test  eax,eax
        mov  DWORD PTR [ebx+0x899c],eax
        je loc_0040116D
        mov  edx,DWORD PTR ds:0x491c10
        push  0x46cb50
        mov  ecx,0x3
        call FUN_00447280
        test  eax,eax
        mov  DWORD PTR [ebx+0x8998],eax
        jne loc_00401184
    loc_0040116D:
        push  0x46cb68
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        or   eax,0xffffffff
        pop  ebx
        ret
    loc_00401184:
        push  esi
        push  edi
        push  0x4014f0
        call FUN_00449ed0
        mov  esi,eax
        mov  edi,DWORD PTR [esi+0x4]
        mov  eax,ds:0x491be4
        and  edi,0xfffffffd
        mov  DWORD PTR [esi+0x4],edi
        push  eax
        mov  edi,0x4
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449ae0
        push  0x401510
        mov  DWORD PTR [ebx+0xc],esi
        call FUN_00449ed0
        mov  ecx,DWORD PTR ds:0x491be4
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x4]
        and  eax,0xfffffffd
        push  ecx
        mov  edi,0x30
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],eax
        call FUN_00449b70
        push  0x401520
        mov  DWORD PTR [ebx+0x10],esi
        call FUN_00449ed0
        mov  edx,DWORD PTR ds:0x491be4
        mov  esi,eax
        mov  ecx,DWORD PTR [esi+0x4]
        and  ecx,0xfffffffd
        push  edx
        mov  edi,0x26
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],ecx
        call FUN_00449b70
        mov  edi,DWORD PTR [ebx+0x8994]
        mov  DWORD PTR [ebx+0x89a8],esi
        lea  esi,[ebx+0x14]
        mov  edx,esi
        call FUN_00401de0
        xor  edx,edx
        mov  eax,esi
        mov  ecx,edi
        mov  DWORD PTR [esi+0x308],edi
        call FUN_0043e5a0
        lea  esi,[ebx+0x3c0]
        mov  ebx,DWORD PTR [ebx+0x8994]
        mov  edx,esi
        call FUN_00401de0
        mov  edx,0x62
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
