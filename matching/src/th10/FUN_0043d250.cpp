// 0043D250: FUN_0043d250
// Original size: 80 bytes, actual code: 34 instructions
extern "C" void _strncmp(void);

extern "C" __declspec(naked) void FUN_0043d250(void) {
    __asm {
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        mov  ebx,eax
        test  ebx,ebx
        push  esi
        mov  esi,ecx
        jbe loc_0043D286
        nop
    loc_0043D260:
        mov  eax,DWORD PTR [esi+0x4]
        push  0x4
        push  ebp
        push  esi
        mov  DWORD PTR [edi],eax
        call _strncmp
        add  esp,0xc
        test  eax,eax
        je loc_0043D28E
        mov  eax,DWORD PTR [edi]
        mov  ecx,0xfffffff8
        sub  ecx,eax
        add  ebx,ecx
        lea  esi,[esi+eax*1+0x8]
        jne loc_0043D260
    loc_0043D286:
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        ret  0x4
    loc_0043D28E:
        lea  eax,[esi+0x8]
        pop  esi
        pop  ebp
        pop  ebx
        ret  0x4
    }
}
