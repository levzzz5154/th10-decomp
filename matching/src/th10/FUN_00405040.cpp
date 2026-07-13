// 00405040: FUN_00405040
// Original size: 144 bytes, actual code: 41 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00405040(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x4]
        fld  DWORD PTR [esp+0xc]
        mov  ecx,DWORD PTR [esp+0x8]
        mov  edx,DWORD PTR [esp+0xc]
        mov  DWORD PTR [esi],eax
        mov  eax,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esi+0x4],ecx
        mov  ecx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [esi+0x8],edx
        mov  edx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [esi+0xc],eax
        mov  DWORD PTR [esi+0x10],ecx
        mov  DWORD PTR [esi+0x14],edx
        call FUN_00463b2c
        fld  DWORD PTR [esp+0x10]
        mov  BYTE PTR [esi+0x18],al
        call FUN_00463b2c
        fld  DWORD PTR [esp+0x14]
        mov  BYTE PTR [esi+0x19],al
        call FUN_00463b2c
        fld  DWORD PTR [esp+0x18]
        mov  BYTE PTR [esi+0x1a],al
        call FUN_00463b2c
        mov  BYTE PTR [esi+0x1b],al
        mov  eax,esi
        ret  0x18
    }
}
