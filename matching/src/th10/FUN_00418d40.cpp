// 00418D40: FUN_00418d40
// Original size: 240 bytes, actual code: 59 instructions

extern "C" __declspec(naked) void FUN_00418d40(void) {
    __asm {
        xor  eax,eax
        push  edi
        mov  ecx,0x6a
        mov  edi,edx
        rep stosd
        or   DWORD PTR [edx],0x2
        mov  DWORD PTR [edx+0x18],edx
        mov  DWORD PTR [edx+0x24],edx
        xor  eax,eax
        mov  DWORD PTR [edx+0x1c],eax
        mov  DWORD PTR [edx+0x20],eax
        mov  DWORD PTR [edx+0x28],eax
        mov  DWORD PTR [edx+0x2c],eax
        mov  DWORD PTR [edx+0x30],edx
        mov  DWORD PTR [edx+0x34],eax
        mov  DWORD PTR [edx+0x38],eax
        mov  DWORD PTR [edx+0x3c],edx
        mov  DWORD PTR [edx+0x40],eax
        mov  DWORD PTR [edx+0x44],eax
        mov  DWORD PTR [edx+0x48],edx
        mov  DWORD PTR [edx+0x4c],eax
        mov  DWORD PTR [edx+0x50],eax
        mov  DWORD PTR [edx+0x54],edx
        mov  DWORD PTR [edx+0x58],eax
        mov  DWORD PTR [edx+0x5c],eax
        mov  DWORD PTR [edx+0x60],edx
        mov  DWORD PTR [edx+0x64],eax
        mov  DWORD PTR [edx+0x68],eax
        mov  DWORD PTR [edx+0x6c],edx
        mov  DWORD PTR [edx+0x70],eax
        mov  DWORD PTR [edx+0x74],eax
        mov  DWORD PTR [edx+0x78],edx
        mov  DWORD PTR [edx+0x84],edx
        mov  DWORD PTR [edx+0x7c],eax
        mov  DWORD PTR [edx+0x80],eax
        mov  DWORD PTR [edx+0x88],eax
        mov  DWORD PTR [edx+0x8c],eax
        mov  DWORD PTR [edx+0x90],edx
        mov  DWORD PTR [edx+0x94],eax
        mov  DWORD PTR [edx+0x98],eax
        mov  DWORD PTR [edx+0x9c],edx
        mov  DWORD PTR [edx+0xa0],eax
        mov  DWORD PTR [edx+0xa4],eax
        mov  DWORD PTR [edx+0xa8],edx
        mov  DWORD PTR [edx+0xac],eax
        mov  DWORD PTR [edx+0xb0],eax
        mov  DWORD PTR [edx+0xb4],edx
        mov  DWORD PTR [edx+0xb8],eax
        mov  DWORD PTR [edx+0xbc],eax
        mov  DWORD PTR [edx+0xc0],edx
        mov  DWORD PTR [edx+0xc4],eax
        mov  DWORD PTR [edx+0xc8],eax
        mov  DWORD PTR [edx+0xcc],edx
        mov  DWORD PTR [edx+0xd0],eax
        mov  DWORD PTR [edx+0xd4],eax
        mov  DWORD PTR ds:0x477814,edx
        mov  eax,edx
        pop  edi
        ret
    }
}
