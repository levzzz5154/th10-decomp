// 0040C6E0: FUN_0040c6e0
// Original size: 80 bytes, actual code: 27 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0040c6e0(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR [eax+0x1034]
        test  esi,esi
        je loc_0040C70B
        push  edi
        nop
    loc_0040C6F0:
        mov  ecx,DWORD PTR [esi]
        mov  edi,DWORD PTR [esi+0x4]
        push  ecx
        call _free
        push  esi
        call _free
        add  esp,0x8
        test  edi,edi
        mov  esi,edi
        jne loc_0040C6F0
        pop  edi
    loc_0040C70B:
        pop  esi
        ret
    }
}
