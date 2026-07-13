// 00408660: FUN_00408660
// Original size: 80 bytes, actual code: 22 instructions

extern "C" __declspec(naked) void FUN_00408660(void) {
    __asm {
        fld  DWORD PTR [esp+0x4]
        fsub  DWORD PTR [esp+0x8]
        fcom  DWORD PTR ds:0x470b18
        fnstsw ax
        test  ah,0x41
        jne loc_00408688
        fstp  st(0)
        fld  DWORD PTR [esp+0x8]
        fadd  DWORD PTR ds:0x470b14
        fsubr DWORD PTR [esp+0x4]
        ret  0x8
    loc_00408688:
        fld  DWORD PTR [esp+0x8]
        fsub  DWORD PTR [esp+0x4]
        fcomp DWORD PTR ds:0x470b18
        fnstsw ax
        test  ah,0x41
        jne loc_004086AD
        fstp  st(0)
        fld  DWORD PTR [esp+0x8]
        fsub  DWORD PTR ds:0x470b14
        fsubr DWORD PTR [esp+0x4]
    loc_004086AD:
        ret  0x8
    }
}
