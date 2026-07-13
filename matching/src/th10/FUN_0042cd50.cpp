// 0042CD50: FUN_0042cd50
// Original size: 96 bytes, actual code: 31 instructions
extern "C" void FUN_0042c920(void);
extern "C" void FUN_0044c150(void);
extern "C" void operator_new(void);
extern "C" void __beginthreadex(void);

extern "C" __declspec(naked) void FUN_0042cd50(void) {
    __asm {
        push  esi
        push  edi
        push  0x5acc
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_0042CD6E
        mov  edx,eax
        call FUN_0042c920
        mov  edi,eax
        jmp loc_0042CD70
    loc_0042CD6E:
        xor  edi,edi
    loc_0042CD70:
        lea  esi,[edi+0x5ab0]
        call FUN_0044c150
        lea  eax,[esi+0x8]
        push  eax
        push  0x0
        push  edi
        push  0x42c9f0
        push  0x0
        push  0x0
        mov  DWORD PTR [esi+0x18],0x42c9f0
        mov  DWORD PTR [esi+0x10],0x1
        mov  DWORD PTR [esi+0xc],0x0
        call __beginthreadex
        add  esp,0x18
        mov  DWORD PTR [esi+0x4],eax
        mov  eax,edi
        pop  edi
        pop  esi
        ret
    }
}
