// 00405DE0: FUN_00405de0
// Original size: 64 bytes, actual code: 11 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00405de0(void) {
    __asm {
        push  esi
        mov  esi,ecx
        mov  eax,DWORD PTR [esi+0x360]
        test  eax,eax
        je loc_00405DF6
        push  eax
        call _free
        add  esp,0x4
    loc_00405DF6:
        mov  DWORD PTR [esi+0x360],0x0
        pop  esi
        ret
    }
}
