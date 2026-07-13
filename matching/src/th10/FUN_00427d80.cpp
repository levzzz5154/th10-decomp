// 00427D80: FUN_00427d80
// Original size: 272 bytes, actual code: 10 instructions

extern "C" __declspec(naked) void FUN_00427d80(void) {
    __asm {
        push  esi
        mov  esi,ecx
        mov  ecx,DWORD PTR [esi+0x4]
        mov  esi,DWORD PTR [esi]
        imul  ecx,edx
        imul  esi,edx
        mov  DWORD PTR [eax],esi
        mov  DWORD PTR [eax+0x4],ecx
        pop  esi
        ret
    }
}
