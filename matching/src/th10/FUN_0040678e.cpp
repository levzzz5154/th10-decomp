// 0040678E: FUN_0040678e
// Original size: 66 bytes, actual code: 5 instructions
extern "C" void FUN_004065c0(void);

extern "C" __declspec(naked) void FUN_0040678e(void) {
    __asm {
        push  esi
        mov  esi,ecx
        call FUN_004065c0
        pop  esi
        ret
    }
}
