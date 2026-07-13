// 0044C5D0: FUN_0044c5d0
// Original size: 528 bytes, actual code: 16 instructions

extern "C" __declspec(naked) void FUN_0044c5d0(void) {
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
