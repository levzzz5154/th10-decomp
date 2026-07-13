// 00405300: FUN_00405300
// Original size: 272 bytes, actual code: 16 instructions
extern "C" void FUN_00421480(void);

extern "C" __declspec(naked) void FUN_00405300(void) {
    __asm {
        mov  eax,ebx
        imul  eax,eax,0x118
        push  edi
        lea  edi,[eax+esi*1+0x154]
        mov  DWORD PTR [esi+0x384],edi
        call FUN_00421480
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
