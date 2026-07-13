// 0040CEA0: FUN_0040cea0
// Original size: 160 bytes, actual code: 7 instructions
extern "C" void FUN_004492a0(void);

extern "C" __declspec(naked) void FUN_0040cea0(void) {
    __asm {
        or   DWORD PTR [esi+0x378c],0x10
        mov  eax,DWORD PTR [esi+0x774]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004492a0
        mov  DWORD PTR [esi+0x774],0x0
        ret
    }
}
