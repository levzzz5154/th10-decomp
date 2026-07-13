// 0044C1C0: FUN_0044c1c0
// Original size: 224 bytes, actual code: 19 instructions
extern "C" void FUN_0044c150(void);
extern "C" void __beginthreadex(void);

extern "C" __declspec(naked) void FUN_0044c1c0(void) {
    __asm {
        push  esi
        mov  esi,eax
        call FUN_0044c150
        mov  ecx,DWORD PTR [esp+0x8]
        lea  eax,[esi+0x8]
        push  eax
        push  0x0
        push  ecx
        push  edi
        push  0x0
        push  0x0
        mov  DWORD PTR [esi+0x18],edi
        mov  DWORD PTR [esi+0x10],0x1
        mov  DWORD PTR [esi+0xc],0x0
        call __beginthreadex
        add  esp,0x18
        mov  DWORD PTR [esi+0x4],eax
        pop  esi
        ret  0x4
    }
}
