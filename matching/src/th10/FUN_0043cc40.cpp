// 0043CC40: FUN_0043cc40
// Original size: 240 bytes, actual code: 70 instructions
extern "C" void FUN_0043cd30(void);

extern "C" __declspec(naked) void FUN_0043cc40(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x5218]
        test  eax,eax
        je loc_0043CCEC
        mov  ecx,DWORD PTR [esi+0x5224]
        test  ecx,ecx
        jne loc_0043CC62
        mov  DWORD PTR [esi+0x5224],0x1
    loc_0043CC62:
        push  ebx
        push  edi
        mov  edi,DWORD PTR ds:0x46611c
        push  0x64
        push  eax
        call  edi
        cmp  eax,0x102
        mov  ebx,DWORD PTR ds:0x4660ac
        jne loc_0043CC96
        nop
    loc_0043CC80:
        push  0x1
        call  ebx
        mov  eax,DWORD PTR [esi+0x5218]
        push  0x64
        push  eax
        call  edi
        cmp  eax,0x102
        je loc_0043CC80
    loc_0043CC96:
        mov  ecx,DWORD PTR [esi+0x521c]
        push  0x64
        push  ecx
        call  edi
        cmp  eax,0x102
        jne loc_0043CCBE
    loc_0043CCA8:
        push  0x1
        call  ebx
        mov  edx,DWORD PTR [esi+0x521c]
        push  0x64
        push  edx
        call  edi
        cmp  eax,0x102
        je loc_0043CCA8
    loc_0043CCBE:
        mov  eax,DWORD PTR [esi+0x5218]
        mov  edi,DWORD PTR ds:0x4660cc
        push  eax
        call  edi
        mov  ecx,DWORD PTR [esi+0x521c]
        push  ecx
        call  edi
        pop  edi
        mov  DWORD PTR [esi+0x5218],0x0
        mov  DWORD PTR [esi+0x521c],0x0
        pop  ebx
    loc_0043CCEC:
        xor  eax,eax
        ret
    }
}
