// 0043DAB0: FUN_0043dab0
// Original size: 176 bytes, actual code: 54 instructions
extern "C" void FUN_0044d550(void);

extern "C" __declspec(naked) void FUN_0043dab0(void) {
    __asm {
        push  edi
        mov  edi,DWORD PTR [esi+0x5208]
        test  edi,edi
        je loc_0043DB5E
        call FUN_0044d550
        mov  eax,DWORD PTR [esi+0x618]
        test  eax,eax
        je loc_0043DB44
        mov  eax,DWORD PTR [esi+0x614]
        mov  edi,DWORD PTR ds:0x466210
        push  ebx
        push  0x0
        push  0x0
        push  0x12
        push  eax
        call  edi
        mov  ecx,DWORD PTR [esi+0x618]
        mov  ebx,DWORD PTR ds:0x46611c
        push  0x100
        push  ecx
        call  ebx
        test  eax,eax
        je loc_0043DB21
        nop
    loc_0043DB00:
        mov  edx,DWORD PTR [esi+0x614]
        push  0x0
        push  0x0
        push  0x12
        push  edx
        call  edi
        mov  eax,DWORD PTR [esi+0x618]
        push  0x100
        push  eax
        call  ebx
        test  eax,eax
        jne loc_0043DB00
    loc_0043DB21:
        mov  ecx,DWORD PTR [esi+0x618]
        mov  edi,DWORD PTR ds:0x4660cc
        push  ecx
        call  edi
        mov  edx,DWORD PTR [esi+0x520c]
        push  edx
        call  edi
        mov  DWORD PTR [esi+0x618],0x0
        pop  ebx
    loc_0043DB44:
        mov  ecx,DWORD PTR [esi+0x5208]
        test  ecx,ecx
        je loc_0043DB5E
        mov  eax,DWORD PTR [ecx]
        push  0x1
        call  DWORD PTR [eax]
        mov  DWORD PTR [esi+0x5208],0x0
    loc_0043DB5E:
        pop  edi
        ret
    }
}
