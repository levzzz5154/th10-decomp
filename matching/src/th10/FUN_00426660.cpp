// 00426660: FUN_00426660
// Original size: 80 bytes, actual code: 23 instructions

extern "C" __declspec(naked) void FUN_00426660(void) {
    __asm {
        fld  DWORD PTR [ecx+0x3c0]
        fsub  DWORD PTR [eax]
        fld  DWORD PTR [ecx+0x3c4]
        fsub  DWORD PTR [eax+0x4]
        fld  DWORD PTR ds:0x470b04
        fld  st(1)
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0042669E
        fld  DWORD PTR ds:0x470b04
        fld  st(2)
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0042669E
        fstp  st(0)
        fstp  st(0)
        fld  DWORD PTR ds:0x470b94
        ret
    loc_0042669E:
        fxch  st(1)
        fpatan
        ret
    }
}
