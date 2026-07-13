// 00448DB0: FUN_00448db0
// Original size: 128 bytes, actual code: 31 instructions
extern "C" void FUN_0043e710(void);
extern "C" void FUN_004489d0(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_00448db0(void) {
    __asm {
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x10]
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00449950
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x35c]
        mov  ebx,DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esi+0x20],0x0
        or   eax,0x40000000
        mov  DWORD PTR [esi+0x35c],eax
        fld  DWORD PTR [edi]
        fadd  DWORD PTR ds:0x470b4c
        fstp  DWORD PTR [esi+0x340]
        fld  DWORD PTR [edi+0x4]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [esi+0x344]
        mov  eax,DWORD PTR [edi+0x8]
        mov  DWORD PTR [esi+0x348],eax
        mov  eax,esi
        call FUN_0043e710
        mov  edx,DWORD PTR ds:0x491c10
        mov  ebx,esi
        mov  eax,ebp
        call FUN_004489d0
        pop  esi
        pop  ebp
        pop  ebx
        ret  0xc
    }
}
