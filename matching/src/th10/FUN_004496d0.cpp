// 004496D0: FUN_004496d0
// Original size: 256 bytes, actual code: 10 instructions
extern "C" void FUN_0043e8b0(void);
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_004496d0(void) {
    __asm {
        mov  ecx,DWORD PTR [eax]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        call FUN_004491c0
        test  eax,eax
        je loc_004496F1
        mov  ecx,DWORD PTR [esp+0x4]
        mov  edx,DWORD PTR [eax+0x308]
        call FUN_0043e8b0
    loc_004496F1:
        ret  0x4
    }
}
