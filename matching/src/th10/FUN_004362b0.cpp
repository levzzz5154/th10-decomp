// 004362B0: FUN_004362b0
// Original size: 128 bytes, actual code: 35 instructions

extern "C" __declspec(naked) void FUN_004362b0(void) {
    __asm {
        push  ebx
        push  esi
        mov  esi,eax
        lea  eax,[esi+esi*2]
        lea  edx,[eax*4+0x477858]
        mov  eax,DWORD PTR [edx]
        lea  eax,[eax+eax*2]
        shl  eax,0x2
        push  edi
        cmp  DWORD PTR [eax+0x47785c],esi
        jne loc_004362D7
        mov  DWORD PTR [eax+0x47785c],ecx
        jmp loc_004362DD
    loc_004362D7:
        mov  DWORD PTR [eax+0x477860],ecx
    loc_004362DD:
        lea  eax,[ecx+ecx*2]
        shl  eax,0x2
        lea  esi,[eax+0x477858]
        mov  edi,edx
        mov  ebx,DWORD PTR [edi]
        mov  DWORD PTR [esi],ebx
        mov  ebx,DWORD PTR [edi+0x4]
        mov  DWORD PTR [esi+0x4],ebx
        mov  edi,DWORD PTR [edi+0x8]
        mov  DWORD PTR [esi+0x8],edi
        mov  esi,DWORD PTR [eax+0x47785c]
        lea  esi,[esi+esi*2]
        mov  DWORD PTR [esi*4+0x477858],ecx
        mov  eax,DWORD PTR [eax+0x477860]
        pop  edi
        lea  eax,[eax+eax*2]
        pop  esi
        mov  DWORD PTR [eax*4+0x477858],ecx
        mov  DWORD PTR [edx],0x0
        pop  ebx
        ret
    }
}
