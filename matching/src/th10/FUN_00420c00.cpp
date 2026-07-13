// 00420C00: FUN_00420c00
// Original size: 48 bytes, actual code: 13 instructions
extern "C" void FUN_0043e460(void);

extern "C" __declspec(naked) void FUN_00420c00(void) {
    __asm {
        test  BYTE PTR ds:0x491d78,0x10
        mov  edx,0x46df98
        push  0x0
        mov  eax,0x492590
        je loc_00420C1F
        push  0x4
        call FUN_0043e460
        xor  eax,eax
        ret
    loc_00420C1F:
        push  0x3
        call FUN_0043e460
        xor  eax,eax
        ret
    }
}
