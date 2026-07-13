// 00428DD0: FUN_00428dd0
// Original size: 64 bytes, actual code: 9 instructions
extern "C" void FUN_0044bf40(void);

extern "C" __declspec(naked) void FUN_00428dd0(void) {
    __asm {
        push  ecx
        neg  eax
        mov  DWORD PTR [esp],eax
        fild  DWORD PTR [esp]
        push  ecx
        fstp  DWORD PTR [esp]
        call FUN_0044bf40
        pop  ecx
        ret
    }
}
