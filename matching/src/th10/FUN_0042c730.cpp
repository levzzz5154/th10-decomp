// 0042C730: FUN_0042c730
// Original size: 32 bytes, actual code: 8 instructions
extern "C" void FUN_00449250(void);

extern "C" __declspec(naked) void FUN_0042c730(void) {
    __asm {
        mov  edx,DWORD PTR [eax+ecx*4+0x2c4]
        push  edi
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        mov  edi,0x2
        call FUN_00449250
        pop  edi
        ret
    }
}
