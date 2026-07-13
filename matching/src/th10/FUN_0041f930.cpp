// 0041F930: FUN_0041f930
// Original size: 96 bytes, actual code: 28 instructions
extern "C" void FUN_00447810(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0041f930(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        add  esi,0x3ad084
        push  edi
        mov  edi,DWORD PTR [esi]
        test  edi,edi
        je loc_0041F95A
        call FUN_00447810
        mov  eax,DWORD PTR [esi]
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],0x0
    loc_0041F95A:
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [esi+0x3ad088]
        add  esi,0x3ad088
        test  edi,edi
        je loc_0041F986
        call FUN_00447810
        mov  ecx,DWORD PTR [esi]
        push  ecx
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],0x0
    loc_0041F986:
        pop  edi
        xor  eax,eax
        pop  esi
        ret
    }
}
