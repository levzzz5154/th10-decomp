// 0044DBF0: FUN_0044dbf0
// Original size: 176 bytes, actual code: 58 instructions

extern "C" __declspec(naked) void FUN_0044dbf0(void) {
    __asm {
        cmp  eax,0x1
        push  edi
        mov  edi,edx
        mov  DWORD PTR [esi+0x78],eax
        mov  DWORD PTR [esi+0x7c],0x0
        jne loc_0044DC99
        test  ecx,ecx
        jne loc_0044DC11
        mov  eax,0x80070057
        pop  edi
        ret
    loc_0044DC11:
        push  0x0
        push  0x8000080
        push  0x3
        push  0x0
        push  0x1
        push  0x80000000
        push  ecx
        call  DWORD PTR ds:0x4660c4
        cmp  eax,0xffffffff
        mov  DWORD PTR [esi+0x8c],eax
        jne loc_0044DC3C
        mov  eax,0x80004005
        pop  edi
        ret
    loc_0044DC3C:
        mov  ecx,DWORD PTR [esi+0x7c]
        test  ecx,ecx
        mov  DWORD PTR [esi+0x90],edi
        je loc_0044DC6C
        mov  eax,DWORD PTR [esi+0x80]
        mov  DWORD PTR [esi+0x84],eax
        mov  eax,DWORD PTR [edi+0x1c]
        test  eax,eax
        jle loc_0044DC93
        mov  ecx,DWORD PTR [esi+0x8]
        mov  DWORD PTR [esi+0x88],eax
        mov  DWORD PTR [esi+0x2c],ecx
        xor  eax,eax
        pop  edi
        ret
    loc_0044DC6C:
        test  eax,eax
        je loc_0044DC93
        mov  ecx,DWORD PTR [edi+0x10]
        mov  edi,DWORD PTR ds:0x4977a4
        push  0x0
        push  0x0
        add  ecx,edi
        push  ecx
        push  eax
        call  DWORD PTR ds:0x4660c8
        mov  edx,DWORD PTR [esi+0x90]
        mov  eax,DWORD PTR [edx+0x1c]
        mov  DWORD PTR [esi+0x8],eax
    loc_0044DC93:
        mov  ecx,DWORD PTR [esi+0x8]
        mov  DWORD PTR [esi+0x2c],ecx
    loc_0044DC99:
        xor  eax,eax
        pop  edi
        ret
    }
}
