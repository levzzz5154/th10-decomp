// 0043EC70: FUN_0043ec70
// Original size: 144 bytes, actual code: 40 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0043ec70(void) {
    __asm {
        lea  edx,[eax-0x2710]
        cmp  edx,0x9
        ja loc_0043ECD7
        jmp  DWORD PTR [edx*4+0x43ecd8]
        mov  eax,DWORD PTR [ecx+0x30c]
        ret
        mov  eax,DWORD PTR [ecx+0x310]
        ret
        mov  eax,DWORD PTR [ecx+0x314]
        ret
        mov  eax,DWORD PTR [ecx+0x318]
        ret
        fld  DWORD PTR [ecx+0x31c]
        jmp FUN_00463b2c
        fld  DWORD PTR [ecx+0x320]
        jmp FUN_00463b2c
        fld  DWORD PTR [ecx+0x324]
        jmp FUN_00463b2c
        fld  DWORD PTR [ecx+0x328]
        jmp FUN_00463b2c
        mov  eax,DWORD PTR [ecx+0x32c]
        ret
        mov  eax,DWORD PTR [ecx+0x330]
    loc_0043ECD7:
        ret
        sub  ah,0x43
        add  BYTE PTR [ecx-0x6fffbc14],cl
        in   al,dx
        inc  ebx
        add  BYTE PTR [edi-0x61ffbc14],dl
        in   al,dx
        inc  ebx
        add  BYTE PTR [ecx-0x4bffbc14],ch
        in   al,dx
        inc  ebx
        add  BYTE PTR [edi-0x35ffbc14],bh
        in   al,dx
        inc  ebx
        add  cl,dl
        in   al,dx
        inc  ebx
    }
}
