// 00418B80: FUN_00418b80
// Original size: 192 bytes, actual code: 21 instructions

extern "C" __declspec(naked) void FUN_00418b80(void) {
    __asm {
        mov  eax,0x66666667
        imul  DWORD PTR [esp+0x4]
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        mov  DWORD PTR [ecx+0xc],eax
        mov  eax,DWORD PTR [ecx+0x24]
        xor  edx,edx
        test  al,0x1
        jne loc_00418BB9
        or   eax,0x1
        mov  DWORD PTR [ecx+0x18],edx
        mov  DWORD PTR [ecx+0x14],0xfff0bdc1
        mov  DWORD PTR [ecx+0x1c],edx
        mov  DWORD PTR [ecx+0x20],0x476f78
        mov  DWORD PTR [ecx+0x24],eax
    loc_00418BB9:
        mov  DWORD PTR [ecx+0x18],edx
        mov  DWORD PTR [ecx+0x1c],edx
        mov  DWORD PTR [ecx+0x14],0xffffffff
        ret  0x4
    }
}
