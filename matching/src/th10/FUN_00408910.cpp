// 00408910: FUN_00408910
// Original size: 176 bytes, actual code: 47 instructions
extern "C" void _eh_vector_constructor_iterator_(void);

extern "C" __declspec(naked) void FUN_00408910(void) {
    __asm {
        mov  eax,fs:0x0
        push  0xffffffff
        push  0x465514
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  esi
        mov  esi,DWORD PTR [esp+0x14]
        push  edi
        push  0x401ff0
        push  0x402050
        push  0x2
        push  0x3ac
        lea  eax,[esi+0x10]
        push  eax
        call _eh_vector_constructor_iterator_
        push  0x401ff0
        push  0x402050
        push  0x8
        push  0x3ac
        lea  ecx,[esi+0x778]
        push  ecx
        mov  DWORD PTR [esp+0x24],0x0
        call _eh_vector_constructor_iterator_
        push  0x401ff0
        push  0x402050
        push  0x5
        push  0x3ac
        lea  edx,[esi+0x24d8]
        push  edx
        mov  BYTE PTR [esp+0x24],0x1
        call _eh_vector_constructor_iterator_
        and  DWORD PTR [esi+0x3744],0xfffffffe
        xor  eax,eax
        mov  edi,esi
        mov  ecx,0xdec
        rep stosd
        mov  eax,DWORD PTR [esi]
        mov  ecx,DWORD PTR [esp+0x8]
        or   eax,0x2
        mov  DWORD PTR [esi],eax
        pop  edi
        mov  DWORD PTR ds:0x4776f4,esi
        mov  eax,esi
        mov  DWORD PTR fs:0x0,ecx
        pop  esi
        add  esp,0xc
        ret  0x4
    }
}
