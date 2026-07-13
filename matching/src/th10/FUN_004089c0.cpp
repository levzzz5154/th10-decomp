// 004089C0: FUN_004089c0
// Original size: 304 bytes, actual code: 53 instructions
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);

extern "C" __declspec(naked) void FUN_004089c0(void) {
    __asm {
        push  esi
        push  edi
        push  0x409220
        call FUN_00449ed0
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x4]
        mov  eax,ds:0x491be4
        and  edx,0xfffffffd
        push  eax
        mov  edi,0x16
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],edx
        call FUN_00449ae0
        push  0x409230
        mov  DWORD PTR [ebx+0x8],esi
        call FUN_00449ed0
        mov  ecx,DWORD PTR ds:0x491be4
        mov  esi,eax
        and  DWORD PTR [esi+0x4],0xfffffffd
        push  ecx
        mov  edi,0xe
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449b70
        push  0x409270
        mov  DWORD PTR [ebx+0xc],esi
        call FUN_00449ed0
        mov  edx,DWORD PTR ds:0x491be4
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x4]
        and  eax,0xfffffffd
        push  edx
        mov  edi,0x25
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],eax
        call FUN_00449b70
        mov  DWORD PTR [ebx+0x37ac],esi
        mov  eax,DWORD PTR [ebx+0x3744]
        xor  ecx,ecx
        test  al,0x1
        pop  edi
        pop  esi
        jne loc_00408A7A
        or   eax,0x1
        mov  DWORD PTR [ebx+0x3738],ecx
        mov  DWORD PTR [ebx+0x3734],0xfff0bdc1
        mov  DWORD PTR [ebx+0x373c],ecx
        mov  DWORD PTR [ebx+0x3740],0x476f78
        mov  DWORD PTR [ebx+0x3744],eax
    loc_00408A7A:
        mov  DWORD PTR [ebx+0x3738],ecx
        mov  DWORD PTR [ebx+0x373c],ecx
        mov  DWORD PTR [ebx+0x3734],0xffffffff
        xor  eax,eax
        ret
    }
}
