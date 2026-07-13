// 00413270: FUN_00413270
// Original size: 224 bytes, actual code: 16 instructions
extern "C" void FUN_0044bb90(void);

extern "C" __declspec(naked) void FUN_00413270(void) {
    __asm {
        push  ecx
        mov  DWORD PTR [esp],ecx
        mov  eax,DWORD PTR [esp]
        fld  DWORD PTR [esp+0x8]
        fsincos
        fmul  DWORD PTR [esp+0xc]
        fstp  DWORD PTR [eax]
        fmul  DWORD PTR [esp+0x10]
        fstp  DWORD PTR [eax+0x4]
        pop  ecx
        ret  0xc
    }
}
