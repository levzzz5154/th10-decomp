// 00404DA0: FUN_00404da0
// Original size: 112 bytes, actual code: 31 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00404da0(void) {
    __asm {
        fld  DWORD PTR [esp+0x4]
        fmul  DWORD PTR [eax+0x14]
        fld  DWORD PTR [esp+0x4]
        fmul  DWORD PTR [eax+0x10]
        fld  DWORD PTR [esp+0x4]
        fmul  DWORD PTR [eax+0xc]
        fld  DWORD PTR [esp+0x4]
        fmul  DWORD PTR [eax+0x8]
        fld  DWORD PTR [esp+0x4]
        fmul  DWORD PTR [eax+0x4]
        fld  DWORD PTR [esp+0x4]
        fmul  DWORD PTR [eax]
        fstp  DWORD PTR [esi]
        fstp  DWORD PTR [esi+0x4]
        fst  DWORD PTR [esi+0x8]
        fld  st(1)
        fstp  DWORD PTR [esi+0xc]
        fld  st(2)
        fstp  DWORD PTR [esi+0x10]
        fld  st(3)
        fstp  DWORD PTR [esi+0x14]
        call FUN_00463b2c
        mov  BYTE PTR [esi+0x18],al
        call FUN_00463b2c
        mov  BYTE PTR [esi+0x19],al
        call FUN_00463b2c
        mov  BYTE PTR [esi+0x1a],al
        call FUN_00463b2c
        mov  BYTE PTR [esi+0x1b],al
        mov  eax,esi
        ret  0x4
    }
}
