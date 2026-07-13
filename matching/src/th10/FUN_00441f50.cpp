// 00441F50: FUN_00441f50
// Original size: 256 bytes, actual code: 21 instructions

extern "C" __declspec(naked) void FUN_00441f50(void) {
    __asm {
        movzx edx,dl
        mov  DWORD PTR [eax+0x230],edx
        movzx edx,BYTE PTR [esp+0x8]
        mov  DWORD PTR [eax+0x22c],ecx
        movzx ecx,BYTE PTR [esp+0x4]
        mov  DWORD PTR [eax+0x20c],edx
        mov  DWORD PTR [eax+0x208],ecx
        mov  ecx,DWORD PTR [eax+0x228]
        xor  edx,edx
        test  cl,0x1
        jne loc_00441FAB
        or   ecx,0x1
        mov  DWORD PTR [eax+0x21c],edx
        mov  DWORD PTR [eax+0x218],0xfff0bdc1
        mov  DWORD PTR [eax+0x220],edx
        mov  DWORD PTR [eax+0x224],0x476f78
        mov  DWORD PTR [eax+0x228],ecx
    loc_00441FAB:
        mov  DWORD PTR [eax+0x21c],edx
        mov  DWORD PTR [eax+0x220],edx
        mov  DWORD PTR [eax+0x218],0xffffffff
        ret  0x8
    }
}
