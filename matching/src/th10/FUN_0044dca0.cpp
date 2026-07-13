// 0044DCA0: FUN_0044dca0
// Original size: 160 bytes, actual code: 40 instructions

extern "C" __declspec(naked) void FUN_0044dca0(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x7c]
        test  eax,eax
        jne loc_0044DCB2
        mov  eax,DWORD PTR [esi+0x8c]
        cmp  eax,0xffffffff
        jne loc_0044DCB8
    loc_0044DCB2:
        mov  eax,0x80004005
        ret
    loc_0044DCB8:
        test  eax,eax
        mov  DWORD PTR [esi+0x90],ecx
        je loc_0044DCE5
        mov  ecx,DWORD PTR [ecx+0x10]
        mov  edx,DWORD PTR ds:0x4977a4
        push  0x0
        push  0x0
        add  ecx,edx
        push  ecx
        push  eax
        call  DWORD PTR ds:0x4660c8
        mov  edx,DWORD PTR [esi+0x90]
        mov  eax,DWORD PTR [edx+0x1c]
        mov  DWORD PTR [esi+0x8],eax
    loc_0044DCE5:
        mov  ecx,DWORD PTR [esi+0x8]
        mov  DWORD PTR [esi+0x2c],ecx
        xor  eax,eax
        ret
    }
}
