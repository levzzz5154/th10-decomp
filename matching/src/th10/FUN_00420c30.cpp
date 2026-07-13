// 00420C30: FUN_00420c30
// Original size: 160 bytes, actual code: 23 instructions
extern "C" void FUN_0043e460(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00420c30(void) {
    __asm {
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR ds:0x476f78
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_00420C4B
        fld  DWORD PTR [esp+0x4]
        jmp loc_00420C68
    loc_00420C4B:
        fld  DWORD PTR ds:0x476f78
        fcomp DWORD PTR ds:0x470afc
        fld  DWORD PTR [esp+0x4]
        fnstsw ax
        test  ah,0x41
        je loc_00420C68
        fdiv  DWORD PTR ds:0x476f78
    loc_00420C68:
        call FUN_00463b2c
        push  eax
        push  0x5
        mov  edx,0x46d275
        mov  eax,0x492590
        call FUN_0043e460
        xor  eax,eax
        ret  0x4
    }
}
