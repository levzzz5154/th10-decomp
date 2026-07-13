// 00408750: FUN_00408750
// Original size: 368 bytes, actual code: 16 instructions
extern "C" void FUN_0044bb20(void);

extern "C" __declspec(naked) void FUN_00408750(void) {
    __asm {
        push  ecx
        mov  DWORD PTR [esp],ecx
        mov  eax,DWORD PTR [esp]
        fld  DWORD PTR [esp+0x8]
        fsincos
        fmul  DWORD PTR [esp+0xc]
        fstp  DWORD PTR [eax]
        fmul  DWORD PTR [esp+0xc]
        fstp  DWORD PTR [eax+0x4]
        pop  ecx
        ret  0x8
    }
}
