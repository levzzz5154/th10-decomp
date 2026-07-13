// 0042CAA0: FUN_0042caa0
// Original size: 192 bytes, actual code: 52 instructions
extern "C" void FUN_00447280(void);
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);
extern "C" void FUN_0044b810(void);

extern "C" __declspec(naked) void FUN_0042caa0(void) {
    __asm {
        push  esi
        push  edi
        push  0x42d2e0
        call FUN_00449ed0
        mov  esi,eax
        mov  edi,DWORD PTR [esi+0x4]
        mov  eax,ds:0x491be4
        and  edi,0xfffffffd
        mov  DWORD PTR [esi+0x4],edi
        push  eax
        mov  edi,0x6
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449ae0
        push  0x42d2f0
        mov  DWORD PTR [ebx+0xc],esi
        call FUN_00449ed0
        mov  ecx,DWORD PTR ds:0x491be4
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x4]
        and  eax,0xfffffffd
        push  ecx
        mov  edi,0x3
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],eax
        call FUN_00449b70
        mov  edx,DWORD PTR ds:0x491c10
        push  0x46f0ac
        mov  ecx,0x19
        mov  DWORD PTR [ebx+0x10],esi
        call FUN_00447280
        test  eax,eax
        pop  edi
        mov  DWORD PTR [ebx+0x14],eax
        pop  esi
        je loc_0042CB33
        mov  edx,DWORD PTR ds:0x491c10
        push  0x46f0a0
        mov  ecx,0x1a
        call FUN_00447280
        test  eax,eax
        mov  DWORD PTR [ebx+0x18],eax
        jne loc_0042CB49
    loc_0042CB33:
        push  0x46cb68
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        or   eax,0xffffffff
        ret
    loc_0042CB49:
        mov  DWORD PTR [ebx+0xf4],0x1
        mov  DWORD PTR ds:0x4918a4,0x0
        xor  eax,eax
        ret
    }
}
