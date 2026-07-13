// 004045B0: FUN_004045b0
// Original size: 96 bytes, actual code: 15 instructions

extern "C" __declspec(naked) void FUN_004045b0(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x2a2c]
        test  cl,0x1
        jne loc_004045E6
        xor  edx,edx
        or   ecx,0x1
        mov  DWORD PTR [eax+0x2a20],edx
        mov  DWORD PTR [eax+0x2a1c],0xfff0bdc1
        mov  DWORD PTR [eax+0x2a24],edx
        mov  DWORD PTR [eax+0x2a28],0x476f78
        mov  DWORD PTR [eax+0x2a2c],ecx
    loc_004045E6:
        mov  DWORD PTR [eax+0x2a20],0x3c
        mov  DWORD PTR [eax+0x2a24],0x42700000
        mov  DWORD PTR [eax+0x2a1c],0x3b
        or   DWORD PTR [eax+0x2a18],0x4
        ret
    }
}
