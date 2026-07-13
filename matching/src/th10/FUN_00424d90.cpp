// 00424D90: FUN_00424d90
// Original size: 320 bytes, actual code: 68 instructions
extern "C" void FUN_00413790(void);
extern "C" void FUN_004492a0(void);

extern "C" __declspec(naked) void FUN_00424d90(void) {
    __asm {
        mov  DWORD PTR [esi+0x458],0x1
        mov  eax,DWORD PTR [esi+0x470]
        push  edi
        xor  edi,edi
        test  al,0x1
        mov  edx,0xfff0bdc1
        mov  ecx,0x476f78
        jne loc_00424DD2
        or   eax,0x1
        mov  DWORD PTR [esi+0x464],edi
        mov  DWORD PTR [esi+0x460],edx
        mov  DWORD PTR [esi+0x468],edi
        mov  DWORD PTR [esi+0x46c],ecx
        mov  DWORD PTR [esi+0x470],eax
    loc_00424DD2:
        mov  DWORD PTR [esi+0x464],0xffffffff
        mov  DWORD PTR [esi+0x468],0xbf800000
        mov  DWORD PTR [esi+0x460],0xfffffffe
        mov  eax,DWORD PTR [esi+0x484]
        test  al,0x1
        jne loc_00424E1B
        or   eax,0x1
        mov  DWORD PTR [esi+0x478],edi
        mov  DWORD PTR [esi+0x474],edx
        mov  DWORD PTR [esi+0x47c],edi
        mov  DWORD PTR [esi+0x480],ecx
        mov  DWORD PTR [esi+0x484],eax
    loc_00424E1B:
        mov  DWORD PTR [esi+0x478],edi
        mov  DWORD PTR [esi+0x47c],edi
        mov  DWORD PTR [esi+0x474],0xffffffff
        mov  eax,DWORD PTR [esi+0x498]
        test  al,0x1
        jne loc_00424E5C
        or   eax,0x1
        mov  DWORD PTR [esi+0x48c],edi
        mov  DWORD PTR [esi+0x488],edx
        mov  DWORD PTR [esi+0x490],edi
        mov  DWORD PTR [esi+0x494],ecx
        mov  DWORD PTR [esi+0x498],eax
    loc_00424E5C:
        mov  edx,DWORD PTR ds:0x491c10
        mov  DWORD PTR [esi+0x48c],edi
        mov  DWORD PTR [esi+0x490],edi
        mov  DWORD PTR [esi+0x488],0xffffffff
        mov  eax,DWORD PTR [esi+0x329c]
        push  eax
        call FUN_004492a0
        mov  eax,ds:0x47770c
        mov  DWORD PTR [esi+0x329c],edi
        mov  DWORD PTR [esi+0x329c],edi
        mov  ecx,DWORD PTR ds:0x474c70
        pop  edi
        jmp FUN_00413790
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        xor  eax,eax
        ret
    }
}
