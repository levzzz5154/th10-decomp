// 00402160: FUN_00402160
// Original size: 208 bytes, actual code: 50 instructions
extern "C" void _eh_vector_constructor_iterator_(void);

extern "C" __declspec(naked) void FUN_00402160(void) {
    __asm {
        mov  eax,fs:0x0
        push  0xffffffff
        push  0x46556b
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  esi
        mov  esi,DWORD PTR [esp+0x14]
        mov  ecx,DWORD PTR [esi+0x34]
        push  edi
        mov  edi,0xfffffffe
        and  ecx,edi
        mov  DWORD PTR [esi+0x34],ecx
        and  DWORD PTR [esi+0x48],edi
        and  DWORD PTR [esi+0x90],edi
        mov  ecx,DWORD PTR [esi+0xdc]
        push  0x401ff0
        and  ecx,edi
        mov  DWORD PTR [esi+0xdc],ecx
        mov  eax,DWORD PTR [esi+0x168]
        push  0x402050
        and  eax,edi
        push  0x8
        mov  DWORD PTR [esi+0x168],eax
        push  0x3ac
        lea  eax,[esi+0x180]
        push  eax
        call _eh_vector_constructor_iterator_
        push  0x401ff0
        push  0x402050
        push  0x3
        push  0x3ac
        lea  ecx,[esi+0x1f08]
        push  ecx
        mov  DWORD PTR [esp+0x24],0x0
        call _eh_vector_constructor_iterator_
        and  DWORD PTR [esi+0x2a2c],edi
        xor  eax,eax
        mov  edi,esi
        mov  ecx,0xad9
        rep stosd
        mov  eax,DWORD PTR [esi]
        mov  ecx,DWORD PTR [esp+0x8]
        or   eax,0x2
        mov  DWORD PTR [esi],eax
        pop  edi
        mov  eax,esi
        mov  DWORD PTR fs:0x0,ecx
        pop  esi
        add  esp,0xc
        ret  0x4
    }
}
