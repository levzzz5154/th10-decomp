// 004423C0: FUN_004423c0
// Original size: 32 bytes, actual code: 8 instructions

extern "C" __declspec(naked) void FUN_004423c0(void) {
    __asm {
        movzx eax,al
        movzx ecx,cl
        imul  eax,ecx
        shr  eax,0x7
        cmp  eax,0x100
        jb loc_004423D8
        mov  eax,0xff
    loc_004423D8:
        ret
    }
}
