// 0044C100: FUN_0044c100
// Original size: 48 bytes, actual code: 12 instructions
extern "C" void FUN_0044c150(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0044c100(void) {
    __asm {
        push  esi
        mov  esi,ecx
        mov  DWORD PTR [esi],0x4703e4
        call FUN_0044c150
        test  BYTE PTR [esp+0x8],0x1
        je loc_0044C11E
        push  esi
        call _free
        add  esp,0x4
    loc_0044C11E:
        mov  eax,esi
        pop  esi
        ret  0x4
    }
}
