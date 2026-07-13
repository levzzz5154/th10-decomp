// 00449670: FUN_00449670
// Original size: 48 bytes, actual code: 10 instructions
extern "C" void FUN_0043e5a0(void);
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_00449670(void) {
    __asm {
        mov  ecx,DWORD PTR [eax]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        call FUN_004491c0
        test  eax,eax
        je loc_00449691
        mov  edx,DWORD PTR [esp+0x4]
        mov  ecx,DWORD PTR [eax+0x308]
        call FUN_0043e5a0
    loc_00449691:
        ret  0x4
    }
}
