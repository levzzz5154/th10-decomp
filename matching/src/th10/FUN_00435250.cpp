// 00435250: FUN_00435250
// Original size: 208 bytes, actual code: 11 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00435250(void) {
    __asm {
        push  esi
        mov  esi,ecx
        mov  eax,DWORD PTR [esi]
        test  eax,eax
        je loc_00435268
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],0x0
    loc_00435268:
        pop  esi
        ret
    }
}
