// 004363C0: FUN_004363c0
// Original size: 112 bytes, actual code: 19 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_004363c0(void) {
    __asm {
        push  esi
        mov  esi,ecx
        mov  eax,DWORD PTR [esi+0xc]
        push  edi
        xor  edi,edi
        cmp  eax,edi
        mov  DWORD PTR [esi],0x46f308
        je loc_004363DF
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0xc],edi
    loc_004363DF:
        mov  DWORD PTR [esi+0xc],edi
        mov  DWORD PTR [esi+0x4],edi
        mov  DWORD PTR [esi+0x8],edi
        pop  edi
        mov  DWORD PTR [esi],0x46f210
        pop  esi
        ret
    }
}
