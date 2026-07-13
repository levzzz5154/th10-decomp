// 00436680: FUN_00436680
// Original size: 64 bytes, actual code: 19 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00436680(void) {
    __asm {
        push  esi
        mov  esi,ecx
        mov  eax,DWORD PTR [esi+0xc]
        push  edi
        xor  edi,edi
        cmp  eax,edi
        mov  DWORD PTR [esi],0x46f308
        je loc_0043669F
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0xc],edi
    loc_0043669F:
        mov  DWORD PTR [esi+0xc],edi
        mov  DWORD PTR [esi+0x4],edi
        mov  DWORD PTR [esi+0x8],edi
        pop  edi
        mov  DWORD PTR [esi],0x46f210
        pop  esi
        ret
    }
}
