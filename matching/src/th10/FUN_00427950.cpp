// 00427950: FUN_00427950
// Original size: 16 bytes, actual code: 6 instructions
extern "C" void FUN_00427960(void);

extern "C" __declspec(naked) void FUN_00427950(void) {
    __asm {
        push  esi
        mov  esi,ecx
        call FUN_00427960
        xor  eax,eax
        pop  esi
        ret
    }
}
