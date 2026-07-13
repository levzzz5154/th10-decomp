// 00422150: FUN_00422150
// Original size: 208 bytes, actual code: 47 instructions
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);

extern "C" __declspec(naked) void FUN_00422150(void) {
    __asm {
        push  esi
        push  edi
        push  0x422a90
        call FUN_00449ed0
        mov  esi,eax
        mov  edi,DWORD PTR [esi+0x4]
        mov  eax,ds:0x491be4
        and  edi,0xfffffffd
        mov  DWORD PTR [esi+0x4],edi
        push  eax
        mov  edi,0x9
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449ae0
        push  0x422aa0
        mov  DWORD PTR [ebx+0x8],esi
        call FUN_00449ed0
        mov  ecx,DWORD PTR ds:0x491be4
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x4]
        and  eax,0xfffffffd
        push  ecx
        mov  edi,0x2e
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],eax
        call FUN_00449b70
        mov  DWORD PTR [ebx+0xc],esi
        mov  eax,DWORD PTR [ebx+0x20]
        xor  ecx,ecx
        test  al,0x1
        pop  edi
        pop  esi
        jne loc_004221CE
        or   eax,0x1
        mov  DWORD PTR [ebx+0x14],ecx
        mov  DWORD PTR [ebx+0x10],0xfff0bdc1
        mov  DWORD PTR [ebx+0x18],ecx
        mov  DWORD PTR [ebx+0x1c],0x476f78
        mov  DWORD PTR [ebx+0x20],eax
    loc_004221CE:
        mov  DWORD PTR [ebx+0x14],ecx
        mov  DWORD PTR [ebx+0x18],ecx
        mov  DWORD PTR [ebx+0x10],0xffffffff
        xor  eax,eax
        ret
    }
}
