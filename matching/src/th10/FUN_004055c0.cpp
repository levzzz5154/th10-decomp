// 004055C0: FUN_004055c0
// Original size: 96 bytes, actual code: 26 instructions
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);

extern "C" __declspec(naked) void FUN_004055c0(void) {
    __asm {
        push  esi
        push  edi
        push  0x405840
        call FUN_00449ed0
        mov  esi,eax
        or   DWORD PTR [esi+0x4],0x2
        mov  eax,ds:0x491be4
        push  eax
        mov  edi,0x11
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449ae0
        push  0x405850
        mov  DWORD PTR [ebx+0x8],esi
        call FUN_00449ed0
        mov  esi,eax
        or   DWORD PTR [esi+0x4],0x2
        mov  ecx,DWORD PTR ds:0x491be4
        push  ecx
        mov  edi,0x22
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449b70
        pop  edi
        mov  DWORD PTR [ebx+0xc],esi
        xor  eax,eax
        pop  esi
        ret
    }
}
