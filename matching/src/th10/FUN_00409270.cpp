// 00409270: FUN_00409270
// Original size: 16 bytes, actual code: 5 instructions
extern "C" void FUN_004091c0(void);

extern "C" __declspec(naked) void FUN_00409270(void) {
    __asm {
        push  ebx
        mov  ebx,ecx
        call FUN_004091c0
        pop  ebx
        ret
    }
}
