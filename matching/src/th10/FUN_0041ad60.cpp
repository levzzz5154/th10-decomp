// 0041AD60: FUN_0041ad60
// Original size: 48 bytes, actual code: 11 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0041ad60(void) {
    __asm {
        push  esi
        mov  esi,ecx
        mov  eax,DWORD PTR [esi+0x358]
        test  eax,eax
        je loc_0041AD76
        push  eax
        call _free
        add  esp,0x4
    loc_0041AD76:
        mov  DWORD PTR [esi+0x358],0x0
        pop  esi
        ret
    }
}
