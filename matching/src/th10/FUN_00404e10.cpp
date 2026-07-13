// 00404E10: FUN_00404e10
// Original size: 192 bytes, actual code: 31 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00404e10(void) {
    __asm {
        fld  DWORD PTR [eax+0x14]
        fadd  DWORD PTR [ecx+0x14]
        fld  DWORD PTR [eax+0x10]
        fadd  DWORD PTR [ecx+0x10]
        fld  DWORD PTR [eax+0xc]
        fadd  DWORD PTR [ecx+0xc]
        fld  DWORD PTR [eax+0x8]
        fadd  DWORD PTR [ecx+0x8]
        fld  DWORD PTR [eax+0x4]
        fadd  DWORD PTR [ecx+0x4]
        fld  DWORD PTR [eax]
        fadd  DWORD PTR [ecx]
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
        ret
    }
}
