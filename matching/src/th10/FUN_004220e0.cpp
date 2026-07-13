// 004220E0: FUN_004220e0
// Original size: 112 bytes, actual code: 24 instructions

extern "C" __declspec(naked) void FUN_004220e0(void) {
    __asm {
        mov  ecx,DWORD PTR [edx+0x20]
        xor  eax,eax
        and  ecx,0xfffffffe
        mov  DWORD PTR [edx+0x20],ecx
        mov  DWORD PTR [edx+0xb0],eax
        mov  DWORD PTR [edx+0x24],eax
        mov  DWORD PTR [edx+0xf8],eax
        mov  DWORD PTR [edx+0xf4],0x1
        mov  ecx,0x3e7
        mov  DWORD PTR [edx+0x2c],ecx
        mov  DWORD PTR [edx+0x104],ecx
        push  edi
        mov  DWORD PTR [edx+0x188],eax
        mov  DWORD PTR [edx+0xfc],eax
        mov  DWORD PTR [edx+0x1d0],eax
        mov  DWORD PTR [edx+0x1cc],0x1
        mov  ecx,0xb2
        mov  edi,edx
        rep stosd
        or   DWORD PTR [edx],0x2
        mov  DWORD PTR ds:0x477830,edx
        mov  eax,edx
        pop  edi
        ret
    }
}
