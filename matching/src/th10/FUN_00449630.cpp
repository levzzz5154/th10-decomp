// 00449630: FUN_00449630
// Original size: 64 bytes, actual code: 6 instructions
extern "C" void FUN_004492a0(void);

extern "C" __declspec(naked) void FUN_00449630(void) {
    __asm {
        mov  eax,DWORD PTR [esi]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004492a0
        mov  DWORD PTR [esi],0x0
        ret
    }
}
