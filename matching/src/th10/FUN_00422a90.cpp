// 00422A90: FUN_00422a90
// Original size: 32 bytes, actual code: 5 instructions
extern "C" void FUN_004223f0(void);

extern "C" __declspec(naked) void FUN_00422a90(void) {
    __asm {
        push  esi
        mov  esi,ecx
        call FUN_004223f0
        pop  esi
        ret
    }
}
