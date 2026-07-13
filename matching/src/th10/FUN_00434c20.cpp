// 00434C20: FUN_00434c20
// Original size: 16 bytes, actual code: 5 instructions
extern "C" void FUN_00434d10(void);

extern "C" __declspec(naked) void FUN_00434c20(void) {
    __asm {
        push  esi
        mov  esi,ecx
        call FUN_00434d10
        pop  esi
        ret
    }
}
