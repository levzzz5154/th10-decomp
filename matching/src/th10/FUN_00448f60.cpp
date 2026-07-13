// 00448F60: FUN_00448f60
// Original size: 304 bytes, actual code: 21 instructions
extern "C" void FUN_00448ac0(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_00448f60(void) {
    __asm {
        push  ebx
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00449950
        mov  ecx,DWORD PTR [esp+0x10]
        mov  ebx,eax
        mov  esi,DWORD PTR [ebx+0x35c]
        mov  eax,DWORD PTR [esp+0x14]
        push  ecx
        mov  ecx,DWORD PTR [esp+0x10]
        or   esi,0x40000000
        push  ebx
        mov  DWORD PTR [ebx+0x20],eax
        mov  DWORD PTR [ebx+0x35c],esi
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        mov  eax,edi
        call FUN_00448ac0
        pop  esi
        pop  ebx
        ret  0xc
    }
}
