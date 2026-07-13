// 00417770: FUN_00417770
// Original size: 144 bytes, actual code: 27 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00417770(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR [eax+0x18]
        test  esi,esi
        je loc_004177B0
        push  edi
        nop
    loc_00417780:
        mov  edx,DWORD PTR [esi]
        mov  edi,DWORD PTR [esi+0x8]
        mov  ecx,esi
        call  DWORD PTR [edx+0x10]
        mov  eax,DWORD PTR [esi+0x4]
        mov  ecx,DWORD PTR [esi+0x8]
        mov  DWORD PTR [eax+0x8],ecx
        mov  eax,DWORD PTR [esi+0x8]
        test  eax,eax
        je loc_004177A0
        mov  edx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [eax+0x4],edx
    loc_004177A0:
        push  esi
        call _free
        add  esp,0x4
        test  edi,edi
        mov  esi,edi
        jne loc_00417780
        pop  edi
    loc_004177B0:
        pop  esi
        ret
    }
}
