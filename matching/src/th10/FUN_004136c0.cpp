// 004136C0: FUN_004136c0
// Original size: 208 bytes, actual code: 37 instructions
extern "C" void FUN_004492a0(void);

extern "C" __declspec(naked) void FUN_004136c0(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x40]
        push  ebx
        push  edi
        mov  edi,DWORD PTR ds:0x491c10
        push  eax
        mov  edx,edi
        call FUN_004492a0
        xor  ebx,ebx
        mov  DWORD PTR [esi+0x40],ebx
        mov  ecx,DWORD PTR [esi+0x44]
        push  ecx
        mov  edx,edi
        call FUN_004492a0
        mov  DWORD PTR [esi+0x44],ebx
        mov  edx,DWORD PTR [esi+0x48]
        push  edx
        mov  edx,edi
        call FUN_004492a0
        mov  DWORD PTR [esi+0x48],ebx
        mov  eax,DWORD PTR [esi+0x4c]
        push  eax
        mov  edx,edi
        call FUN_004492a0
        mov  DWORD PTR [esi+0x4c],ebx
        mov  ecx,DWORD PTR [esi+0x50]
        push  ecx
        mov  edx,edi
        call FUN_004492a0
        mov  DWORD PTR [esi+0x50],ebx
        mov  edx,DWORD PTR [esi+0x54]
        push  edx
        mov  edx,edi
        call FUN_004492a0
        pop  edi
        mov  DWORD PTR [esi+0x54],ebx
        pop  ebx
        ret
    }
}
