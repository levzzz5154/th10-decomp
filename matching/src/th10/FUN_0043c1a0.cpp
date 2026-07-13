// 0043C1A0: FUN_0043c1a0
// Original size: 288 bytes, actual code: 33 instructions
extern "C" void FUN_0043bda0(void);
extern "C" void FUN_00442f50(void);

extern "C" __declspec(naked) void FUN_0043c1a0(void) {
    __asm {
        sub  esp,0x10
        push  ebx
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        push  edi
        mov  edi,ecx
        mov  DWORD PTR [esp+0xc],0x0
        mov  DWORD PTR [esp+0x10],0x0
        mov  DWORD PTR [esp+0x14],0x44200000
        mov  DWORD PTR [esp+0x18],0x43f00000
        call FUN_00442f50
        xor  eax,eax
        mov  ds:0x491cf4,eax
        mov  ds:0x491cf8,eax
        mov  eax,ds:0x491c30
        push  0x491cf4
        mov  DWORD PTR ds:0x491cfc,0x280
        mov  DWORD PTR ds:0x491d00,0x1e0
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0xbc]
        mov  ebx,DWORD PTR [edi+0x18]
        mov  eax,DWORD PTR [edi+0x20]
        shl  ebx,0x18
        or   ebx,eax
        lea  edi,[esp+0xc]
        call FUN_0043bda0
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebx
        add  esp,0x10
        ret
    }
}
