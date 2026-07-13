// 0042C920: FUN_0042c920
// Original size: 384 bytes, actual code: 43 instructions

extern "C" __declspec(naked) void FUN_0042c920(void) {
    __asm {
        mov  DWORD PTR [edx],0x46ecf0
        xor  eax,eax
        mov  DWORD PTR [edx+0xb0],eax
        mov  DWORD PTR [edx+0x24],eax
        mov  DWORD PTR [edx+0xf8],eax
        push  esi
        mov  esi,0x1
        mov  DWORD PTR [edx+0xf4],esi
        mov  ecx,0x3e7
        mov  DWORD PTR [edx+0x2c],ecx
        mov  DWORD PTR [edx+0x188],eax
        mov  DWORD PTR [edx+0xfc],eax
        mov  DWORD PTR [edx+0x1d0],eax
        mov  DWORD PTR [edx+0x1cc],esi
        mov  DWORD PTR [edx+0x104],ecx
        mov  DWORD PTR [edx+0x260],eax
        mov  DWORD PTR [edx+0x1d4],eax
        mov  DWORD PTR [edx+0x2a8],eax
        mov  DWORD PTR [edx+0x2a4],esi
        mov  DWORD PTR [edx+0x1dc],ecx
        push  edi
        and  DWORD PTR [edx+0x2c0],0xfffffffe
        mov  DWORD PTR [edx+0x5980],eax
        mov  DWORD PTR [edx+0x58f4],eax
        mov  DWORD PTR [edx+0x59c8],eax
        mov  DWORD PTR [edx+0x58fc],ecx
        mov  DWORD PTR [edx+0x59c4],esi
        mov  DWORD PTR [edx+0x5ab4],eax
        mov  DWORD PTR [edx+0x5ab8],eax
        mov  DWORD PTR [edx+0x5abc],eax
        mov  DWORD PTR [edx+0x5ac0],eax
        mov  DWORD PTR [edx+0x5ab0],0x4703e4
        mov  ecx,0x16b3
        mov  edi,edx
        rep stosd
        mov  eax,DWORD PTR [edx+0x4]
        or   eax,0x2
        pop  edi
        mov  DWORD PTR [edx+0x4],eax
        mov  DWORD PTR ds:0x47784c,edx
        mov  eax,edx
        pop  esi
        ret
    }
}
