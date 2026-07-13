// 00436260: FUN_00436260
// Original size: 80 bytes, actual code: 17 instructions

extern "C" __declspec(naked) void FUN_00436260(void) {
    __asm {
        push  edi
        lea  ecx,[esi+esi*2]
        mov  edi,DWORD PTR [ecx*4+0x477858]
        lea  eax,[edx+edx*2]
        mov  DWORD PTR [eax*4+0x477858],edi
        mov  eax,DWORD PTR [ecx*4+0x477858]
        lea  eax,[eax+eax*2]
        shl  eax,0x2
        cmp  DWORD PTR [eax+0x477860],esi
        pop  edi
        jne loc_0043629D
        mov  DWORD PTR [eax+0x477860],edx
        mov  DWORD PTR [ecx*4+0x477858],0x0
        ret
    loc_0043629D:
        mov  DWORD PTR [eax+0x47785c],edx
        mov  DWORD PTR [ecx*4+0x477858],0x0
        ret
    }
}
