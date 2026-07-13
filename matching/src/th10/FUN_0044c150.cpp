// 0044C150: FUN_0044c150
// Original size: 112 bytes, actual code: 35 instructions

extern "C" __declspec(naked) void FUN_0044c150(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x4]
        push  ebp
        xor  ebp,ebp
        cmp  eax,ebp
        je loc_0044C1B3
        push  edi
        mov  edi,DWORD PTR ds:0x46611c
        push  0xc8
        push  eax
        mov  DWORD PTR [esi+0xc],0x1
        mov  DWORD PTR [esi+0x10],ebp
        call  edi
        cmp  eax,0x102
        jne loc_0044C1A2
        push  ebx
        mov  ebx,DWORD PTR ds:0x4660ac
    loc_0044C181:
        push  0x1
        mov  DWORD PTR [esi+0xc],0x1
        mov  DWORD PTR [esi+0x10],ebp
        call  ebx
        mov  eax,DWORD PTR [esi+0x4]
        push  0xc8
        push  eax
        call  edi
        cmp  eax,0x102
        je loc_0044C181
        pop  ebx
    loc_0044C1A2:
        mov  ecx,DWORD PTR [esi+0x4]
        push  ecx
        call  DWORD PTR ds:0x4660cc
        mov  DWORD PTR [esi+0x4],ebp
        mov  DWORD PTR [esi+0x18],ebp
        pop  edi
    loc_0044C1B3:
        pop  ebp
        ret
    }
}
