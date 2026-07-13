// 00428E10: FUN_00428e10
// Original size: 336 bytes, actual code: 16 instructions

extern "C" __declspec(naked) void FUN_00428e10(void) {
    __asm {
        mov  edx,DWORD PTR [ecx]
        mov  DWORD PTR [eax+0x3cc],edx
        mov  ecx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [eax+0x3d0],ecx
        fild  DWORD PTR [eax+0x3cc]
        mov  ecx,0x1
        fmul  DWORD PTR ds:0x470b00
        fstp  DWORD PTR [eax+0x3c0]
        fild  DWORD PTR [eax+0x3d0]
        fmul  DWORD PTR ds:0x470b00
        fstp  DWORD PTR [eax+0x3c4]
        mov  DWORD PTR [eax+0x332c],ecx
        mov  DWORD PTR [eax+0x33c4],ecx
        mov  DWORD PTR [eax+0x345c],ecx
        mov  DWORD PTR [eax+0x34f4],ecx
        ret
    }
}
