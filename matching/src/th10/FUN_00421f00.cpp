// 00421F00: FUN_00421f00
// Original size: 96 bytes, actual code: 16 instructions
extern "C" void FUN_00418c40(void);

extern "C" __declspec(naked) void FUN_00421f00(void) {
    __asm {
        push  edi
        lea  edx,[esi+0x120]
        call FUN_00418c40
        xor  eax,eax
        mov  DWORD PTR [esi+0x630],eax
        mov  DWORD PTR [esi+0x634],eax
        mov  DWORD PTR [esi+0x638],eax
        mov  DWORD PTR [esi+0x63c],eax
        mov  DWORD PTR [esi+0x62c],0x4703e4
        mov  ecx,0x1e1
        mov  edi,esi
        rep stosd
        or   DWORD PTR [esi+0x3cc],0x140
        mov  eax,esi
        pop  edi
        ret
    }
}
