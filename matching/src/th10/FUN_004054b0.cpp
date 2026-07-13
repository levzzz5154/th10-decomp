// 004054B0: FUN_004054b0
// Original size: 80 bytes, actual code: 20 instructions
extern "C" void FUN_0043e5a0(void);

extern "C" __declspec(naked) void FUN_004054b0(void) {
    __asm {
        mov  ecx,DWORD PTR [esi+0x9ec8]
        push  edi
        add  edx,0x8
        lea  eax,[esi+0x6a8c]
        call FUN_0043e5a0
        mov  eax,DWORD PTR [esp+0x8]
        cdq
        mov  ecx,0xa
        idiv  ecx
        mov  ecx,DWORD PTR [esi+0x9ec8]
        mov  edi,edx
        lea  edx,[eax+0x8]
        lea  eax,[esi+0x71e4]
        call FUN_0043e5a0
        mov  ecx,DWORD PTR [esi+0x9ec8]
        lea  edx,[edi+0x8]
        lea  eax,[esi+0x7590]
        call FUN_0043e5a0
        pop  edi
        ret  0x4
    }
}
