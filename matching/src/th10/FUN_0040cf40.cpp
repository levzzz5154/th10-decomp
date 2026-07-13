// 0040CF40: FUN_0040cf40
// Original size: 32 bytes, actual code: 9 instructions

extern "C" __declspec(naked) void FUN_0040cf40(void) {
    __asm {
        push  edi
        xor  eax,eax
        mov  ecx,0x7e
        mov  edi,edx
        rep stosd
        mov  DWORD PTR [edx+0x2c],0x41000000
        mov  eax,edx
        pop  edi
        ret
    }
}
