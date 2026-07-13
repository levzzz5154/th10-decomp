// 00448D50: FUN_00448d50
// Original size: 96 bytes, actual code: 28 instructions
extern "C" void FUN_0043e710(void);
extern "C" void FUN_004489d0(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_00448d50(void) {
    __asm {
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x10]
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00449950
        mov  ebx,DWORD PTR [esp+0x18]
        mov  esi,eax
        or   DWORD PTR [esi+0x35c],0x40000000
        mov  DWORD PTR [esi+0x20],0x0
        mov  ecx,DWORD PTR [edi]
        lea  eax,[esi+0x340]
        mov  DWORD PTR [eax],ecx
        mov  edx,DWORD PTR [edi+0x4]
        mov  DWORD PTR [eax+0x4],edx
        mov  ecx,DWORD PTR [edi+0x8]
        mov  DWORD PTR [eax+0x8],ecx
        mov  ecx,DWORD PTR [esp+0x10]
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
