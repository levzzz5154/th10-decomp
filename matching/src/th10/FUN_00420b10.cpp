// 00420B10: FUN_00420b10
// Original size: 240 bytes, actual code: 18 instructions
extern "C" void FUN_0043e460(void);

extern "C" __declspec(naked) void FUN_00420b10(void) {
    __asm {
        test  BYTE PTR ds:0x491d78,0x10
        je loc_00420B2C
        push  0x0
        push  0x4
        mov  edx,0x46df98
        mov  eax,0x492590
        call FUN_0043e460
    loc_00420B2C:
        mov  eax,DWORD PTR [esp+0x4]
        push  eax
        push  0x2
        mov  edx,0x46df98
        mov  eax,0x492590
        call FUN_0043e460
        mov  ecx,DWORD PTR ds:0x47783c
        mov  edx,DWORD PTR [esp+0x8]
        mov  BYTE PTR [ecx+edx*1+0x1d892],0x1
        xor  eax,eax
        ret  0x8
    }
}
