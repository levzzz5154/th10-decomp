// 0043A730: FUN_0043a730
// Original size: 480 bytes, actual code: 13 instructions

extern "C" __declspec(naked) void FUN_0043a730(void) {
    __asm {
        xor  eax,eax
    loc_0043A732:
        mov  ecx,DWORD PTR [esi]
        mov  dl,BYTE PTR [ecx]
        inc  ecx
        mov  DWORD PTR [esi],ecx
        xor  ecx,ecx
        mov  cl,dl
        shl  eax,0x7
        and  ecx,0x7f
        add  eax,ecx
        test  dl,dl
        js loc_0043A732
        ret
    }
}
