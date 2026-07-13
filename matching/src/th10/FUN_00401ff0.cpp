// 00401FF0: FUN_00401ff0
// Original size: 96 bytes, actual code: 11 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00401ff0(void) {
    __asm {
        push  esi
        mov  esi,ecx
        mov  eax,DWORD PTR [esi+0x358]
        test  eax,eax
        je loc_00402006
        push  eax
        call _free
        add  esp,0x4
    loc_00402006:
        mov  DWORD PTR [esi+0x358],0x0
        pop  esi
        ret
    }
}
