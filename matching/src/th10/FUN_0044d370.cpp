// 0044D370: FUN_0044d370
// Original size: 208 bytes, actual code: 44 instructions
extern "C" void _rand(void);

extern "C" __declspec(naked) void FUN_0044d370(void) {
    __asm {
        push  ecx
        mov  eax,DWORD PTR [edi+0x4]
        test  eax,eax
        jne loc_0044D37C
        xor  eax,eax
        pop  ecx
        ret
    loc_0044D37C:
        mov  eax,DWORD PTR [edi+0x10]
        push  esi
        xor  esi,esi
        test  eax,eax
        jbe loc_0044D3B6
    loc_0044D386:
        mov  eax,DWORD PTR [edi+0x4]
        cmp  DWORD PTR [eax+esi*4],0x0
        je loc_0044D3AE
        mov  ecx,eax
        mov  DWORD PTR [esp+0x4],0x0
        mov  eax,DWORD PTR [ecx+esi*4]
        mov  edx,DWORD PTR [eax]
        lea  ecx,[esp+0x4]
        push  ecx
        push  eax
        call  DWORD PTR [edx+0x24]
        test  BYTE PTR [esp+0x4],0x1
        je loc_0044D3B6
    loc_0044D3AE:
        mov  eax,DWORD PTR [edi+0x10]
        inc  esi
        cmp  esi,eax
        jb loc_0044D386
    loc_0044D3B6:
        cmp  esi,DWORD PTR [edi+0x10]
        je loc_0044D3C4
        mov  edx,DWORD PTR [edi+0x4]
        mov  eax,DWORD PTR [edx+esi*4]
        pop  esi
        pop  ecx
        ret
    loc_0044D3C4:
        call _rand
        xor  edx,edx
        div  DWORD PTR [edi+0x10]
        mov  eax,DWORD PTR [edi+0x4]
        pop  esi
        mov  eax,DWORD PTR [eax+edx*4]
        pop  ecx
        ret
    }
}
