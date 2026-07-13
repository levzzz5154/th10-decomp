// 00401D20: FUN_00401d20
// Original size: 192 bytes, actual code: 16 instructions
extern "C" void FUN_004215a0(void);

extern "C" __declspec(naked) void FUN_00401d20(void) {
    __asm {
        mov  eax,ebx
        imul  eax,eax,0x118
        push  edi
        lea  edi,[eax+esi*1+0x154]
        mov  DWORD PTR [esi+0x384],edi
        call FUN_004215a0
        mov  edx,DWORD PTR [esi+0x384]
        mov  eax,DWORD PTR [esi+0x8]
        mov  ecx,DWORD PTR [eax]
        add  edx,0xcc
        push  edx
        push  eax
        call  DWORD PTR [ecx+0xbc]
        mov  DWORD PTR [esi+0x388],ebx
        pop  edi
        ret
    }
}
