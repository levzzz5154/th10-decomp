// 0043C8B0: FUN_0043c8b0
// Original size: 192 bytes, actual code: 33 instructions
extern "C" void FUN_0043c970(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_0043c8b0(void) {
    __asm {
        push  esi
        push  0x44
        call operator_new
        mov  esi,eax
        add  esp,0x4
        xor  eax,eax
        test  esi,esi
        je loc_0043C8FE
        mov  ecx,DWORD PTR [esi+0x40]
        mov  edx,DWORD PTR [esp+0x10]
        push  edi
        and  ecx,0xfffffffe
        mov  DWORD PTR [esi+0x40],ecx
        mov  ecx,0x11
        mov  edi,esi
        rep stosd
        mov  eax,DWORD PTR [esi]
        mov  ecx,DWORD PTR [esp+0x18]
        or   eax,0x2
        pop  edi
        mov  DWORD PTR [esi],eax
        mov  eax,DWORD PTR [esp+0x18]
        push  eax
        mov  eax,DWORD PTR [esp+0x10]
        push  ecx
        mov  ecx,DWORD PTR [esp+0x10]
        push  edx
        push  eax
        push  ecx
        call FUN_0043c970
        mov  eax,esi
    loc_0043C8FE:
        pop  esi
        ret  0x14
    }
}
