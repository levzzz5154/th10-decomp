// 00405ED0: FUN_00405ed0
// Original size: 160 bytes, actual code: 30 instructions
extern "C" void FUN_00447280(void);
extern "C" void FUN_004493e0(void);
extern "C" void FUN_0044b810(void);

extern "C" __declspec(naked) void FUN_00405ed0(void) {
    __asm {
        mov  edx,DWORD PTR [esi+0x3e0b50]
        mov  eax,ds:0x491c10
        push  edi
        call FUN_004493e0
        lea  edx,[esi+0x60]
        mov  ecx,0xf82bc
        xor  eax,eax
        mov  edi,edx
        rep stosd
        mov  DWORD PTR [esi+0x10],edx
        mov  WORD PTR [esi+0x3e07a6],0x5
        pop  edi
        ret
    }
}
