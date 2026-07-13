// 0041BE80: FUN_0041be80
// Original size: 48 bytes, actual code: 14 instructions

extern "C" __declspec(naked) void FUN_0041be80(void) {
    __asm {
        mov  eax,0x66666667
        imul  DWORD PTR [esp+0x4]
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        mov  edx,DWORD PTR [ecx+0xc]
        add  edx,eax
        mov  eax,edx
        cmp  eax,0x1869f
        mov  DWORD PTR [ecx+0xc],edx
        jle loc_0041BEAB
        mov  DWORD PTR [ecx+0xc],0x1869f
    loc_0041BEAB:
        ret  0x4
    }
}
