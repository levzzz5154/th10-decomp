// 0042C670: FUN_0042c670
// Original size: 96 bytes, actual code: 26 instructions
extern "C" void FUN_004489d0(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_0042c670(void) {
    __asm {
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        mov  eax,DWORD PTR [ebp+0x14]
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        mov  DWORD PTR [esp+0x10],eax
        call FUN_00449950
        mov  ecx,DWORD PTR [esp+0x10]
        mov  ebx,eax
        mov  edx,DWORD PTR [ebx+0x35c]
        push  edi
        or   edx,0x40000000
        push  ebx
        mov  DWORD PTR [ebx+0x20],0xf
        mov  DWORD PTR [ebx+0x35c],edx
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x10]
        call FUN_004489d0
        mov  ecx,DWORD PTR [esp+0x10]
        pop  esi
        mov  DWORD PTR [ebp+edi*4+0x2c4],ecx
        pop  ebp
        pop  ebx
        ret  0x4
    }
}
