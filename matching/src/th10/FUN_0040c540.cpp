// 0040C540: FUN_0040c540
// Original size: 416 bytes, actual code: 22 instructions
extern "C" void FUN_00448d50(void);

extern "C" __declspec(naked) void FUN_0040c540(void) {
    __asm {
        sub  esp,0xc
        mov  eax,DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [esp],eax
        mov  eax,DWORD PTR [esi+0x89a4]
        test  eax,eax
        mov  DWORD PTR [esp+0x4],ecx
        mov  DWORD PTR [esp+0x8],0x0
        jne loc_0040C585
        mov  eax,DWORD PTR [esi+0x8994]
        push  edi
        push  0x6
        lea  edx,[esp+0x18]
        push  edx
        push  eax
        lea  edi,[esp+0x10]
        call FUN_00448d50
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [esi+0x89a4],eax
        pop  edi
    loc_0040C585:
        add  esp,0xc
        ret  0x8
    }
}
