// 00404530: FUN_00404530
// Original size: 128 bytes, actual code: 23 instructions
extern "C" void FUN_0043c8b0(void);

extern "C" __declspec(naked) void FUN_00404530(void) {
    __asm {
        push  ebx
        push  0x0
        push  0x0
        push  0x0
        push  0x1e
        push  0x2
        mov  ebx,0xf
        call FUN_0043c8b0
        mov  eax,DWORD PTR [esi+0x2a2c]
        test  al,0x1
        pop  ebx
        jne loc_00404581
        or   eax,0x1
        mov  DWORD PTR [esi+0x2a20],0x0
        mov  DWORD PTR [esi+0x2a1c],0xfff0bdc1
        mov  DWORD PTR [esi+0x2a24],0x0
        mov  DWORD PTR [esi+0x2a28],0x476f78
        mov  DWORD PTR [esi+0x2a2c],eax
    loc_00404581:
        mov  DWORD PTR [esi+0x2a20],0x1e
        mov  DWORD PTR [esi+0x2a24],0x41f00000
        mov  DWORD PTR [esi+0x2a1c],0x1d
        or   DWORD PTR [esi+0x2a18],0x2
        ret
    }
}
