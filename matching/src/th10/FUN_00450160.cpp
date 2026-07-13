// 00450160: FUN_00450160
// Original size: 48 bytes, actual code: 12 instructions

extern "C" __declspec(naked) void FUN_00450160(void) {
    __asm {
        add  eax,0x1030
        je loc_00450181
        jmp loc_00450170
        nop
    loc_00450170:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx+0x1010],ecx
        je loc_00450183
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00450170
    loc_00450181:
        xor  eax,eax
    loc_00450183:
        ret
    }
}
