// 00409230: FUN_00409230
// Original size: 64 bytes, actual code: 13 instructions
extern "C" void FUN_004451c0(void);

extern "C" __declspec(naked) void FUN_00409230(void) {
    __asm {
        push  esi
        mov  esi,ecx
        test  BYTE PTR [esi+0x378c],0x1
        je loc_0040925B
        mov  ecx,DWORD PTR ds:0x491c10
        lea  eax,[esi+0x10]
        call FUN_004451c0
        mov  ecx,DWORD PTR ds:0x491c10
        lea  eax,[esi+0x3bc]
        call FUN_004451c0
    loc_0040925B:
        mov  eax,0x1
        pop  esi
        ret
    }
}
