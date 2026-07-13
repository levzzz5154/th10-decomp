// 00401520: FUN_00401520
// Original size: 16 bytes, actual code: 5 instructions
extern "C" void FUN_00401a50(void);

extern "C" __declspec(naked) void FUN_00401520(void) {
    __asm {
        push  ebx
        mov  ebx,ecx
        call FUN_00401a50
        pop  ebx
        ret
    }
}
