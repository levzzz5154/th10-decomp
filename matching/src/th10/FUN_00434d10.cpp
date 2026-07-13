// 00434D10: FUN_00434d10
// Original size: 192 bytes, actual code: 36 instructions
extern "C" void _free(void);
extern "C" void _free(void);
extern "C" void _eh_vector_destructor_iterator_(void);

extern "C" __declspec(naked) void FUN_00434d10(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x8]
        push  edi
        xor  edi,edi
        cmp  eax,edi
        je loc_00434D26
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0x8],edi
    loc_00434D26:
        mov  eax,DWORD PTR [esi]
        cmp  eax,edi
        mov  DWORD PTR [esi+0x8],edi
        je loc_00434D4E
        mov  ecx,DWORD PTR [eax-0x4]
        push  ebx
        lea  ebx,[eax-0x4]
        push  0x435250
        push  ecx
        push  0x10
        push  eax
        call _eh_vector_destructor_iterator_
        push  ebx
        call _free
        add  esp,0x4
        pop  ebx
    loc_00434D4E:
        mov  ecx,DWORD PTR [esi+0xc]
        cmp  ecx,edi
        mov  DWORD PTR [esi],edi
        je loc_00434D5E
        mov  edx,DWORD PTR [ecx]
        push  0x1
        call  DWORD PTR [edx+0x1c]
    loc_00434D5E:
        mov  DWORD PTR [esi+0xc],edi
        mov  DWORD PTR [esi+0x4],edi
        pop  edi
        ret
    }
}
