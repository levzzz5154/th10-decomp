// 00413810: FUN_00413810
// Original size: 368 bytes, actual code: 90 instructions
extern "C" void _eh_vector_constructor_iterator_(void);

extern "C" __declspec(naked) void FUN_00413810(void) {
    __asm {
        mov  eax,fs:0x0
        push  0xffffffff
        push  0x4654b5
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ebx
        push  esi
        mov  esi,DWORD PTR [esp+0x18]
        push  edi
        push  0x401ff0
        push  0x402050
        push  0xa
        push  0x3ac
        lea  eax,[esi+0x10]
        push  eax
        call _eh_vector_constructor_iterator_
        push  0x401ff0
        push  0x402050
        push  0xa
        push  0x3ac
        lea  ecx,[esi+0x24c8]
        push  ecx
        mov  DWORD PTR [esp+0x28],0x0
        call _eh_vector_constructor_iterator_
        push  0x401ff0
        push  0x402050
        push  0x9
        push  0x3ac
        lea  edx,[esi+0x4980]
        push  edx
        mov  BYTE PTR [esp+0x28],0x1
        call _eh_vector_constructor_iterator_
        push  0x401ff0
        push  0x402050
        push  0x4
        push  0x3ac
        lea  eax,[esi+0x6a8c]
        push  eax
        mov  BYTE PTR [esp+0x28],0x2
        call _eh_vector_constructor_iterator_
        push  0x401ff0
        push  0x402050
        push  0x2
        push  0x3ac
        lea  ecx,[esi+0x793c]
        push  ecx
        mov  BYTE PTR [esp+0x28],0x3
        call _eh_vector_constructor_iterator_
        push  0x401ff0
        push  0x402050
        push  0x7
        push  0x3ac
        lea  edx,[esi+0x8094]
        push  edx
        mov  BYTE PTR [esp+0x28],0x4
        call _eh_vector_constructor_iterator_
        mov  ecx,DWORD PTR [esi+0x9ab4]
        lea  edx,[esi+0x9a48]
        mov  ebx,0xfffffffe
        and  ecx,ebx
        mov  DWORD PTR [edx+0x6c],ecx
        and  DWORD PTR [edx+0xb0],ebx
        and  DWORD PTR [edx+0xfc],ebx
        and  DWORD PTR [edx+0x128],ebx
        and  DWORD PTR [edx+0x174],ebx
        and  DWORD PTR [edx+0x1b0],ebx
        and  DWORD PTR [edx+0x1fc],ebx
        and  DWORD PTR [edx+0x228],ebx
        and  DWORD PTR [edx+0x378],ebx
        xor  eax,eax
        mov  ecx,0xeb
        mov  edi,edx
        rep stosd
        mov  WORD PTR [edx+0x384],0xffff
        and  DWORD PTR [esi+0x9e70],ebx
        mov  edi,esi
        mov  ecx,0x27b4
        rep stosd
        mov  eax,DWORD PTR [esi]
        mov  ecx,DWORD PTR [esp+0xc]
        or   eax,0x2
        mov  DWORD PTR [esi],eax
        pop  edi
        mov  DWORD PTR ds:0x47770c,esi
        mov  eax,esi
        pop  esi
        mov  DWORD PTR fs:0x0,ecx
        pop  ebx
        add  esp,0xc
        ret  0x4
    }
}
