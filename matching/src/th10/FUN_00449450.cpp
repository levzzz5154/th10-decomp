// 00449450: FUN_00449450
// Original size: 32 bytes, actual code: 8 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_00449450(void) {
    __asm {
        mov  eax,DWORD PTR [esi]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004491c0
        test  eax,eax
        jne loc_00449464
        mov  DWORD PTR [esi],eax
    loc_00449464:
        ret
    }
}
