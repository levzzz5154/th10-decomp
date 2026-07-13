// 00412A00: FUN_00412a00
// Original size: 16 bytes, actual code: 5 instructions
extern "C" void FUN_0044fdb0(void);

extern "C" __declspec(naked) void FUN_00412a00(void) {
    __asm {
        mov  eax,DWORD PTR [eax+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  ecx
        call FUN_0044fdb0
        ret
    }
}
