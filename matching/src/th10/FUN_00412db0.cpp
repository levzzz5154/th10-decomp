// 00412DB0: FUN_00412db0
// Original size: 192 bytes, actual code: 14 instructions

extern "C" __declspec(naked) void FUN_00412db0(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x30]
        xor  edx,edx
        test  cl,0x1
        jne loc_00412DD4
        or   ecx,0x1
        mov  DWORD PTR [eax+0x24],edx
        mov  DWORD PTR [eax+0x20],0xfff0bdc1
        mov  DWORD PTR [eax+0x28],edx
        mov  DWORD PTR [eax+0x2c],0x476f78
        mov  DWORD PTR [eax+0x30],ecx
    loc_00412DD4:
        mov  DWORD PTR [eax+0x24],edx
        mov  DWORD PTR [eax+0x28],edx
        mov  DWORD PTR [eax+0x20],0xffffffff
        ret
    }
}
