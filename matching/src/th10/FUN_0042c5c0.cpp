// 0042C5C0: FUN_0042c5c0
// Original size: 96 bytes, actual code: 16 instructions

extern "C" __declspec(naked) void FUN_0042c5c0(void) {
    __asm {
        xor  edx,edx
        mov  DWORD PTR [eax+0x1c],ecx
        mov  DWORD PTR [eax+0x20],edx
        mov  ecx,DWORD PTR [eax+0x2c0]
        test  cl,0x1
        jne loc_0042C5FC
        or   ecx,0x1
        mov  DWORD PTR [eax+0x2b4],edx
        mov  DWORD PTR [eax+0x2b0],0xfff0bdc1
        mov  DWORD PTR [eax+0x2b8],edx
        mov  DWORD PTR [eax+0x2bc],0x476f78
        mov  DWORD PTR [eax+0x2c0],ecx
    loc_0042C5FC:
        mov  DWORD PTR [eax+0x2b4],edx
        mov  DWORD PTR [eax+0x2b8],edx
        mov  DWORD PTR [eax+0x2b0],0xffffffff
        ret
    }
}
