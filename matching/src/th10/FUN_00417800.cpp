// 00417800: FUN_00417800
// Original size: 112 bytes, actual code: 17 instructions

extern "C" __declspec(naked) void FUN_00417800(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x50]
        xor  edx,edx
        test  cl,0x1
        jne loc_00417824
        or   ecx,0x1
        mov  DWORD PTR [eax+0x44],edx
        mov  DWORD PTR [eax+0x40],0xfff0bdc1
        mov  DWORD PTR [eax+0x48],edx
        mov  DWORD PTR [eax+0x4c],0x476f78
        mov  DWORD PTR [eax+0x50],ecx
    loc_00417824:
        mov  DWORD PTR [eax+0x44],edx
        mov  DWORD PTR [eax+0x48],edx
        mov  DWORD PTR [eax+0x40],0xffffffff
        mov  DWORD PTR [eax+0x58],edx
        mov  DWORD PTR [eax+0x5c],edx
        xor  eax,eax
        ret
    }
}
