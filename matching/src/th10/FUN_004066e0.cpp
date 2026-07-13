// 004066E0: FUN_004066e0
// Original size: 174 bytes, actual code: 30 instructions
extern "C" void FUN_004451c0(void);
extern "C" void FUN_0044bc10(void);

extern "C" __declspec(naked) void FUN_004066e0(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR [eax+ecx*4+0x14]
        test  esi,esi
        je loc_0040675F
        nop
    loc_004066F0:
        fld  DWORD PTR [esi+0x3b4]
        fadd  DWORD PTR ds:0x470b4c
        fstp  DWORD PTR [esi+0x33c]
        fld  DWORD PTR [esi+0x3b8]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [esi+0x340]
        mov  edx,DWORD PTR [esi+0x3bc]
        mov  DWORD PTR [esi+0x344],edx
        test  DWORD PTR [esi+0x364],0x8000000
        je loc_00406747
        mov  eax,DWORD PTR [esi+0x3e4]
        push  0x3fc90fdb
        push  eax
        call FUN_0044bc10
        fstp  DWORD PTR [esi+0x34]
        or   DWORD PTR [esi+0x364],0x4
    loc_00406747:
        mov  ecx,DWORD PTR ds:0x491c10
        lea  eax,[esi+0x8]
        call FUN_004451c0
        mov  esi,DWORD PTR [esi+0x44c]
        test  esi,esi
        jne loc_004066F0
    loc_0040675F:
        mov  eax,0x1
        pop  esi
        ret
    }
}
