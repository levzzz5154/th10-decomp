// 00436430: FUN_00436430
// Original size: 320 bytes, actual code: 17 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00436430(void) {
    __asm {
        push  esi
        mov  esi,ecx
        mov  eax,DWORD PTR [esi+0xc]
        push  edi
        xor  edi,edi
        cmp  eax,edi
        je loc_00436449
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0xc],edi
    loc_00436449:
        mov  DWORD PTR [esi+0xc],edi
        mov  DWORD PTR [esi+0x4],edi
        mov  DWORD PTR [esi+0x8],edi
        pop  edi
        pop  esi
        ret
    }
}
