// 0041BEB0: FUN_0041beb0
// Original size: 384 bytes, actual code: 14 instructions

extern "C" __declspec(naked) void FUN_0041beb0(void) {
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
