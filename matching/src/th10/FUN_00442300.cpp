// 00442300: FUN_00442300
// Original size: 192 bytes, actual code: 23 instructions

extern "C" __declspec(naked) void FUN_00442300(void) {
    __asm {
        mov  DWORD PTR [eax+0x12c],ecx
        movzx ecx,BYTE PTR [esp+0x4]
        mov  DWORD PTR [eax+0x130],ecx
        movzx ecx,BYTE PTR [esp+0x8]
        mov  DWORD PTR [eax+0x108],ecx
        movzx ecx,BYTE PTR [esp+0xc]
        xor  edx,edx
        mov  DWORD PTR [eax+0x110],edx
        mov  DWORD PTR [eax+0x114],edx
        mov  DWORD PTR [eax+0x10c],ecx
        mov  ecx,DWORD PTR [eax+0x128]
        test  cl,0x1
        jne loc_00442369
        or   ecx,0x1
        mov  DWORD PTR [eax+0x11c],edx
        mov  DWORD PTR [eax+0x118],0xfff0bdc1
        mov  DWORD PTR [eax+0x120],edx
        mov  DWORD PTR [eax+0x124],0x476f78
        mov  DWORD PTR [eax+0x128],ecx
    loc_00442369:
        mov  DWORD PTR [eax+0x11c],edx
        mov  DWORD PTR [eax+0x120],edx
        mov  DWORD PTR [eax+0x118],0xffffffff
        ret  0xc
    }
}
