// 00418C40: FUN_00418c40
// Original size: 192 bytes, actual code: 56 instructions

extern "C" __declspec(naked) void FUN_00418c40(void) {
    __asm {
        push  esi
        push  edi
        xor  eax,eax
        mov  ecx,0xd
        mov  edi,edx
        rep stosd
        mov  ecx,0x258
        mov  WORD PTR [edx+0x16],cx
        mov  WORD PTR [edx+0x18],cx
        mov  cl,0x1
        mov  BYTE PTR [edx+0x1b],cl
        mov  BYTE PTR [edx+0x1c],cl
        or   DWORD PTR [edx+0x30],0x100
        xor  al,al
        mov  BYTE PTR [edx+0x1a],al
        mov  DWORD PTR [edx],0x100003
        mov  BYTE PTR [edx+0x1d],al
        mov  BYTE PTR [edx+0x1e],al
        mov  esi,DWORD PTR ds:0x474e88
        lea  ecx,[edx+0x4]
        mov  DWORD PTR [ecx],esi
        mov  esi,DWORD PTR ds:0x474e8c
        mov  DWORD PTR [ecx+0x4],esi
        mov  esi,DWORD PTR ds:0x474e90
        mov  DWORD PTR [ecx+0x8],esi
        mov  esi,DWORD PTR ds:0x474e94
        mov  DWORD PTR [ecx+0xc],esi
        mov  si,WORD PTR ds:0x474e98
        pop  edi
        mov  WORD PTR [ecx+0x10],si
        mov  BYTE PTR [edx+0x1f],0x2
        mov  BYTE PTR [edx+0x22],al
        mov  BYTE PTR [edx+0x20],0x64
        mov  BYTE PTR [edx+0x21],0x50
        pop  esi
        ret
    }
}
