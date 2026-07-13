// 00436A30: FUN_00436a30
// Original size: 192 bytes, actual code: 28 instructions

extern "C" __declspec(naked) void FUN_00436a30(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x114]
        push  edi
        xor  edi,edi
        cmp  eax,edi
        je loc_00436A97
        mov  ecx,DWORD PTR [esi+0x118]
        push  ecx
        push  eax
        call  DWORD PTR ds:0x46602c
        mov  edx,DWORD PTR [esi+0x114]
        push  edx
        call  DWORD PTR ds:0x466028
        mov  eax,DWORD PTR [esi+0x11c]
        push  eax
        call  DWORD PTR ds:0x466030
        mov  DWORD PTR [esi+0x104],edi
        mov  DWORD PTR [esi+0x108],edi
        mov  DWORD PTR [esi+0x114],edi
        mov  DWORD PTR [esi+0x11c],edi
        mov  DWORD PTR [esi+0x118],edi
        mov  DWORD PTR [esi+0x120],edi
        mov  DWORD PTR [esi+0x100],0xffffffff
        mov  al,0x1
        pop  edi
        ret
    loc_00436A97:
        xor  al,al
        pop  edi
        ret
    }
}
