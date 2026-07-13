// 00418D00: FUN_00418d00
// Original size: 64 bytes, actual code: 16 instructions

extern "C" __declspec(naked) void FUN_00418d00(void) {
    __asm {
        xor  eax,eax
        push  edi
        mov  ecx,0x22
        mov  edi,edx
        rep stosd
        mov  DWORD PTR [edx+0x10],eax
        mov  DWORD PTR [edx+0x14],eax
        mov  DWORD PTR [edx+0xc],edx
        or   eax,0xffffffff
        mov  DWORD PTR [edx+0x84],eax
        mov  DWORD PTR [edx+0x70],eax
        mov  DWORD PTR [edx+0x6c],0x12c
        mov  DWORD PTR [edx+0x7c],0x3f800000
        mov  eax,edx
        pop  edi
        ret
    }
}
