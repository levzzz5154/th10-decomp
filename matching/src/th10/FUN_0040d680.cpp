// 0040D680: FUN_0040d680
// Original size: 48 bytes, actual code: 9 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0040d680(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x8c]
        test  eax,eax
        mov  DWORD PTR [esi],0x46d0f0
        je loc_0040D6A3
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0x8c],0x0
    loc_0040D6A3:
        ret
    }
}
