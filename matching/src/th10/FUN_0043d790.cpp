// 0043D790: FUN_0043d790
// Original size: 64 bytes, actual code: 20 instructions
extern "C" void FUN_0043d2a0(void);
extern "C" void FUN_0044dca0(void);

extern "C" __declspec(naked) void FUN_0043d790(void) {
    __asm {
        push  esi
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x5208]
        test  eax,eax
        jne loc_0043D7A2
        or   eax,0xffffffff
        pop  esi
        ret
    loc_0043D7A2:
        push  esi
        call FUN_0043d2a0
        mov  ecx,eax
        mov  eax,DWORD PTR [esi+0x1f84]
        imul  ecx,ecx,0x34
        add  ecx,eax
        mov  eax,DWORD PTR [esi+0x5208]
        mov  esi,DWORD PTR [eax+0xc]
        call FUN_0044dca0
        xor  eax,eax
        pop  esi
        ret
    }
}
