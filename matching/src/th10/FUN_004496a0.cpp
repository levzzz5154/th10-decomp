// 004496A0: FUN_004496a0
// Original size: 48 bytes, actual code: 10 instructions
extern "C" void FUN_0043e5a0(void);
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_004496a0(void) {
    __asm {
        mov  ecx,DWORD PTR [eax]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        call FUN_004491c0
        test  eax,eax
        je loc_004496BF
        mov  edx,DWORD PTR [esp+0x8]
        mov  ecx,DWORD PTR [esp+0x4]
        call FUN_0043e5a0
    loc_004496BF:
        ret  0x8
    }
}
