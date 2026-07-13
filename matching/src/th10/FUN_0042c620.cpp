// 0042C620: FUN_0042c620
// Original size: 80 bytes, actual code: 15 instructions

extern "C" __declspec(naked) void FUN_0042c620(void) {
    __asm {
        mov  DWORD PTR [eax+0x20],ecx
        mov  ecx,DWORD PTR [eax+0x2c0]
        xor  edx,edx
        test  cl,0x1
        jne loc_0042C659
        or   ecx,0x1
        mov  DWORD PTR [eax+0x2b4],edx
        mov  DWORD PTR [eax+0x2b0],0xfff0bdc1
        mov  DWORD PTR [eax+0x2b8],edx
        mov  DWORD PTR [eax+0x2bc],0x476f78
        mov  DWORD PTR [eax+0x2c0],ecx
    loc_0042C659:
        mov  DWORD PTR [eax+0x2b4],edx
        mov  DWORD PTR [eax+0x2b8],edx
        mov  DWORD PTR [eax+0x2b0],0xffffffff
        ret
    }
}
