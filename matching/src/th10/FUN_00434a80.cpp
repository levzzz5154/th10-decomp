// 00434A80: FUN_00434a80
// Original size: 416 bytes, actual code: 60 instructions

extern "C" __declspec(naked) void FUN_00434a80(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR [esp+0x8]
        mov  DWORD PTR [eax+0xb4],esi
        push  edi
        mov  edi,DWORD PTR ds:0x491c14
        lea  esi,[eax+0x88]
        mov  DWORD PTR [esi],edi
        mov  edi,DWORD PTR ds:0x491c18
        mov  DWORD PTR [esi+0x4],edi
        mov  edi,DWORD PTR ds:0x491c1c
        mov  DWORD PTR [esi+0x8],edi
        mov  edi,DWORD PTR ds:0x491c14
        lea  esi,[eax+0x94]
        mov  DWORD PTR [esi],edi
        mov  edi,DWORD PTR ds:0x491c18
        mov  DWORD PTR [esi+0x4],edi
        mov  edi,DWORD PTR ds:0x491c1c
        mov  DWORD PTR [esi+0x8],edi
        movzx esi,BYTE PTR [esp+0x10]
        mov  DWORD PTR [eax+0xb8],esi
        mov  edi,DWORD PTR [edx]
        lea  esi,[eax+0x70]
        mov  DWORD PTR [esi],edi
        mov  edi,DWORD PTR [edx+0x4]
        mov  DWORD PTR [esi+0x4],edi
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [esi+0x8],edx
        mov  esi,DWORD PTR [ecx]
        lea  edx,[eax+0x7c]
        mov  DWORD PTR [edx],esi
        mov  esi,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x4],esi
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edx+0x8],ecx
        mov  ecx,DWORD PTR [eax+0xb0]
        xor  edx,edx
        test  cl,0x1
        pop  edi
        pop  esi
        jne loc_00434B35
        or   ecx,0x1
        mov  DWORD PTR [eax+0xa4],edx
        mov  DWORD PTR [eax+0xa0],0xfff0bdc1
        mov  DWORD PTR [eax+0xa8],edx
        mov  DWORD PTR [eax+0xac],0x476f78
        mov  DWORD PTR [eax+0xb0],ecx
    loc_00434B35:
        mov  DWORD PTR [eax+0xa4],edx
        mov  DWORD PTR [eax+0xa8],edx
        mov  DWORD PTR [eax+0xa0],0xffffffff
        ret  0x8
    }
}
