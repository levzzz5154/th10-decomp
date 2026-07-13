// 00441EF0: FUN_00441ef0
// Original size: 96 bytes, actual code: 17 instructions

extern "C" __declspec(naked) void FUN_00441ef0(void) {
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
