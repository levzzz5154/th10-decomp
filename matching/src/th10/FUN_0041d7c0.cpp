// 0041D7C0: FUN_0041d7c0
// Original size: 192 bytes, actual code: 49 instructions
extern "C" void FUN_004451c0(void);
extern "C" void FUN_0044bc10(void);

extern "C" __declspec(naked) void FUN_0041d7c0(void) {
    __asm {
        push  esi
        mov  esi,ecx
        fld  DWORD PTR [esi+0x24]
        push  edi
        fadd  DWORD PTR ds:0x470b4c
        push  0x3fc90fdb
        lea  edi,[esi+0x600]
        fstp  DWORD PTR [esi+0x934]
        fld  DWORD PTR [esi+0x28]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [esi+0x938]
        mov  eax,DWORD PTR [esi+0x2c]
        mov  DWORD PTR [esi+0x93c],eax
        mov  ecx,DWORD PTR [esi+0x3c]
        push  ecx
        call FUN_0044bc10
        fstp  DWORD PTR [edi+0x2c]
        mov  eax,DWORD PTR [edi+0x35c]
        mov  ecx,DWORD PTR ds:0x491c10
        or   eax,0x4
        mov  DWORD PTR [edi+0x35c],eax
        mov  eax,edi
        call FUN_004451c0
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [esi+0x4c]
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0041D868
        fld  DWORD PTR [esi+0x24]
        mov  ecx,DWORD PTR ds:0x491c10
        fadd  DWORD PTR ds:0x470b4c
        lea  eax,[esi+0x9ac]
        fstp  DWORD PTR [esi+0xce0]
        fld  DWORD PTR [esi+0x28]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [esi+0xce4]
        mov  edx,DWORD PTR [esi+0x2c]
        mov  DWORD PTR [esi+0xce8],edx
        call FUN_004451c0
    loc_0041D868:
        pop  edi
        xor  eax,eax
        pop  esi
        ret
    }
}
