// 00412E70: FUN_00412e70
// Original size: 96 bytes, actual code: 18 instructions

extern "C" __declspec(naked) void FUN_00412e70(void) {
    __asm {
        mov  eax,0x99999999
        imul  DWORD PTR [esp+0x4]
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        mov  edx,DWORD PTR [ecx+0xc]
        add  edx,eax
        mov  eax,edx
        cmp  eax,0x1388
        mov  DWORD PTR [ecx+0xc],edx
        jge loc_00412E9B
        mov  DWORD PTR [ecx+0xc],0x1388
    loc_00412E9B:
        ret  0x4
    }
}
