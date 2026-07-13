// 004198A0: FUN_004198a0
// Original size: 32 bytes, actual code: 5 instructions
extern "C" void FUN_00419650(void);

extern "C" __declspec(naked) void FUN_004198a0(void) {
    __asm {
        push  ebx
        mov  ebx,ecx
        call FUN_00419650
        pop  ebx
        ret
    }
}
