// 00408030: FUN_00408030
// Original size: 208 bytes, actual code: 52 instructions
extern "C" void FUN_004086b0(void);
extern "C" void FUN_00448db0(void);

extern "C" __declspec(naked) void FUN_00408030(void) {
    __asm {
        push  ecx
        mov  ax,WORD PTR [esi+0x446]
        cmp  ax,0x2
        je loc_00408048
        cmp  ax,0x1
        je loc_00408048
        xor  eax,eax
        pop  ecx
        ret
    loc_00408048:
        push  0x41000000
        lea  ecx,[esi+0x3b4]
        push  0x41000000
        call FUN_004086b0
        test  eax,eax
        mov  WORD PTR [esi+0x30c],0x1
        mov  WORD PTR [esi+0x446],0x3
        jne loc_004080ED
        mov  eax,DWORD PTR [esi+0x438]
        push  ebp
        xor  ebp,ebp
        cmp  eax,ebp
        jl loc_0040809C
        mov  edx,DWORD PTR ds:0x4776f0
        push  edi
        push  eax
        lea  eax,[esp+0xc]
        push  eax
        mov  eax,DWORD PTR [edx+0x3e0b50]
        push  eax
        mov  edi,ecx
        call FUN_00448db0
        pop  edi
    loc_0040809C:
        mov  eax,DWORD PTR [esi+0x408]
        test  al,0x1
        jne loc_004080CF
        or   eax,0x1
        mov  DWORD PTR [esi+0x3fc],ebp
        mov  DWORD PTR [esi+0x3f8],0xfff0bdc1
        mov  DWORD PTR [esi+0x400],ebp
        mov  DWORD PTR [esi+0x404],0x476f78
        mov  DWORD PTR [esi+0x408],eax
    loc_004080CF:
        mov  DWORD PTR [esi+0x3fc],ebp
        mov  DWORD PTR [esi+0x400],ebp
        mov  DWORD PTR [esi+0x3f8],0xffffffff
        pop  ebp
        mov  eax,0x1
        pop  ecx
        ret
    loc_004080ED:
        or   DWORD PTR [esi],0x8
        mov  eax,0x1
        pop  ecx
        ret
    }
}
