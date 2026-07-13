// 004050D0: FUN_004050d0
// Original size: 560 bytes, actual code: 14 instructions

extern "C" __declspec(naked) void FUN_004050d0(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x40]
        xor  edx,edx
        test  cl,0x1
        jne loc_004050F4
        or   ecx,0x1
        mov  DWORD PTR [eax+0x34],edx
        mov  DWORD PTR [eax+0x30],0xfff0bdc1
        mov  DWORD PTR [eax+0x38],edx
        mov  DWORD PTR [eax+0x3c],0x476f78
        mov  DWORD PTR [eax+0x40],ecx
    loc_004050F4:
        mov  DWORD PTR [eax+0x34],edx
        mov  DWORD PTR [eax+0x38],edx
        mov  DWORD PTR [eax+0x30],0xffffffff
        ret
    }
}
