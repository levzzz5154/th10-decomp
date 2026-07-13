// 00426610: FUN_00426610
// Original size: 80 bytes, actual code: 23 instructions

extern "C" __declspec(naked) void FUN_00426610(void) {
    __asm {
        fld  DWORD PTR [eax]
        fsub  DWORD PTR [ecx+0x3c0]
        fld  DWORD PTR [eax+0x4]
        fsub  DWORD PTR [ecx+0x3c4]
        fld  DWORD PTR ds:0x470b04
        fld  st(1)
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0042664E
        fld  DWORD PTR ds:0x470b04
        fld  st(2)
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0042664E
        fstp  st(0)
        fstp  st(0)
        fld  DWORD PTR ds:0x470b94
        ret
    loc_0042664E:
        fxch  st(1)
        fpatan
        ret
    }
}
